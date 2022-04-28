/*---------------------------
 * test_sw_opr.c
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

#if TEST_SW_OPR

#include <stdio.h>
#include <stdlib.h>

#include "../hw_cve/3opr/sw_knl_opr.h"

static BYTE frm_out[176*144],frm_in0[176*144],frm_in1[176*144];
static char eff[5][5],hco[5][5],vco[5][5];
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
static void test_sw_opr_knl0(void);
static void test_sw_opr_knl0(void)
{
	sw_opr_DLT5(frm_out, frm_in0, 176, 144, 0x00);
	sw_opr_DLT3(frm_out, frm_in0, 176, 144, 0x00);
	sw_opr_ERD5(frm_out, frm_in0, 176, 144, 0x00);
	sw_opr_ERD3(frm_out, frm_in0, 176, 144, 0x00);
	sw_opr_FLT(frm_out, frm_in0, 176, 144, 0x00,eff);
	sw_opr_MAX(frm_out, frm_in0, 176, 144);
	sw_opr_MED(frm_out, frm_in0, 176, 144);
	sw_opr_MIN(frm_out, frm_in0, 176, 144);
	sw_opr_SBL(frm_out, frm_in0, 176, 144, 0x00,0x01,0x02,0x03,hco,vco);
}
/**************************************************/
static  WORD map_table[256];
static void test_sw_opr_knl1(void);
static void test_sw_opr_knl1(void)
{
	int i;
	for (i = 0; i < 256; i++)
		map_table[i]=(WORD)rand();

	sw_opr_BLK(frm_out, frm_in0, 176, 144, 0x01, 0x02);
	sw_opr_HST(frm_out, frm_in0, 176, 144, 0x00);
	sw_opr_MAP(frm_out, frm_in0, 176, 144, 0x00, map_table);
	sw_opr_SUM8(frm_out, frm_in0, 176, 144, 44, 36, 22, 18);
	sw_opr_SUM16(frm_out, frm_in0, 176, 144, 0x00, 44, 36, 22, 18);
	sw_opr_TRS8(frm_out, frm_in0, 176, 144, 0x30,0x70,0x00,0x01,0x11,0x22);
	sw_opr_TRS16(frm_out, frm_in0, 176, 144, 0x30,0x70,0x00,0x00,0x01,0x11,0x22);
}

/**************************************************/
static void test_sw_opr_knl2(void);
static void test_sw_opr_knl2(void)
{
	sw_opr_ADD(frm_out, frm_in0, frm_in1,176, 144, 0x00);
	sw_opr_AND(frm_out, frm_in0, frm_in1, 176, 144);
	sw_opr_OR(frm_out, frm_in0, frm_in1, 176, 144);
	sw_opr_SAD(frm_out, frm_in0, frm_in1, 176, 144, 0x00);
	sw_opr_SUB(frm_out, frm_in0, frm_in1, 176, 144, 0x00);
	sw_opr_VAR(frm_out, frm_in0, frm_in1, 176, 144, 0x00, 0x20, 0x40, 88, 72, 44, 36, 22, 18);
	sw_opr_XOR(frm_out, frm_in0, frm_in1, 176, 144);
}
#endif

/**************************************************/
void test_sw_opr(void);
void test_sw_opr(void)
{
#if TEST_SW_OPR
	test_ini_data();
	test_sw_opr_knl0();
	test_sw_opr_knl1();
	test_sw_opr_knl2();
#endif
}

#endif
/* end of test_sw_opr.c */
