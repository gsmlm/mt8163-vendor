/*
 * Copyright (c) 2014 TRUSTONIC LIMITED
 * All rights reserved
 *
 * The present software is the confidential and proprietary information of
 * TRUSTONIC LIMITED. You shall not disclose the present software and shall
 * use it only in accordance with the terms of the license agreement you
 * entered into with TRUSTONIC LIMITED. This software may be subject to
 * export or import laws in certain countries.
 */

#include <stdio.h>
#include <string.h>
#include <bl_common.h>
#include <assert.h>
#include <arch_helpers.h>
#include <console.h>
#include <platform.h>
#include <context_mgmt.h>
#include <runtime_svc.h>
#include <bl31.h>
#include <tbase_private.h>

#include <gic_v2.h>
#include <gic_v3.h>
#include <interrupt_mgmt.h>
#include <plat_config.h>
#include "plat_private.h"


/*
 * Notes:
 *   * 32 bit SMC take and return only 32 bit results; remaining bits are undef.
 *     * Never use remaining values for anything.
 *   * PM callbacks are dummy.
 *     * Implement resume and migrate callbacks.
 *   * We update secure system registers at every return. We could optimize this.
 * To be consireded:
 *   * Initialization checks: Check non-null context
 *   * On-demand intialization
 *   * State checking: Chech tbase does not return incorrect way
 *     (fastcall vs normal SMC / interrupt)
 *   * Disable FIQs, if occuring when tbase is not ok to handle them.
 */ 

// MSM areas
struct msm_area_t msm_area;

// Context for each core. gp registers not used by SPD.
tbase_context *secure_context = msm_area.secure_context;

// FIQ dump related functions
extern uint32_t plat_tbase_input(uint64_t DataId,uint64_t* Length,void* out);
extern uint32_t plat_tbase_forward_fiq(uint32_t fiqId);
extern uint32_t plat_tbase_dump(void);
extern void mt_atf_trigger_WDT_FIQ();

// ************************************************************************************
// Common setup for normal fastcalls and fastcalls to tbase

static void tbase_setup_entry_common( cpu_context_t *s_context, 
              cpu_context_t *ns_context, 
              uint32_t call_offset) {
  // Set up registers
  gp_regs_t *s_gpregs = get_gpregs_ctx(s_context);  
  
  // NWd spsr
  uint64_t ns_spsr = read_ctx_reg(get_el3state_ctx(ns_context), CTX_SPSR_EL3);
  write_ctx_reg(s_gpregs, CTX_GPREG_X2, ns_spsr);
  
  // Entry to tbase
  el3_state_t *el3sysregs = get_el3state_ctx(s_context);
  write_ctx_reg(el3sysregs, CTX_SPSR_EL3, tbaseEntrySpsr);
  
  cm_set_elr_el3(SECURE,tbaseEntryBase+call_offset);
}

// ************************************************************************************
// Set up fastcall or normal SMC entry from NWd to tbase

void tbase_setup_entry_nwd( cpu_context_t *ns_context, uint32_t call_offset ) {

  uint64_t registerAddress = (int64_t)get_gpregs_ctx(ns_context);

  // Set up registers
  cpu_context_t *s_context = (cpu_context_t *) cm_get_context(SECURE);
  gp_regs_t *s_gpregs = get_gpregs_ctx(s_context);  

  // Offset into registerFile
  uint64_t registerOffset = registerAddress -registerFileStart[REGISTER_FILE_NWD];
  write_ctx_reg(s_gpregs, CTX_GPREG_X0, registerOffset);
  // Flags
  write_ctx_reg(s_gpregs, CTX_GPREG_X1, (TBASE_NWD_REGISTER_COUNT<<8) | TBASE_SMC_NWD);

  tbase_setup_entry_common( s_context, ns_context, call_offset );
}

// ************************************************************************************
// Set up fastcall entry from monitor to tbase

void tbase_setup_entry_monitor( cpu_context_t *ns_context ) {
  uint64_t mpidr = read_mpidr();
  uint32_t linear_id = platform_get_core_pos(mpidr);
  uint64_t registerAddress = (int64_t)secure_context[linear_id].monitorCallRegs;
  
  // Set up registers
  cpu_context_t *s_context = (cpu_context_t *) cm_get_context(SECURE);
  gp_regs_t *s_gpregs = get_gpregs_ctx(s_context);  

  // Offset into registerFile
  uint64_t registerOffset = page_align(registerFileEnd[REGISTER_FILE_NWD] - registerFileStart[REGISTER_FILE_NWD], UP) + (uint64_t)registerAddress - registerFileStart[REGISTER_FILE_MONITOR];
  write_ctx_reg(s_gpregs, CTX_GPREG_X0, registerOffset);
  // Flags
  write_ctx_reg(s_gpregs, CTX_GPREG_X1, (TBASE_MAX_MONITOR_CALL_REGS<<8) | TBASE_SMC_MONITOR);

  tbase_setup_entry_common( s_context, ns_context, ENTRY_OFFSET_FASTCALL );
}

