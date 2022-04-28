/*---------------------------
 * test_hw_reg.c
 *  Created on: Jun 25, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Literally test all functions in ./hw_cve/2reg
 *
 *
 *
 *---------------------------
 */


#include "../src/test/c_share.h"

#if  IVE_UNIT_TEST

#if TEST_HW_REG
#include <stdio.h>
#include <stdlib.h>

/**************************************************/
static void test_hw_top(void);
#include "../hw_cve/2reg/hw_reg_top.h"
static  int t_top[20];
static void test_hw_top(void)
{
	top_ini_base_addr((void *)t_top);
	top_ini_sw_reg();
	top_set_start_reg(0x01);
	top_set_ddr_addr((void *)t_top,(void *)t_top);
	top_set_frm_addr((void *)t_top, (void *)t_top);
	top_set_wb_addr((void *)t_top);
	top_set_img_size(352,288);
	top_set_blk_size(0X10,0X20);
	top_set_blk1_pos(0X10,0X20);
	top_set_blk2_pos(0X10,0X20);
	WORD h,w;
	top_get_img_size(&h,&w);
	DWORD st;
	top_get_irq_state(&st);
	top_wait_cve_done(10000,10);
	top_set_clr_irq_state(0X0001);

	top_set_writeback_id(0x01);
	top_set_frame_id(0x01);
	top_set_lowband_parameter(0x22);
	WORD  cnt;
	top_get_lowband_counter(&cnt);
	void *ptr;
	top_get_read_error_addr(&ptr);
	top_get_write_error_addr(&ptr);
}
/**************************************************/
static void test_hw_knl0(void);
#include "../hw_cve/2reg/hw_reg_knl0.h"
static  int t_knl0[40];
static BYTE co[5][5],hco[5][5],vco[5][5];
static void ini_co(void);
static void ini_co(void)
{

	int ii,jj;
	for(ii=0;ii<5;ii++)
		for(jj=0;jj<5;jj++)
		{
			co[ii][jj]=ii*jj+0x80;
			hco[ii][jj]=ii+jj;
			vco[ii][jj]=ii+jj;
		}
}


static void test_hw_knl0(void)
{
	ini_co();

	knl0_ini_base_addr((void *)t_knl0);
	knl0_ini_sw_reg();

	knl0_set_opr_enabler(0x01);
	knl0_clr_opr_enabler(0x01);

	knl0_set_MED3x3_opr();
	knl0_clr_MED3x3_opr();

	knl0_set_MIN3x3_opr();
	knl0_clr_MIN3x3_opr();

	knl0_set_MAX3x3_opr();
	knl0_clr_MAX3x3_opr();

	knl0_set_ERD3x3_opr();
	knl0_clr_ERD3x3_opr();
	knl0_set_ERD3x3_mode(0x01);

	knl0_set_ERD3x3_opr();
	knl0_clr_ERD3x3_opr();
	knl0_set_ERD5x5_mode(0x01);

	knl0_set_DLT3x3_opr();
	knl0_clr_DLT3x3_opr();
	knl0_set_DLT3x3_mode(0x01);

	knl0_set_DLT5x5_opr();
	knl0_clr_DLT5x5_opr();
	knl0_set_DLT5x5_mode(0x01);

	knl0_set_FLT_opr();
	knl0_clr_FLT_opr();
	knl0_set_FLT_power(0x02);
	knl0_set_FLT_coeff(co);

	knl0_set_SBL_opr();
	knl0_clr_SBL_opr();
	knl0_set_SBL_mode(0x01,0x02);
	knl0_set_SBL_mode_output(0x01);
	knl0_set_SBL_mode_angle(0x02);
	knl0_set_SBL_power(0x01, 0x02);
	knl0_set_SBL_power_ang(0x01);
	knl0_set_SBL_power_mag(0x02);
	knl0_set_SBL_hcoeff(hco);
	knl0_set_SBL_vcoeff(vco);
}
/**************************************************/
static void test_hw_knl1(void);
#include "../hw_cve/2reg/hw_reg_knl1.h"
static  int t_knl1[40];
static void test_hw_knl1(void)
{
	knl1_ini_base_addr((void *)t_knl1);
	knl1_ini_sw_reg();

	knl1_set_opr_enabler(0x04);
	knl1_clr_opr_enabler(0x04);

	knl1_set_MAP_opr();
	knl1_set_MAP_mode(0x01);
	knl1_set_MAP_write(0x40,0x01);
	knl1_clr_MAP_opr();

	knl1_set_HST_opr();
	knl1_set_HST_mode(0x01);
	knl1_clr_HST_opr();

	knl1_set_TRS8_opr();
	knl1_set_TRS8_mode(0x01);
	knl1_set_TRS8_trs(0x10,0x20);
	knl1_set_TRS8_value(0x10,0x30,0x50);
	knl1_clr_TRS8_opr();

	knl1_set_SUM8_opr();
	int dout;
	knl1_get_SUM8_output(&dout);
	knl1_clr_SUM8_opr();

	knl1_set_SUM16_opr();
	knl1_set_SUM16_mode(0x01);
	long lout;
	knl1_get_SUM16_output(&lout);
	knl1_clr_SUM16_opr();

	knl1_set_TRS16_opr();
	knl1_set_TRS16_mode_sign(0x01);
	knl1_set_TRS16_mode_value(0x01);
	knl1_set_TRS16_trs(0x100,0x300);
	knl1_set_TRS16_value(0x10,0x30,0x50);
	knl1_clr_TRS16_opr();

	knl1_set_BLK16_opr();
	knl1_set_BLK16_mode(0x01);
	knl1_set_BLK16_power(0x02);
	knl1_clr_BLK16_opr();

}
/**************************************************/
static void test_hw_knl2(void);
#include "../hw_cve/2reg/hw_reg_knl2.h"
static  int t_knl2[40];
static void test_hw_knl2(void)
{
	knl2_ini_base_addr((void *)t_knl2);
	knl2_ini_sw_reg();

	knl2_set_opr_enabler(0x01);
	knl2_clr_opr_enabler(0x01);

	knl2_set_SAD_opr();
	knl2_set_SAD_mode(0x01);
	knl2_clr_SAD_opr();

	knl2_set_VAR_opr();
	knl2_set_VAR_mode(0x01);
	knl2_set_VAR_input(0x01, 0x01);
	long lout;
	knl2_get_VAR_output(&lout);
	knl2_clr_VAR_opr();

	knl2_set_SUB_opr();
	knl2_set_SUB_mode(0x01);
	knl2_clr_SUB_opr();

	knl2_set_ADD_opr();
	knl2_set_ADD_mode(0x01);
	knl2_clr_ADD_opr();

	knl2_set_XOR_opr();
	knl2_clr_XOR_opr();

	knl2_set_OR_opr();
	knl2_clr_OR_opr();

	knl2_set_AND_opr();
	knl2_clr_AND_opr();
}
#endif
/**************************************************/
void test_hw_reg(void);
void test_hw_reg(void)
{
#if TEST_HW_REG
	test_hw_top();
	test_hw_knl0();
	test_hw_knl1();
	test_hw_knl2();
#endif
}

#endif

/* end of test_hw_reg.c */
