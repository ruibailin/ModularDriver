/*---------------------------
 * test_sw_reg.c
 *  Created on: Jun 25, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#include "../src/test/c_share.h"

#if  IVE_UNIT_TEST

#if TEST_SW_REG
#include <stdio.h>
#include <stdlib.h>

#include "../hw_cve/2reg/hw_reg_knl.h"
#include "../hw_cve/2reg/hw_reg_top.h"

#include "../sw_cve/4reg/sw_reg_knl.h"
#include "../sw_cve/4reg/sw_reg_top.h"

/**************************************************/
static void test_sw_top(void);
static void test_sw_top(void)
{
	void *top;
	top_get_base_addr(&top);
	top_ini_hw_reg();

	top_ini_base_addr(top);

	DWORD state;
	top_get_start_reg(&state);

	void *start, *end;
	top_get_ddr_addr(&start,&end);
	void *frm1, *frm2;
	top_get_frm_addr(&frm1, &frm2);
	void *wb;
	top_get_wb_addr(&wb);
	WORD w,h,x,y;
	top_get_img_size(&w,&h);
	top_get_blk_size(&w,&h);
	top_get_blk1_pos(&x,&y);
	top_get_blk2_pos(&x,&y);
	top_set_irq_state(state);
	top_set_cve_done();
	top_set_cve_undone();

	DWORD bit;
	top_get_clr_irq_state(&bit);
	top_set_clr_irq_state(bit);

	BYTE id;
	top_get_writeback_id(&id);
	top_get_frame_id(&id);

	WORD para;
	top_get_lowband_parameter(&para);
	top_set_lowband_counter(para);

	void *addr;
	addr=0x00;
	top_set_read_error_addr(addr);
	top_set_write_error_addr(addr);
}

/**************************************************/
static void test_sw_knl0(void);
static void test_sw_knl0(void)
{
	BYTE co[5][5],hco[5][5],vco[5][5];

	void *knl0;
	knl0_get_base_addr(&knl0);
	knl0_ini_hw_reg();
	knl0_ini_base_addr(knl0);

	DWORD opr;
	knl0_get_opr_enabler(&opr);

	int ctrl;
	knl0_get_ERD5x5_ctrl(&ctrl);
	knl0_get_ERD3x3_ctrl(&ctrl);
	knl0_get_DLT5x5_ctrl(&ctrl);
	knl0_get_DLT3x3_ctrl(&ctrl);
	knl0_get_FLT_ctrl(&ctrl);
	knl0_get_FLT_coeff(co);
	knl0_get_SBL_ctrl(&ctrl);
	knl0_get_SBL_hcoeff(hco);
	knl0_get_SBL_vcoeff(vco);
}

/**************************************************/
static void test_sw_knl1(void);
static void test_sw_knl1(void)
{
	void *knl1;
	knl1_get_base_addr(&knl1);
	knl1_ini_hw_reg();
	knl1_ini_base_addr(knl1);

	DWORD opr;
	knl1_get_opr_enabler(&opr);

	int ctrl;
	knl1_get_MAP_ctrl(&ctrl);
	WORD data;
	BYTE addr;
	knl1_get_MAP_write(&data,&addr);
	knl1_get_HST_ctrl(&ctrl);
	knl1_get_TRS8_ctrl0(&ctrl);
	knl1_get_TRS8_ctrl1(&ctrl);
	DWORD output;
	output=0x1000;
	knl1_set_SUM8_output(output);
	knl1_get_SUM16_ctrl(&ctrl);
	knl1_set_SUM16_output((long)output);
	knl1_get_TRS16_ctrl0(&ctrl);
	knl1_get_TRS16_ctrl1(&ctrl);
	knl1_get_BLK16_ctrl(&ctrl);
}

/**************************************************/
static void test_sw_knl2(void);
static void test_sw_knl2(void)
{
	void *knl2;
	knl2_get_base_addr(&knl2);
	knl2_ini_hw_reg();
	knl2_ini_base_addr(knl2);

	DWORD opr;
	knl2_get_opr_enabler(&opr);
	int ctrl;
	knl2_get_SAD_ctrl(&ctrl);
	knl2_get_VAR_ctrl(&ctrl);
	QWORD output;
	output=0x1000;
	knl2_set_VAR_output(output);
	knl2_get_SUB_ctrl(&ctrl);
	knl2_get_ADD_ctrl(&ctrl);
}
#endif

/**************************************************/
void test_sw_reg(void);
void test_sw_reg(void)
{
#if TEST_SW_REG
	test_sw_top();
	test_sw_knl0();
	test_sw_knl1();
	test_sw_knl2();
#endif
}

#endif
/* end of test_sw_reg.c */