// ************************************************************************************
// Print NWd parameters X0...X3

#if DEBUG
void print_fastcall_params( char *msg, uint32_t secure ) {
  gp_regs_t *ns_gpregs = get_gpregs_ctx((cpu_context_t *) cm_get_context(secure)); 
  DBG_PRINTF("tbase %s (%d) 0x%llx 0x%llx 0x%llx 0x%llx\n\r", msg, secure,
    read_ctx_reg(ns_gpregs, CTX_GPREG_X0), 
    read_ctx_reg(ns_gpregs, CTX_GPREG_X1), 
    read_ctx_reg(ns_gpregs, CTX_GPREG_X2), 
    read_ctx_reg(ns_gpregs, CTX_GPREG_X3) );
}
#endif

// ************************************************************************************
// Forward fastcall to tbase
// Returns 0 in case of successfull call, and non-zero in case of error.
// If resp is non-NULL, return values are put there.
// If previous context was NON_SECURE, caller must save it before call.
// Function changes to SECURE context.

uint64_t tbase_monitor_fastcall(uint32_t smc_fid,
        uint64_t x1,
        uint64_t x2,
        uint64_t x3,
        uint64_t x4,
        fc_response_t *resp )
{
  uint64_t mpidr = read_mpidr();
  uint32_t linear_id = platform_get_core_pos(mpidr);
  tbase_context *tbase_ctx = &secure_context[linear_id];
  uint64_t *regs = tbase_ctx->monitorCallRegs;
  
  if ((tbaseExecutionStatus&TBASE_STATUS_FASTCALL_OK_BIT)==0) {
    // TBASE must be initialized to be usable
    DBG_PRINTF( "tbase_monitor_fastcall tbase not ready for fastcall\n\r" );
    return 1;
  }
  if(tbase_ctx->state == TBASE_STATE_OFF) {
    DBG_PRINTF( "tbase_monitor_fastcall tbase not ready for fastcall\n\r" );
    return 1;
  }


  // parameters for call
  regs[0] = smc_fid;
  regs[1] = x1;
  regs[2] = x2;
  regs[3] = x3;
  regs[4] = x4;

  cpu_context_t *ns_context = (cpu_context_t *) cm_get_context(NON_SECURE);
  tbase_setup_entry_monitor(ns_context);

  tbase_synchronous_sp_entry(tbase_ctx);

  if (resp!=NULL) {
    resp->x1 = regs[1];
    resp->x2 = regs[2];
    resp->x3 = regs[3];
    resp->x4 = regs[4];
  }
  
  return 0;
}

// ************************************************************************************
// Output thru monitor

static void output(uint64_t x1,uint64_t x2) 
{
  switch(maskSWdRegister(x1)) {
    case TBASE_SMC_FASTCALL_OUTPUT_PUTC:
      TBASE_OUTPUT_PUTC(x2&0xFF);
    break;
  }
}


// ************************************************************************************
// Set tbase status

static void tbase_status(uint64_t x1,uint64_t x2) 
{
  DBG_PRINTF( "tbase_fastcall_handler TBASE_SMC_FASTCALL_STATUS %x %x\n\r", x1, x2 );
  switch(maskSWdRegister(x1)) {
    case TBASE_SMC_FASTCALL_STATUS_EXECUTION:
      tbaseExecutionStatus = maskSWdRegister(x2);
      TBASE_EXECUTION_STATUS(tbaseExecutionStatus);
      break;
  }
}


// ************************************************************************************
// tbase_fiqforward_configure(intrNo,status)
void tbase_fiqforward_configure(uint32_t intrNo, uint32_t enable)
{
  // Trigger monitor fastcall to t-base for FIQ configuration
  tbase_monitor_fastcall( (uint32_t)TBASE_SMC_FASTCALL_FIQFORWARD_CONFIG,
                          (uint64_t)intrNo,
                          (uint64_t)enable,
                          (uint64_t)0,
                          (uint64_t)0,
                          NULL);

  DBG_PRINTF( "%s: Forwarding interrupt %d is %s\n\r", 
              __func__,
              intrNo,
              (enable == TBASE_FLAG_SET)?"enabled":"disabled" );
}


