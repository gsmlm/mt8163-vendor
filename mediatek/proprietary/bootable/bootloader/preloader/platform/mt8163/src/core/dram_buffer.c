#include "dram_buffer.h"
#include "typedefs.h"
#include "emi.h"

#define MOD "[Dram_Buffer]"
#define DRAM_BASE 0x40000000

dram_buf_t* g_dram_buf = 0;

void init_dram_buffer(){
#if !CFG_FPGA_PLATFORM

	u32 dram_rank_size[4] = {0,0,0,0};
	u32 dram_size = 0;
	u32 structure_size = sizeof(dram_buf_t);
	/*get memory size*/
	get_dram_rank_size(dram_rank_size);
	dram_size= dram_rank_size[0] + dram_rank_size[1] + dram_rank_size[2] + dram_rank_size[3];
	print("%s dram size: 0x%x \n" ,MOD, dram_size);
	print("%s dram_buf_t size: 0x%x \n" ,MOD, structure_size);
	print("%s part_hdr_t size: 0x%x \n" ,MOD, sizeof(part_hdr_t));
	/*allocate dram_buf*/
	//g_dram_buf = DRAM_BASE  + dram_size - (5*1024*1024);
#ifdef SLT
  g_dram_buf = DRAM_BASE + (2*1024*1024*1024)-(5*1024*1024);
#else
  g_dram_buf = DRAM_BASE + 0x2000000;
#endif
	//make sure dram_buffer if move to the head of memory
	print("%s g_dram_buf start addr: 0x%x \n" ,MOD, g_dram_buf);
    #ifdef MTK_EMMC_SUPPORT
	//make sure msdc_gpd_pool and msdc_bd_pool is 64 bytes alignment
	print("%s g_dram_buf->msdc_gpd_pool start addr: 0x%x \n" ,MOD, g_dram_buf->msdc_gpd_pool);
	print("%s g_dram_buf->msdc_bd_pool start addr: 0x%x \n" ,MOD, g_dram_buf->msdc_bd_pool);
    #endif
#else
    g_dram_buf = 0x40C00000;
	print("%s g_dram_buf->nand_hynix_rr_table start addr: 0x%x \n" ,MOD, g_dram_buf->nand_hynix_rr_table);
	print("%s g_dram_buf->lastest_part start addr: 0x%x \n" ,MOD, g_dram_buf->lastest_part);
	print("%s g_dram_buf->bootarg start addr: 0x%x \n" ,MOD, &g_dram_buf->bootarg);
	//print("%s g_dram_buf->msdc_gpd_pool start addr: 0x%x \n" ,MOD, g_dram_buf->msdc_gpd_pool);
	//print("%s g_dram_buf->msdc_bd_pool start addr: 0x%x \n" ,MOD, g_dram_buf->msdc_bd_pool);
#endif

}

