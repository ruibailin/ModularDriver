
/*---------------------------
 * test_hw_cve.c
 *  Created on: 2017年8月15日
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
#include "../src/code/hw_cve/3opr/hw_knl_opr.h"
/**************************************************/
static	void ini_FLT5x5_coeff(char coeff[][5]);
static	void ini_FLT5x5_coeff(char coeff[][5])
{
/*	coeff[0][0] = 1;		coeff[0][1] = 2;		coeff[0][2] = 0;		coeff[0][3] = -2;		coeff[0][4] = -1;
	coeff[1][0] = 4;		coeff[1][1] = 8;		coeff[1][2] = 0;		coeff[1][3] = -8;		coeff[1][4] = -4;
	coeff[2][0] = 6;		coeff[2][1] = 12;		coeff[2][2] = 0;		coeff[2][3] = -12;		coeff[2][4] = -6;
	coeff[3][0] = 4;		coeff[3][1] = 8;		coeff[3][2] = 0;		coeff[3][3] = -8;		coeff[3][4] = -4;
	coeff[4][0] = 1;		coeff[4][1] = 2;		coeff[4][2] = 0;		coeff[4][3] = -2;		coeff[4][4] = -1;
*/
	coeff[0][0] = -1;		coeff[0][1] = -4;		coeff[0][2] = -6;		coeff[0][3] = -4;		coeff[0][4] = -1;
	coeff[1][0] = -2;		coeff[1][1] = -8;		coeff[1][2] = -12;		coeff[1][3] = -8;		coeff[1][4] = -2;
	coeff[2][0] = 0;		coeff[2][1] = 0;		coeff[2][2] = 0;		coeff[2][3] = 0;		coeff[2][4] = 0;
	coeff[3][0] = 2;		coeff[3][1] = 8;		coeff[3][2] = 12;		coeff[3][3] = 8;		coeff[3][4] = 2;
	coeff[4][0] = 1;		coeff[4][1] = 4;		coeff[4][2] = 6;		coeff[4][3] = 4;		coeff[4][4] = 1;

}
/**************************************************/
static	void ini_SBL5x5_coeff(char hCoeff[][5],char vCoeff[][5]);
static	void ini_SBL5x5_coeff(char hCoeff[][5],char vCoeff[][5])
{
	hCoeff[0][0] = 1;		hCoeff[0][1] = 2;		hCoeff[0][2] = 0;		hCoeff[0][3] = -2;		hCoeff[0][4] = -1;
	hCoeff[1][0] = 4;		hCoeff[1][1] = 8;		hCoeff[1][2] = 0;		hCoeff[1][3] = -8;		hCoeff[1][4] = -4;
	hCoeff[2][0] = 6;		hCoeff[2][1] = 12;		hCoeff[2][2] = 0;		hCoeff[2][3] = -12;		hCoeff[2][4] = -6;
	hCoeff[3][0] = 4;		hCoeff[3][1] = 8;		hCoeff[3][2] = 0;		hCoeff[3][3] = -8;		hCoeff[3][4] = -4;
	hCoeff[4][0] = 1;		hCoeff[4][1] = 2;		hCoeff[4][2] = 0;		hCoeff[4][3] = -2;		hCoeff[4][4] = -1;

	vCoeff[0][0] = -1;		vCoeff[0][1] = -4;		vCoeff[0][2] = -6;		vCoeff[0][3] = -4;		vCoeff[0][4] = -1;
	vCoeff[1][0] = -2;		vCoeff[1][1] = -8;		vCoeff[1][2] = -12;		vCoeff[1][3] = -8;		vCoeff[1][4] = -2;
	vCoeff[2][0] = 0;		vCoeff[2][1] = 0;		vCoeff[2][2] = 0;		vCoeff[2][3] = 0;		vCoeff[2][4] = 0;
	vCoeff[3][0] = 2;		vCoeff[3][1] = 8;		vCoeff[3][2] = 12;		vCoeff[3][3] = 8;		vCoeff[3][4] = 2;
	vCoeff[4][0] = 1;		vCoeff[4][1] = 4;		vCoeff[4][2] = 6;		vCoeff[4][3] = 4;		vCoeff[4][4] = 1;
}
/**************************************************/
static unsigned char eff[5][5],hco[5][5],vco[5][5];
static void test_knl0_opr()
{
	printf("DLT5\n");
	hw_opr_DLT5(frm_out, frm_in0, FRM_W, FRM_H, 0x80);
	printf("DLT3\n");
	hw_opr_DLT3(frm_out, frm_in0, FRM_W, FRM_H, 0x80);
	printf("ERD5\n");
	hw_opr_ERD5(frm_out, frm_in0, FRM_W, FRM_H, 0x80);
	printf("ERD3\n");
	hw_opr_ERD3(frm_out, frm_in0, FRM_W, FRM_H, 0x80);
	printf("FLT\n");
	ini_FLT5x5_coeff(eff);
	hw_opr_FLT(frm_out, frm_in0, FRM_W, FRM_H, 0x00,eff);
	printf("MAX\n");
	hw_opr_MAX(frm_out, frm_in0, FRM_W, FRM_H);
	printf("MED\n");
	hw_opr_MED(frm_out, frm_in0, FRM_W, FRM_H);
	printf("MIN\n");
	hw_opr_MIN(frm_out, frm_in0, FRM_W, FRM_H);
	printf("SBL\n");
	ini_SBL5x5_coeff(hco,vco);
	hw_opr_SBL(frm_out, frm_in0, FRM_W, FRM_H, 0x00,0x01,0x02,0x03,hco,vco);
}
/**************************************************/
static  WORD map_table[256];
static void test_knl1_opr()
{
	int i;
	for (i = 0; i < 256; i++)
		map_table[i]=(WORD)rand();

	printf("BLK\n");
	hw_opr_BLK(frm_out, frm_in0, FRM_W, FRM_H, 0x01, 0x02);
	printf("HST\n");
	hw_opr_HST(frm_out, frm_in0, FRM_W, FRM_H, 0x00);
	printf("MAP\n");
	hw_opr_MAP(frm_out, frm_in0, FRM_W, FRM_H, 0x00, map_table);
	printf("SUM8\n");
	hw_opr_SUM8(frm_out, frm_in0, FRM_W, FRM_H, 44, 36, 22, 18);
	printf("SUM8 is %d \n",*((int *)frm_out));
	printf("SUM16\n");
	hw_opr_SUM16(frm_out, frm_in0, FRM_W, FRM_H, 0x00, 44, 36, 22, 18);
	printf("SUM16 is %ld\n",*((long *)frm_out));
	printf("TRS8\n");
	hw_opr_TRS8(frm_out, frm_in0, FRM_W, FRM_H, 0x30,0x70,0x00,0x01,0x11,0x22);
	printf("TRS16\n");
	hw_opr_TRS16(frm_out, frm_in0, FRM_W, FRM_H, 0x30,0x70,0x00,0x00,0x01,0x11,0x22);
}
/**************************************************/
static void test_knl2_opr()
{
	printf("ADD\n");
	hw_opr_ADD(frm_out, frm_in0, frm_in1,FRM_W, FRM_H, 0x00);
	printf("AND\n");
	hw_opr_AND(frm_out, frm_in0, frm_in1, FRM_W, FRM_H);
	printf("OR\n");
	hw_opr_OR(frm_out, frm_in0, frm_in1, FRM_W, FRM_H);
	printf("SAD\n");
	hw_opr_SAD(frm_out, frm_in0, frm_in1, FRM_W, FRM_H, 0x00);
	printf("SUB\n");
	hw_opr_SUB(frm_out, frm_in0, frm_in1, FRM_W, FRM_H, 0x00);
	printf("VAR\n");
	hw_opr_VAR(frm_out, frm_in0, frm_in1, FRM_W, FRM_H, 0x00, 0x20, 0x40, 88, 72, 44, 36, 22, 18);
	printf("VAR is %ld \n",*((long *)frm_out));
	printf("XOR\n");
	hw_opr_XOR(frm_out, frm_in0, frm_in1, FRM_W, FRM_H);
}

