/*
 * Copyright (c) 2014, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <xlat_tables.h>
#include <platform.h>
#include <debug.h>
#include <bl_common.h>
#include <assert.h>
#include <context.h>
#include <context_mgmt.h>
#include <fiq_smp_call.h>
#include <runtime_svc.h>
#include <console.h>
#include "plat_private.h"   //for atf_arg_t_ptr

extern void mt_log_set_crash_flag(void);
uint64_t wdt_kernel_cb_addr = 0;


/*
 * The following 2 platform setup functions are weakly defined. They
 * provide typical implementations that may be re-used by multiple
 * platforms but may also be overridden by a platform if required.
 */
#pragma weak bl31_plat_enable_mmu
#pragma weak bl32_plat_enable_mmu

extern unsigned long g_dormant_log_base;
void atf_low_level_log(int tag)
{
        int cpuid = platform_get_core_pos(read_mpidr());
/*
        printf("+atf_low_level_log, cpu %d, g_dormant_log_base=0x%x \n",
        (int)cpuid, g_dormant_log_base);
*/
        if (g_dormant_log_base == 0)
                return;
        ((long *)g_dormant_log_base)[cpuid] = tag;
        dsb();
}

void bl31_plat_enable_mmu(uint32_t flags)
{
	enable_mmu_el3(flags);
}

void bl32_plat_enable_mmu(uint32_t flags)
{
	enable_mmu_el1(flags);
}

void aee_wdt_dump()
{
        struct atf_aee_regs *regs;
        cpu_context_t *ns_cpu_context;
        uint64_t mpidr = read_mpidr();
        uint32_t linear_id = platform_get_core_pos(mpidr);
        unsigned long i,count;
        unsigned long sp_phys;
        uint64_t *pp;
        uint32_t spsr;

        atf_low_level_log(0xA7F00E00);
        printf("=>aee_wdt_dump(dis-IRQ),CPU%d\n", (int)linear_id);

        ns_cpu_context = cm_get_context_by_mpidr(mpidr, NON_SECURE);
    /* compatible to the earlier chipset */
#if (defined(MACH_TYPE_MT6735) || defined(MACH_TYPE_MT6735M) || \
     defined(MACH_TYPE_MT6753) || defined(MACH_TYPE_MT8173))
	    atf_arg_t_ptr teearg = (atf_arg_t_ptr)(uintptr_t)TEE_BOOT_INFO_ADDR;
#else
        atf_arg_t_ptr teearg = &gteearg;;
#endif
        regs = (void *)(teearg->atf_aee_debug_buf_start + (linear_id * sizeof(struct atf_aee_regs)));

        regs->pstate = SMC_GET_EL3(ns_cpu_context, CTX_SPSR_EL3)
        regs->pc = SMC_GET_EL3(ns_cpu_context, CTX_ELR_EL3)
        regs->sp = read_ctx_reg(get_sysregs_ctx(ns_cpu_context), CTX_SP_EL1);
        regs->regs[0] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X0)
        regs->regs[1] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X1)
        regs->regs[2] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X2)
        regs->regs[3] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X3)
        regs->regs[4] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X4)
        regs->regs[5] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X5)
        regs->regs[6] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X6)
        regs->regs[7] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X7)
        regs->regs[8] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X8)
        regs->regs[9] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X9)
        regs->regs[10] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X10)
        regs->regs[11] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X11)
        regs->regs[12] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X12)
        regs->regs[13] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X13)
        regs->regs[14] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X14)
        regs->regs[15] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X15)
        regs->regs[16] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X16)
        regs->regs[17] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X17)
        regs->regs[18] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X18)
        regs->regs[19] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X19)
        regs->regs[20] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X20)
        regs->regs[21] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X21)
        regs->regs[22] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X22)
        regs->regs[23] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X23)
        regs->regs[24] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X24)
        regs->regs[25] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X25)
        regs->regs[26] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X26)
        regs->regs[27] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X27)
        regs->regs[28] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X28)
        regs->regs[29] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_X29)
        regs->regs[30] = SMC_GET_GP(ns_cpu_context, CTX_GPREG_LR)

        if(0 == wdt_kernel_cb_addr) {
            set_uart_flag();
            printf("=> wdt_kernel_cb_addr=0, error before WDT successfully initialized. cpu %d\n", (int)linear_id);
            printf("=> regs->pc : 0x%lx\n", regs->pc);
            printf("=> regs->lr : 0x%lx\n", regs->regs[30]);
            printf("=> regs->sp : 0x%lx\n", regs->sp);

            /* Dump regs */
            printf("=> Informations: pstate=%lx, pc=%lx, sp=%lx\n", regs->pstate, regs->pc, regs->sp);
            for(i=1; i<32; i++) {
                printf("regs->regs[%d] = %lx \n", i, regs->regs[i-1]);
            }

            if (0 == regs->sp) {
                printf("=> sp is NULL, skip stack dump\n");
            } else {
                /* physical address of sp */
                sp_phys = (regs->sp - 0xffffffc000000000) + 0x40000000;
                printf("=> sp_phys : 0x%lx\n", sp_phys);

                printf("=> sp_phys (aligned) : 0x%lx\n", (sp_phys & ~(PAGE_SIZE_2MB_MASK)));

                /* map spphyscial memory for 2MB */
                mmap_add_region((sp_phys & ~(PAGE_SIZE_2MB_MASK)),
                                (sp_phys & ~(PAGE_SIZE_2MB_MASK)),
                                 PAGE_SIZE_2MB,
                                 MT_DEVICE | MT_RW | MT_NS);

                //re-fill translation table
                init_xlat_tables();

                /* flush sp content  */
                flush_dcache_range((uint64_t)sp_phys, (uint64_t)0x2000);

                /* dump 8k */
                pp = (uint64_t *)(uintptr_t)sp_phys;
                //count = ((unsigned long)0x4000-(sp_phys &(~((unsigned long)(0x4000-1)))))/8;
                count = (0x4000 - (sp_phys &(0x4000-1)))/8;

                printf("=> dump sp content with 16K boundry count = %ld ,mask with 0x3fff...\n",count);
                for(i=0; i< count ; i++,pp++) {
                    printf("%16lx:%16lx\n",pp,*pp);
                }
            }
            mt_log_set_crash_flag();
            printf("=> wait until reboot...\n");
            while(1);
        }

        spsr = SMC_GET_EL3(ns_cpu_context, CTX_SPSR_EL3);
        // default enter EL1(64b) or SVC(32b) when enter AEE dump
        if (LINUX_KERNEL_64 == get_kernel_k32_64()){
            spsr = (spsr & ~((MODE_EL_MASK) << MODE_EL_SHIFT));
            spsr = (spsr | ((MODE_EL1) << MODE_EL_SHIFT));
        } else {
            spsr = (spsr & ~((MODE32_MASK) << MODE32_SHIFT));
            spsr = (spsr | ((MODE32_svc) << MODE32_SHIFT));
        }

        // disable IRQ when enter AEE dump
        spsr = (spsr | (DAIF_IRQ_BIT << SPSR_AIF_SHIFT));
        SMC_SET_EL3(ns_cpu_context, CTX_SPSR_EL3, spsr);

        // wdt kernel callback addr should be ready now...
        SMC_SET_EL3(ns_cpu_context, CTX_ELR_EL3, wdt_kernel_cb_addr);
}

void __attribute__((weak)) dump_wfi_spill(void) {}
