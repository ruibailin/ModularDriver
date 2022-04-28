
/*---------------------------
 * test_app_opr.c
 *  Created on: 2017年7月21日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *
 *
 *
 *
 *
 *---------------------------
 */

#include "../src/test/c_share.h"

#if  IVE_UNIT_TEST

#if  TEST_APP_OPR
#include "../app/2sdl/sdl_basic_fun.h"
#include "../app/2sdl/rgb2yuv.h"
#include <stdio.h>
#include <stdlib.h>

#define	FRM_W	720
#define FRM_H	576
/**************************************************/
#define INPUTFILE1  "./720x576_FourPeople_3_refm.yuv"
#include <assert.h>
#include <errno.h>
#include <string.h>
static void	yuv_get_nfrm(void *buf,int n);
static void	yuv_get_nfrm(void *buf,int n)
{
    FILE *fp;
    int size;
    long offset;

    size=FRM_W*FRM_H;
    offset=size*3;
    offset >>= 2;
    offset *= n;
    fp = fopen(INPUTFILE1, "rb");
    if (fp==NULL)
    {
    	printf("%s, open input file:%s ERR!\n",  __func__,INPUTFILE1);
        printf("ERROR is %s\n", strerror(errno));
    	return;
    }
    if(fseek(fp, offset, SEEK_SET))
    {
    	printf("No %d frame found!\n", n);
        fclose(fp);
    	return;
    }
    if (fread(buf, sizeof(unsigned char),  size, fp)!= size)
    {
       printf("Read n frame error, fp(%p),addr(%p), size(%d)\n", fp, buf,size);
       fclose(fp);
       return;
    }
    fclose(fp);
}
/**************************************************/
static unsigned char *frm_in0,*frm_in1,*frm_out;
#include "../hw_cve/3opr/sw_knl_opr.h"
/**************************************************/
static unsigned char eff[5][5],hco[5][5],vco[5][5];
static void test_knl0_opr()
{
	yuv_get_nfrm(frm_in0,0);
	app_show_string(frm_in0,FRM_W,FRM_H);

	printf("DLT5\n");
	sw_opr_DLT5(frm_out, frm_in0, FRM_W, FRM_H, 0x80);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("DLT3\n");
	sw_opr_DLT3(frm_out, frm_in0, FRM_W, FRM_H, 0x80);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("ERD5\n");
	sw_opr_ERD5(frm_out, frm_in0, FRM_W, FRM_H, 0x80);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("ERD3\n");
	sw_opr_ERD3(frm_out, frm_in0, FRM_W, FRM_H, 0x80);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("FLT\n");
	sw_opr_FLT(frm_out, frm_in0, FRM_W, FRM_H, 0x00,eff);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("MAX\n");
	sw_opr_MAX(frm_out, frm_in0, FRM_W, FRM_H);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("MED\n");
	sw_opr_MED(frm_out, frm_in0, FRM_W, FRM_H);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("MIN\n");
	sw_opr_MIN(frm_out, frm_in0, FRM_W, FRM_H);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("SBL\n");
	sw_opr_SBL(frm_out, frm_in0, FRM_W, FRM_H, 0x00,0x01,0x02,0x03,hco,vco);
	app_show_string(frm_out,FRM_W,FRM_H);
}
/**************************************************/
static  WORD map_table[256];
static void test_knl1_opr()
{
	yuv_get_nfrm(frm_in0,1);
	app_show_string(frm_in0,FRM_W,FRM_H);
	int i;
	for (i = 0; i < 256; i++)
		map_table[i]=(WORD)rand();

	printf("BLK\n");
	sw_opr_BLK(frm_out, frm_in0, FRM_W, FRM_H, 0x01, 0x02);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("HST\n");
	sw_opr_HST(frm_out, frm_in0, FRM_W, FRM_H, 0x00);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("MAP\n");
	sw_opr_MAP(frm_out, frm_in0, FRM_W, FRM_H, 0x00, map_table);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("SUM8\n");
	sw_opr_SUM8(frm_out, frm_in0, FRM_W, FRM_H, 44, 36, 22, 18);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("SUM8 is %d \n",*((int *)frm_out));
	printf("SUM16\n");
	sw_opr_SUM16(frm_out, frm_in0, FRM_W, FRM_H, 0x00, 44, 36, 22, 18);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("SUM16 is %ld\n",*((long *)frm_out));
	printf("TRS8\n");
	sw_opr_TRS8(frm_out, frm_in0, FRM_W, FRM_H, 0x30,0x70,0x00,0x01,0x11,0x22);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("TRS16\n");
	sw_opr_TRS16(frm_out, frm_in0, FRM_W, FRM_H, 0x30,0x70,0x00,0x00,0x01,0x11,0x22);
	app_show_string(frm_out,FRM_W,FRM_H);
}
/**************************************************/
static void test_knl2_opr()
{
	yuv_get_nfrm(frm_in0,2);
	yuv_get_nfrm(frm_in1,3);
	app_show_string(frm_in0,FRM_W,FRM_H);
	app_show_string(frm_in1,FRM_W,FRM_H);
	printf("ADD\n");
	sw_opr_ADD(frm_out, frm_in0, frm_in1,FRM_W, FRM_H, 0x00);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("AND\n");
	sw_opr_AND(frm_out, frm_in0, frm_in1, FRM_W, FRM_H);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("OR\n");
	sw_opr_OR(frm_out, frm_in0, frm_in1, FRM_W, FRM_H);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("SAD\n");
	sw_opr_SAD(frm_out, frm_in0, frm_in1, FRM_W, FRM_H, 0x00);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("SUB\n");
	sw_opr_SUB(frm_out, frm_in0, frm_in1, FRM_W, FRM_H, 0x00);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("VAR\n");
	sw_opr_VAR(frm_out, frm_in0, frm_in1, FRM_W, FRM_H, 0x00, 0x20, 0x40, 88, 72, 44, 36, 22, 18);
	app_show_string(frm_out,FRM_W,FRM_H);
	printf("VAR is %ld \n",*((long *)frm_out));
	printf("XOR\n");
	sw_opr_XOR(frm_out, frm_in0, frm_in1, FRM_W, FRM_H);
	app_show_string(frm_out,FRM_W,FRM_H);
}
#endif
/**************************************************/
void test_app_opr();
void test_app_opr()
{
#if  TEST_APP_OPR
	frm_in0=malloc(FRM_W*FRM_H*2); /*BLK need more*/
	frm_in1=malloc(FRM_W*FRM_H);
	frm_out=malloc(FRM_W*FRM_H);
	sdl_create_window(FRM_W,FRM_H);
	test_knl0_opr();
	test_knl1_opr();
	test_knl2_opr();
	sdl_delete_window();
	free(frm_in0);
	free(frm_in1);
	free(frm_out);
#endif
}
#endif
/* end of test_app_opr.c */