// ************************************************************************************
// fastcall handler
static uint64_t tbase_fastcall_handler(uint32_t smc_fid,
        uint64_t x1,
        uint64_t x2,
        uint64_t x3,
        uint64_t x4,
        void *cookie,
        void *handle,
        uint64_t flags)
{
  uint64_t mpidr = read_mpidr();
  uint32_t linear_id = platform_get_core_pos(mpidr);
  tbase_context *tbase_ctx = &secure_context[linear_id];
  int caller_security_state = flags&1;
      
  if (caller_security_state==SECURE) {
    switch(maskSWdRegister(smc_fid)) {
      case TBASE_SMC_FASTCALL_RETURN: {
        // Return values from fastcall already in cpu_context!
        // TODO: Could we skip saving sysregs?
        DBG_PRINTF( "tbase_fastcall_handler TBASE_SMC_FASTCALL_RETURN\n\r");
        tbase_synchronous_sp_exit(tbase_ctx, 0, 1);
      } 
      case TBASE_SMC_FASTCALL_CONFIG_OK: {
                                DBG_PRINTF( "tbase_fastcall_handler TBASE_SMC_FASTCALL_CONFIG_OK\n\r");
        configure_tbase(x1,x2);
        SMC_RET1(handle,smc_fid);
        break;
      } 
      case TBASE_SMC_FASTCALL_OUTPUT: {
        output(x1,x2);
        SMC_RET1(handle,smc_fid);
        break;
      }
      case TBASE_SMC_FASTCALL_STATUS: {
                                DBG_PRINTF( "tbase_fastcall_handler TBASE_SMC_FASTCALL_STATUS\n\r");
        tbase_status(x1,x2);
        SMC_RET1(handle,smc_fid);
        break;
      }
      case TBASE_SMC_FASTCALL_INPUT: {
                                DBG_PRINTF( "tbase_fastcall_handler TBASE_SMC_FASTCALL_INPUT\n\r");
        smc_fid = plat_tbase_input(x1,&x2,&(tbase_ctx->tbase_input_fastcall));
        SMC_RET3(handle,smc_fid,page_align(registerFileEnd[REGISTER_FILE_NWD] - registerFileStart[REGISTER_FILE_NWD], UP)+(uint64_t)&(tbase_ctx->tbase_input_fastcall)- registerFileStart[REGISTER_FILE_MONITOR],x2);
        break;
      }
      case TBASE_SMC_FASTCALL_DUMP: {
                                DBG_PRINTF( "tbase_fastcall_handler TBASE_SMC_FASTCALL_DUMP\n\r");
        //tbase_PlatformDump();
        SMC_RET1(handle,smc_fid);
        break;
      }
      case TBASE_SMC_FASTCALL_FORWARD_FIQ: {
                                DBG_PRINTF( "tbase_fastcall_handler TBASE_SMC_FASTCALL_FORWARD_FIQ\n\r");
        x1 = (uint64_t)plat_tbase_forward_fiq(x1);
        SMC_RET2(handle,smc_fid,x1);
        break;
      }
      
      default: {
        // What now?
        DBG_PRINTF( "tbase_fastcall_handler SMC_UNK %x\n\r", smc_fid );
        SMC_RET1(handle, SMC_UNK);
        break;
      }
    }
  }
  else
  {
    /* Handle AEE Dump even if t-base is not ready, as this will not enter tbase */
    if (smc_fid == TBASE_SMC_AEE_DUMP)         // N-world can request AEE Dump function
    {
      //if (mrdump_start(linear_id, x1)) {
        mt_atf_trigger_WDT_FIQ();
        // Once we return to the N-world's caller,
        // FIQ will be trigged and bring us on EL3 (ATF) on core #0 because HW wiring.
        // Then FIQ will be handled the same way as for HW WDT FIQ.

        //Do we need to save-recover n-context before being able to use it for return?
        cm_el1_sysregs_context_restore(NON_SECURE);
        cm_set_next_eret_context(NON_SECURE);
      //}
      return 0;
    }

    /* Now, check that tbase is ready before doing anything with other fastcalls */
    if ((tbaseExecutionStatus&TBASE_STATUS_FASTCALL_OK_BIT)==0) {
      // TBASE must be initialized to be usable
      // TODO: What is correct error code?
      DBG_PRINTF( "tbase_fastcall_handler tbase not ready for fastcall\n\r" );
      SMC_RET1(handle, SMC_UNK);
      return 0;
    }
    if(tbase_ctx->state == TBASE_STATE_OFF) {
      DBG_PRINTF( "tbase_fastcall_handler tbase not ready for fastcall\n\r" );
      SMC_RET1(handle, SMC_UNK);
      return 0;
    }

    DBG_PRINTF( "tbase_fastcall_handler NWd %x\n\r", smc_fid );
    // So far all fastcalls go to tbase
    // Save NWd context
    gp_regs_t *ns_gpregs = get_gpregs_ctx((cpu_context_t *)handle);
    write_ctx_reg(ns_gpregs, CTX_GPREG_X0, smc_fid ); // These are not saved yet
    write_ctx_reg(ns_gpregs, CTX_GPREG_X1, x1 );
    write_ctx_reg(ns_gpregs, CTX_GPREG_X2, x2 );
    write_ctx_reg(ns_gpregs, CTX_GPREG_X3, x3 );
    cm_el1_sysregs_context_save(NON_SECURE);

    // Load SWd context
    tbase_setup_entry_nwd((cpu_context_t *)handle,ENTRY_OFFSET_FASTCALL);
#if DEBUG
    print_fastcall_params("entry", NON_SECURE);
#endif
    tbase_synchronous_sp_entry(tbase_ctx);
    cm_el1_sysregs_context_restore(NON_SECURE);
    cm_set_next_eret_context(NON_SECURE);
    return 0; // Does not seem to matter what we return
  }
}