/**************************************************/
static unsigned char *vir_in0,*vir_in1,*vir_out;
#include "../src/code/app/9icp/zx_icp.h"
void test_ini_data()
{
	icp_frm_alloc_mem(0,FRM_W*FRM_H);
	vir_in0=icp_frm_get_vir_addr(0);
	yuv_get_nfrm(vir_in0,0);
	frm_in0=(void *)icp_frm_get_phy_addr(0);
	printf("Frame 0 virtual address is 0x%x,physical address is 0x%x",vir_in0,frm_in0);

	icp_frm_alloc_mem(1,FRM_W*FRM_H);
	vir_in1=icp_frm_get_vir_addr(1);
	yuv_get_nfrm(vir_in1,1);
	frm_in1=(void *)icp_frm_get_phy_addr(1);
	printf("Frame 1 virtual address is 0x%x,physical address is 0x%x",vir_in1,frm_in1);

	icp_frm_alloc_mem(2,FRM_W*FRM_H);
	vir_out=icp_frm_get_vir_addr(2);
	frm_out=(void *)icp_frm_get_phy_addr(2);
	printf("Frame out virtual address is 0x%x,physical address is 0x%x",vir_out,frm_out);
}


void test_hw_cve(void);
void test_hw_cve(void)
{
#if TEST_HW_CVE
	ini_hw_cve();
	test_ini_data();

	test_knl0_opr();
	test_knl1_opr();
	test_knl2_opr();

#endif
}
#endif
/* end of test_hw_cve.c */
