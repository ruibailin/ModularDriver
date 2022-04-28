/*---------------------------
 * test_sw_blk.c
 *  Created on: Jun 18, 2017
 *      Author: Bailin Rui
 *          ×÷Õß£ºÜÇ°ØÁÖ
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */

#if  IVE_UNIT_TEST

#if TEST_SW_BLK
#include <stdio.h>
#include <stdlib.h>

#include "c_share.h"
#include "../sw_cve/2blk/sw_knl_base.h"

static unsigned char frm_out[16*12],frm_in[16*12];
static char blk5[5][5],eff5[5][5];
static char blk3[3][3],eff3[5][5];

/**************************************************/
static void ini_frame(void);
static void ini_frame(void)
{

	int ii,jj,kk;

	kk=0;
	for(ii=0;ii<16;ii++)
		for(jj=0;jj<12;jj++)
		{
		frm_in[kk]=(BYTE)rand();
		kk++;
		}

	for(ii=0;ii<5;ii++)
		for(jj=0;jj<5;jj++)
			eff5[ii][jj]=(BYTE)rand();

	for(ii=0;ii<3;ii++)
		for(jj=0;jj<3;jj++)
			eff3[ii][jj]=(BYTE)rand();

}

/**************************************************/
static void test_get_blk(void);
static void test_get_blk(void)
{
	int ii,jj,kk;

	for(ii=0;ii<16;ii++)
		for(jj=0;jj<12;jj++)
		{
			kk=knl_get_blk5x5(frm_in,blk5,ii,jj,16,12);
			kk=knl_conv_blk5x5(blk5,eff5);
			kk=knl_get_blk3x3(frm_in,blk3,ii,jj,16,12);
			kk=knl_conv_blk3x3(blk3,eff3);
		}
}

/**************************************************/
static void test_copy_set(void);
static void test_copy_set(void)
{
	knl_copy_hori(frm_out,frm_in,16, 0);
	knl_copy_hori(frm_out,frm_in,16, 11);

	knl_copy_vert(frm_out,frm_in,16, 0, 12);
	knl_copy_vert(frm_out,frm_in,16, 15, 12);

	knl_set_hori(frm_out,0x01,16, 1);
	knl_set_hori(frm_out,0x0A,16, 10);

	knl_set_vert(frm_out,0x02,16, 1, 12);
	knl_set_vert(frm_out,0x0E,16, 14, 12);

}
#endif

/**************************************************/
void test_sw_blk(void);
void test_sw_blk(void)
{
#if TEST_SW_BLK
	ini_frame();
	test_get_blk();
	test_copy_set();
#endif
}

#endif
/* end of test_sw_blk.c */
