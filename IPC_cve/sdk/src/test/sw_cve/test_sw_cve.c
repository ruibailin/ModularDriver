/*---------------------------
 * test_sh_cve.c
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

#if TEST_SW_CVE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
#include "../sw_cve/4reg/sw_reg_top.h"
void wait_sw_cve_clr_irq(viod);
void wait_sw_cve_clr_irq(viod)
{
	DWORD bit;
	for(;;)
	{
		top_get_clr_irq_state(&bit);
		if(bit == 0)
			break;
		usleep(100000);
	}
}

/**************************************************/
static void test_hw_opr_knl0(void);
#include "../hw_cve/2reg/hw_reg_knl0.h"
static void test_hw_opr_knl0(void)
{
	hw_opr_DLT5(frm_out, frm_in0, 176, 144, 0x00);
	wait_sw_cve_clr_irq();
	hw_opr_DLT3(frm_out, frm_in0, 176, 144, 0x00);
	wait_sw_cve_clr_irq();
	hw_opr_ERD5(frm_out, frm_in0, 176, 144, 0x00);
	wait_sw_cve_clr_irq();
	hw_opr_ERD3(frm_out, frm_in0, 176, 144, 0x00);
	wait_sw_cve_clr_irq();
	hw_opr_FLT(frm_out, frm_in0, 176, 144, 0x00,eff);
	wait_sw_cve_clr_irq();
	hw_opr_MAX(frm_out, frm_in0, 176, 144);
	wait_sw_cve_clr_irq();
	hw_opr_MED(frm_out, frm_in0, 176, 144);
	wait_sw_cve_clr_irq();
	hw_opr_MIN(frm_out, frm_in0, 176, 144);
	wait_sw_cve_clr_irq();
	hw_opr_SBL(frm_out, frm_in0, 176, 144, 0x00,0x01,0x02,0x03,hco,vco);
	wait_sw_cve_clr_irq();
}
/**************************************************/
static void test_hw_opr_knl1(void);
#include "../hw_cve/2reg/hw_reg_knl1.h"
static  WORD map_table[256];
static void test_hw_opr_knl1(void)
{
	int i;
	for (i = 0; i < 256; i++)
		map_table[i]=(WORD)rand();

	hw_opr_BLK(frm_out, frm_in0, 176, 144, 0x01, 0x02);
	wait_sw_cve_clr_irq();
	hw_opr_HST(frm_out, frm_in0, 176, 144, 0x00);
	wait_sw_cve_clr_irq();
	hw_opr_MAP(frm_out, frm_in0, 176, 144, 0x00, map_table);
	wait_sw_cve_clr_irq();
	hw_opr_SUM8(frm_out, frm_in0, 176, 144, 44, 36, 22, 18);
	int dout;
	opr_get_SUM8(&dout);
	wait_sw_cve_clr_irq();
	hw_opr_SUM16(frm_out, frm_in0, 176, 144, 0x00, 44, 36, 22, 18);
	long qout;
	opr_get_SUM16(&qout);
	wait_sw_cve_clr_irq();
	hw_opr_TRS8(frm_out, frm_in0, 176, 144, 0x00,0x30,0x70,0x01,0x11,0x22);
	wait_sw_cve_clr_irq();
	hw_opr_TRS16(frm_out, frm_in0, 176, 144, 0x00,0x30,0x00,0x70,0x01,0x11,0x22);
	wait_sw_cve_clr_irq();
}

/**************************************************/
static void test_hw_opr_knl2(void);
#include "../hw_cve/2reg/hw_reg_knl2.h"
static void test_hw_opr_knl2(void)
{
	hw_opr_ADD(frm_out, frm_in0, frm_in1,176, 144, 0x00);
	wait_sw_cve_clr_irq();
	hw_opr_AND(frm_out, frm_in0, frm_in1, 176, 144);
	wait_sw_cve_clr_irq();
	hw_opr_OR(frm_out, frm_in0, frm_in1, 176, 144);
	wait_sw_cve_clr_irq();
	hw_opr_SAD(frm_out, frm_in0, frm_in1, 176, 144, 0x00);
	wait_sw_cve_clr_irq();
	hw_opr_SUB(frm_out, frm_in0, frm_in1, 176, 144, 0x00);
	wait_sw_cve_clr_irq();
	hw_opr_VAR(frm_out, frm_in0, frm_in1, 176, 144, 0x00, 0x20, 0x40, 88, 72, 44, 36, 22, 18);
	long	qout;
	opr_get_VAR(&qout);
	wait_sw_cve_clr_irq();
	hw_opr_XOR(frm_out, frm_in0, frm_in1, 176, 144);
	wait_sw_cve_clr_irq();
}
extern void ini_sw_cve(void);
#endif
/**************************************************/
void test_sw_cve(void);
void test_sw_cve(void)
{
#if TEST_SW_CVE
	ini_sw_cve();
	test_ini_data();
	for(;;)
	{
		test_hw_opr_knl0();
		test_hw_opr_knl1();
		test_hw_opr_knl2();
	}
#endif
}
#endif
/* end of test_sh_cve.c */