// ************************************************************************************
// SMC handler

static uint64_t tbase_smc_handler(uint32_t smc_fid,
        uint64_t x1,
        uint64_t x2,
        uint64_t x3,
        uint64_t x4,
        void *cookie,
        void *handle,
        uint64_t flags)
{
  uint64_t mpidr = read_mpidr();
  uint32_t linear_id = platform_get_core_pos(mpidr);
  tbase_context *tbase_ctx = &secure_context[linear_id];
  int caller_security_state = flags&1;
 
  //DBG_PRINTF("tbase_smc_handler %d %x\n\r", caller_security_state, smc_fid);
  
  if (caller_security_state==SECURE) {
    // Yield to NWd
    // TODO: Check id
    if (tbaseInitStatus==TBASE_INIT_CONFIG_OK) {
      // Save sysregs to all cores.
      // After this tbase can work on any core.
      save_sysregs_allcore();
      tbaseInitStatus = TBASE_INIT_SYSREGS_OK;
      if (tbaseExecutionStatus==TBASE_STATUS_UNINIT) {
        tbaseExecutionStatus = TBASE_STATUS_NORMAL;
      }
    }
    // If above check fails, it is not possible to return to tbase.
    tbase_synchronous_sp_exit(tbase_ctx, 0, 1);
  } 
  else {
    if ((tbaseExecutionStatus&TBASE_STATUS_SMC_OK_BIT)==0) {
      // TBASE must be initialized to be usable
      DBG_PRINTF( "tbase_smc_handler tbase not ready for smc.\n\r");
      // TODO: What is correct error code?
      SMC_RET1(handle, SMC_UNK);
      return 1;
    }
    if(tbase_ctx->state == TBASE_STATE_OFF) {
      DBG_PRINTF( "tbase_smc_handler tbase not ready for fastcall\n\r" );
      return 1;
    }

    // NSIQ, go to SWd
    // TODO: Check id?
    
    // Save NWd
    gp_regs_t *ns_gpregs = get_gpregs_ctx((cpu_context_t *)handle);
    write_ctx_reg(ns_gpregs, CTX_GPREG_X0, smc_fid );
    write_ctx_reg(ns_gpregs, CTX_GPREG_X1, x1 );
    write_ctx_reg(ns_gpregs, CTX_GPREG_X2, x2 );
    write_ctx_reg(ns_gpregs, CTX_GPREG_X3, x3 );
    cm_el1_sysregs_context_save(NON_SECURE);
    
    // Load SWd
    tbase_setup_entry_nwd((cpu_context_t *)handle,ENTRY_OFFSET_SMC);
    // Enter tbase. tbase must return using normal SMC, which will continue here.   
    tbase_synchronous_sp_entry(tbase_ctx);
    // Load NWd
    cm_el1_sysregs_context_restore(NON_SECURE);
    cm_set_next_eret_context(NON_SECURE);
  }
  return 0;
}

