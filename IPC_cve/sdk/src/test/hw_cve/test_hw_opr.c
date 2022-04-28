/*---------------------------
 * test_hw_opr.c
 *  Created on: Jun 25, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Literally test all functions in ./hw_cve/3opr
 *
 *
 *
 *---------------------------
 */


#include "../src/test/c_share.h"

#if  IVE_UNIT_TEST

#if TEST_HW_OPR
#include <stdio.h>
#include <stdlib.h>
static BYTE frm_out[176*144],frm_in0[176*144],frm_in1[176*144];
static BYTE eff[5][5],hco[5][5],vco[5][5];
#include "../hw_cve/3opr/hw_knl_opr.h"
/**************************************************/
static void test_ini_data(void);
static void test_ini_data(void)
{
	int i,j,k;
	k=0;
	for (i = 0; i < 144; i++)
		for (j = 0; j < 176; j++)
		{
			frm_in0[k]=(BYTE)rand();
			frm_in1[k]=(BYTE)rand();
			k++;
		}
	for (i = 0; i < 5; i++)
		for (j = 0; j < 5; j++)
		{
			eff[i][j]=(BYTE)rand();
			hco[i][j]=(BYTE)rand();
			vco[i][j]=(BYTE)rand();
		}
}
/**************************************************/
static void test_hw_opr_top(void);
#include "../hw_cve/2reg/hw_reg_top.h"
static  int t_top[20];
static void test_hw_opr_top(void)
{
	top_ini_base_addr((void *)t_top);
	top_ini_sw_reg();

	opr_set_out_para(frm_out);
	opr_set_frm_para(frm_in0, frm_in1, 176, 144);
	opr_set_blk_para(88, 72, 44, 36, 22, 18);
	opr_set_cve_run();
	opr_clr_cve_run();
	opr_is_cve_done();
	opr_is_cve_error();
}

/**************************************************/
static void test_hw_opr_knl0(void);
#include "../hw_cve/2reg/hw_reg_knl0.h"
static  int t_knl0[40];
static void test_hw_opr_knl0(void)
{
	knl0_ini_base_addr((void *)t_knl0);
	knl0_ini_sw_reg();

	opr_sel_DLT5(0x00);
	opr_rev_DLT5();
	hw_opr_DLT5(frm_out, frm_in0, 176, 144, 0x00);

	opr_sel_DLT3(0x00);
	opr_rev_DLT3();
	hw_opr_DLT3(frm_out, frm_in0, 176, 144, 0x00);

	opr_sel_ERD5(0x00);
	opr_rev_ERD5();
	hw_opr_ERD5(frm_out, frm_in0, 176, 144, 0x00);

	opr_sel_ERD3(0x00);
	opr_rev_ERD3();
	hw_opr_ERD3(frm_out, frm_in0, 176, 144, 0x00);

	opr_sel_FLT(0x01,eff);
	opr_rev_FLT();
	hw_opr_FLT(frm_out, frm_in0, 176, 144, 0x00,eff);

	opr_sel_MAX();
	opr_rev_MAX();
	hw_opr_MAX(frm_out, frm_in0, 176, 144);

	opr_sel_MED();
	opr_rev_MED();
	hw_opr_MED(frm_out, frm_in0, 176, 144);

	opr_sel_MIN();
	opr_rev_MIN();
	hw_opr_MIN(frm_out, frm_in0, 176, 144);

	opr_sel_SBL(0x00,0x01,0x02,0x03,hco,vco);
	opr_rev_SBL();
	hw_opr_SBL(frm_out, frm_in0, 176, 144, 0x00,0x01,0x02,0x03,hco,vco);
}
/**************************************************/
static void test_hw_opr_knl1(void);
#include "../hw_cve/2reg/hw_reg_knl1.h"
static  int t_knl1[40];
static  WORD map_table[256];
static void test_hw_opr_knl1(void)
{
	int i;
	for (i = 0; i < 256; i++)
		map_table[i]=(WORD)rand();

	knl1_ini_base_addr((void *)t_knl1);
	knl1_ini_sw_reg();

	opr_sel_BLK(0x01, 0x02);
	opr_rev_BLK();
	hw_opr_BLK(frm_out, frm_in0, 176, 144, 0x01, 0x02);

	opr_sel_HST(0x00);
	opr_rev_HST();
	hw_opr_HST(frm_out, frm_in0, 176, 144, 0x00);

	opr_sel_MAP(0x00, map_table);
	opr_rev_MAP();
	hw_opr_MAP(frm_out, frm_in0, 176, 144, 0x00, map_table);

	opr_sel_SUM8();
	int dout;
	opr_get_SUM8(&dout);
	opr_rev_SUM8();
	hw_opr_SUM8(frm_out, frm_in0, 176, 144, 44, 36, 22, 18);

	opr_sel_SUM16(0x00);
	long qout;
	opr_get_SUM16(&qout);
	opr_rev_SUM16();
	hw_opr_SUM16(frm_out, frm_in0, 176, 144, 0x00, 44, 36, 22, 18);

	opr_sel_TRS8(0x00,0x30,0x70,0x01,0x11,0x22);
	opr_rev_TRS8();
	hw_opr_TRS8(frm_out, frm_in0, 176, 144, 0x00,0x30,0x70,0x01,0x11,0x22);

	opr_sel_TRS16(0x00,0x30,0x00,0x70,0x01,0x11,0x22);
	opr_rev_TRS16();
	hw_opr_TRS16(frm_out, frm_in0, 176, 144, 0x00,0x30,0x00,0x70,0x01,0x11,0x22);
}

/**************************************************/
static void test_hw_opr_knl2(void);
#include "../hw_cve/2reg/hw_reg_knl2.h"
static  int t_knl2[40];
static void test_hw_opr_knl2(void)
{
	knl2_ini_base_addr((void *)t_knl2);
	knl2_ini_sw_reg();

	opr_sel_ADD(0x00);
	opr_rev_ADD();
	hw_opr_ADD(frm_out, frm_in0, frm_in1,176, 144, 0x00);

	opr_sel_AND();
	opr_rev_AND();
	hw_opr_AND(frm_out, frm_in0, frm_in1, 176, 144);

	opr_sel_OR();
	opr_rev_OR();
	hw_opr_OR(frm_out, frm_in0, frm_in1, 176, 144);

	opr_sel_SAD(0x00);
	opr_rev_SAD();
	hw_opr_SAD(frm_out, frm_in0, frm_in1, 176, 144, 0x00);

	opr_sel_SUB(0x00);
	opr_rev_SUB();
	hw_opr_SUB(frm_out, frm_in0, frm_in1, 176, 144, 0x00);

	opr_sel_VAR(0x00,0x20, 0x40);
	long	qout;
	opr_get_VAR(&qout);
	opr_rev_VAR();
	hw_opr_VAR(frm_out, frm_in0, frm_in1, 176, 144, 0x00, 0x20, 0x40, 88, 72, 44, 36, 22, 18);

	opr_sel_XOR();
	opr_rev_XOR();
	hw_opr_XOR(frm_out, frm_in0, frm_in1, 176, 144);

}
#endif

/**************************************************/
void test_hw_opr(void);
void test_hw_opr(void)
{
#if TEST_HW_OPR
	test_ini_data();
	test_hw_opr_top();
	test_hw_opr_knl0();
	test_hw_opr_knl1();
	test_hw_opr_knl2();
#endif
}

#endif
/* end of test_hw_opr.c */