//************************************************************************************************
// FIQ handler for FIQ when in NWd
uint64_t tbase_fiq_handler( uint32_t id,
          uint32_t flags,
          void *handle,
          void *cookie)
{
  uint64_t mpidr;
  uint32_t linear_id;
  tbase_context *tbase_ctx;

  mpidr = read_mpidr();
  linear_id = platform_get_core_pos(mpidr);
  tbase_ctx = &secure_context[linear_id];
  assert(&tbase_ctx->cpu_ctx == cm_get_context(SECURE));
  
  /* Check if the vector has been entered for SGI/FIQ dump reason */
  if (id == FIQ_SMP_CALL_SGI) {
    /* ACK gic */
    {
        unsigned int iar;
        iar = gicc_read_IAR(get_plat_config()->gicc_base);
        gicc_write_EOIR(get_plat_config()->gicc_base, iar);
    }
    /* Save the non-secure context before entering the TSP */
    cm_el1_sysregs_context_save(NON_SECURE);
    /* Call customer's dump implementation */
    plat_tbase_dump();
    // Load NWd
    //cm_el1_sysregs_context_restore(NON_SECURE);
    //cm_set_next_eret_context(NON_SECURE);
  } 
  else {

    /* Check the security state when the exception was generated */
    assert(get_interrupt_src_ss(flags) == NON_SECURE);

    /* Sanity check the pointer to this cpu's context */
    assert(handle == cm_get_context(NON_SECURE));

    if ((tbaseExecutionStatus&TBASE_STATUS_SMC_OK_BIT)==0) {
      // TBASE must be initialized to be usable
      // TODO: What should we really do here?
      // We should disable FIQs to prevent futher interrupts
      DBG_PRINTF( "tbase_interrupt_handler tbase not ready for interrupt\n\r" );
      return 1;
    }
    if(tbase_ctx->state == TBASE_STATE_OFF) {
      DBG_PRINTF( "tbase_interrupt_handler tbase not ready for fastcall\n\r" );
      return 1;
    }

    /* Save the non-secure context before entering the TSP */
    cm_el1_sysregs_context_save(NON_SECURE);

    /* Switch to secure context now */
    cm_el1_sysregs_context_restore(SECURE);
    cm_set_next_eret_context(SECURE);

    // Load SWd context
    tbase_setup_entry_nwd((cpu_context_t *)handle,ENTRY_OFFSET_FIQ);
  
    // Enter tbase. tbase must return using normal SMC, which will continue here.
    tbase_synchronous_sp_entry(tbase_ctx);

    // Load NWd
    cm_el1_sysregs_context_restore(NON_SECURE);
    cm_set_next_eret_context(NON_SECURE);
  }

  return 0;
}

//************************************************************************************************
/* Register tbase fastcalls service */

DECLARE_RT_SVC(
  tbase_fastcall,
  OEN_TOS_START,
  OEN_TOS_END,
  SMC_TYPE_FAST,
  tbase_fastcall_setup,
  tbase_fastcall_handler
);

/* Register tbase SMC service */
// Note: OEN_XXX constants do not apply to normal SMCs (only to fastcalls).
DECLARE_RT_SVC(
  tbase_smc,
  0,
  2, /* bastien 2014-10-07 : shouldn't this be 1 ? */
  SMC_TYPE_STD,
  NULL,
  tbase_smc_handler
);

#if TBASE_OEM_ROUTE_ENABLE
/* Register tbase OEM SMC handler service */
DECLARE_RT_SVC(
  tbase_oem_fastcall,
  OEN_OEM_START,
  OEN_OEM_END,
  SMC_TYPE_FAST,
  NULL,
  tbase_fastcall_handler
);
#endif

#if TBASE_SIP_ROUTE_ENABLE
/* Register tbase SIP SMC handler service */
DECLARE_RT_SVC(
  tbase_sip_fastcall,
  OEN_SIP_START,
  OEN_SIP_END,
  SMC_TYPE_FAST,
  NULL,
  tbase_fastcall_handler
);
#endif

#if TBASE_DUMMY_SIP_ROUTE_ENABLE
/* Register tbase SIP SMC handler service, unfortunately because of a typo in our
 * older versions we must serve the 0x81000000 fastcall range for backward compat */
DECLARE_RT_SVC(
  tbase_dummy_sip_fastcall,
  OEN_CPU_START,
  OEN_CPU_END,
  SMC_TYPE_FAST,
  tbase_dummy_setup,
  tbase_fastcall_handler
);
#endif
