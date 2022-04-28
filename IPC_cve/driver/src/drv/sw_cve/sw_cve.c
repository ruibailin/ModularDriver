/*---------------------------
 * sw_cve.c
 *  Created on: Jun 27, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#include "../code/sw_cve/4reg/sw_reg_top.h"
#include "../code/sw_cve/c_share.h"
#include "3opr/sw_knl0_opr.h"
/**************************************************/
#define	OPR_MED3x3_EN		((DWORD)0x00000001<<8)
#define	OPR_MIN3x3_EN		((DWORD)0x00000001<<7)
#define	OPR_MAX3x3_EN		((DWORD)0x00000001<<6)
#define	OPR_DLT3x3_EN		((DWORD)0x00000001<<5)
#define	OPR_ERD3x3_EN		((DWORD)0x00000001<<4)
#define	OPR_DLT5x5_EN		((DWORD)0x00000001<<3)
#define	OPR_ERD5x5_EN		((DWORD)0x00000001<<2)
#define	OPR_SBL5x5_EN		((DWORD)0x00000001<<1)
#define	OPR_FLT5x5_EN		((DWORD)0x00000001<<0)
#include "../code/sw_cve/4reg/sw_reg_knl0.h"
static void sw_cve_knl0_opr(DWORD state);
static void sw_cve_knl0_opr(DWORD state)
{
	BYTE *out, *in0, *in1;
	int width, height;
	top_get_wb_addr(&out);
	top_get_frm_addr(&in0, &in1);
	top_get_img_size(&width, &height);

	int ctrl;
	switch(state)
	{
	case	OPR_MED3x3_EN:
		sw_knl0_MED3x3(out,in0,width,height);
		break;
	case 	OPR_MIN3x3_EN:
		sw_knl0_MIN3x3(out,in0,width,height);
		break;
	case	OPR_MAX3x3_EN:
		sw_knl0_MAX3x3(out,in0,width,height);
		break;
	case	OPR_DLT3x3_EN:
		knl0_get_DLT3x3_ctrl(&ctrl);
		sw_knl0_DLT3x3(out,in0,width,height,ctrl);
		break;
	case	OPR_ERD3x3_EN:
		knl0_get_ERD3x3_ctrl(&ctrl);
		sw_knl0_ERD3x3(out,in0,width,height,ctrl);
		break;
	case	OPR_DLT5x5_EN:
		knl0_get_DLT5x5_ctrl(&ctrl);
		sw_knl0_DLT5x5(out,in0,width,height,ctrl);
		break;
	case	OPR_ERD5x5_EN:
		knl0_get_ERD5x5_ctrl(&ctrl);
		sw_knl0_ERD5x5(out,in0,width,height,ctrl);
		break;
	case	OPR_SBL5x5_EN:
		knl0_get_SBL_ctrl(&ctrl);

		BYTE hco[5][5],vco[5][5];
		knl0_get_SBL_hcoeff(hco);
		knl0_get_SBL_vcoeff(vco);
		sw_knl0_SBL5x5(out,in0,width,height,ctrl,hco,vco);
		break;
	case	OPR_FLT5x5_EN:
		knl0_get_FLT_ctrl(&ctrl);

		BYTE co[5][5];
		knl0_get_FLT_coeff(co);
		sw_knl0_FLT5x5(out,in0,width,height,ctrl,co);
		break;
	default:
		break;
	}
}

/**************************************************/
#define  OPR_MAP_EN					((DWORD)0x00000001<<6)
#define  OPR_HST_EN					((DWORD)0x00000001<<5)
#define  OPR_TRS8_EN				((DWORD)0x00000001<<4)
#define  OPR_SUM8_EN				((DWORD)0x00000001<<3)
#define  OPR_SUM16_EN				((DWORD)0x00000001<<2)
#define  OPR_TRS16_EN				((DWORD)0x00000001<<1)
#define  OPR_BLK16_EN				((DWORD)0x00000001<<0)
#include "../code/sw_cve/4reg/sw_reg_knl1.h"
static void sw_cve_knl1_opr(DWORD state);
static void sw_cve_knl1_opr(DWORD state)
{
	BYTE *out, *in0, *in1;
	int width, height;
	top_get_wb_addr(&out);
	top_get_frm_addr(&in0, &in1);
	top_get_img_size(&width, &height);

	int ctrl;
	int ctrl0,ctrl1;
	int blk0_x, blk0_y, blk_w, blk_h;
	switch(state)
	{
	case	OPR_MAP_EN:
		knl1_get_MAP_ctrl(&ctrl);
		WORD *LUT;
		LUT=knl1_get_MAP_table();
		sw_knl1_MAP(out,in0,width,height,ctrl,LUT);
		break;
	case 	OPR_HST_EN:
		knl1_get_HST_ctrl(&ctrl);
		sw_knl1_HST(out,in0,width,height,ctrl);
		break;
	case	OPR_TRS8_EN:
		knl1_get_TRS8_ctrl0(&ctrl0);
		knl1_get_TRS8_ctrl1(&ctrl1);
		sw_knl1_TRS_8(out,in0,width,height,ctrl0,ctrl1);
		break;
	case	OPR_SUM8_EN:
		top_get_blk_size(&blk_w,&blk_h);
		top_get_blk1_pos(&blk0_x,&blk0_y);
		sw_knl1_SUM_8(out,in0,width,height,blk0_x,blk0_y,blk_w,blk_h);
		int out32;
		out32=*(int *)out;
		knl1_set_SUM16_output(out32);			/*put result to CVE reg. Stupid design*/
		break;
	case	 OPR_SUM16_EN:
		knl1_get_SUM16_ctrl(&ctrl);
		top_get_blk_size(&blk_w,&blk_h);
		top_get_blk1_pos(&blk0_x,&blk0_y);
		sw_knl1_SUM_16(out,in0,width,height,ctrl,blk0_x,blk0_y,blk_w,blk_h);
		long out64;
		out64=*(long *)out;
		knl1_set_SUM16_output(out64);			/*put result to CVE reg. Stupid design*/
		break;
	case	OPR_TRS16_EN:
		knl1_get_TRS16_ctrl0(&ctrl0);
		knl1_get_TRS16_ctrl1(&ctrl1);
		sw_knl1_TRS_16(out,in0,width,height,ctrl0,ctrl1);
		break;
	case	OPR_BLK16_EN:
		knl1_get_BLK16_ctrl(&ctrl);
		sw_knl1_BLK(out,in0,width,height,ctrl);
		break;
	default:
		break;
	}
}

/**************************************************/
#define OPR_SAD_EN   	((DWORD)0x00000001<<6)
#define OPR_VAR_EN   	((DWORD)0x00000001<<5)
#define OPR_SUB_EN   	((DWORD)0x00000001<<4)
#define OPR_ADD_EN   	((DWORD)0x00000001<<3)
#define OPR_XOR_EN   	((DWORD)0x00000001<<2)
#define OPR_OR_EN   	((DWORD)0x00000001<<1)
#define OPR_AND_EN   	((DWORD)0x00000001<<0)
#include "../code/sw_cve/4reg/sw_reg_knl2.h"
static void sw_cve_knl2_opr(DWORD state);
static void sw_cve_knl2_opr(DWORD state)
{
	BYTE *out, *in0, *in1;
	int width, height;
	top_get_wb_addr(&out);
	top_get_frm_addr(&in0, &in1);
	top_get_img_size(&width, &height);

	int ctrl;
	switch(state)
	{
	case	OPR_SAD_EN:
		knl2_get_SAD_ctrl(&ctrl);
		sw_knl2_SAD(out,in0,in1,width,height,ctrl);
		break;
	case 	OPR_VAR_EN:
		knl2_get_VAR_ctrl(&ctrl);
		int blk0_x, blk0_y, blk1_x, blk1_y, blk_w, blk_h;
		top_get_blk_size(&blk_w,&blk_h);
		top_get_blk1_pos(&blk0_x,&blk0_y);
		top_get_blk2_pos(&blk1_x,&blk1_y);
		sw_knl2_VAR(out,in0,in1,width,height,ctrl,blk0_x,blk0_y,blk1_x,blk1_y,blk_w,blk_h);
		long output;
		output=*(long *)out;
		knl2_set_VAR_output(output);			/*put result to CVE reg. Stupid design*/
		break;
	case	OPR_SUB_EN:
		knl2_get_SUB_ctrl(&ctrl);
		sw_knl2_SUB(out,in0,in1,width,height,ctrl);
		break;
	case	OPR_ADD_EN:
		knl2_get_ADD_ctrl(&ctrl);
		sw_knl2_ADD(out,in0,in1,width,height,ctrl);
		break;
	case	OPR_XOR_EN:
		sw_knl2_XOR(out,in0,in1,width,height);
		break;
	case	OPR_OR_EN:
		sw_knl2_OR(out,in0,in1,width,height);
		break;
	case	OPR_AND_EN:
		sw_knl2_AND(out,in0,in1,width,height);
		break;
	default:
		break;
	}
}

/**************************************************/

#include "../code/hw_cve/2reg/hw_reg_top.h"
#include "../hw_cve/2reg/hw_reg_top.h"
static void sw_cve_main_opr(void);
static void sw_cve_main_opr(void)
{
	DWORD state;
	top_get_start_reg(&state);
	state &= 0x01;
	if(state ==0)
		return;
	top_get_irq_state(&state);
	state &= 0x80000000;
	if(state != 0)			/*Last result hasn't fetched by App, pls wait*/
		return;

	knl0_get_opr_enabler(&state);
	if(state !=0)
	{
		sw_cve_knl0_opr(state);
		top_set_cve_done();			/*set CVE work done flag and notice app to get result*/
		return;
	}
	knl1_get_opr_enabler(&state);
	if(state !=0)
	{
		sw_cve_knl1_opr(state);
		top_set_cve_done();			/*set CVE work done flag and notice app to get result*/
		return;
	}

	knl2_get_opr_enabler(&state);
	if(state !=0)
	{
		sw_cve_knl2_opr(state);
		top_set_cve_done();			/*set CVE work done flag and notice app to get result*/
		return;
	}
	return;
}
/**************************************************/
#define CLR_DONE_REQ	0x01
/*deal with clr_irq reuqest*/
static void sw_cve_main_irq(void);
static void sw_cve_main_irq(void)
{
	DWORD request;
	top_get_clr_irq_state(&request);
	request &= CLR_DONE_REQ;
	if(request ==0)
		return;
	top_set_cve_undone();					/*clear done flag*/
	top_clr_clr_irq_state(CLR_DONE_REQ);	/*clear clr_irq flag*/
}
/**************************************************/
/*deal with software CVE error.This should not happen*/
static void sw_cve_main_err(void);
static void sw_cve_main_err(void)
{

}
/**************************************************/
#include "../code/hw_cve/2reg/hw_reg_knl.h"
static void ini_cve_reg(void);
static void ini_cve_reg(void)
{
	void *reg;
	top_ini_hw_reg();
	top_get_base_addr(&reg);

	top_ini_base_addr(reg);
	top_ini_sw_reg();

	knl0_ini_hw_reg();
	knl0_get_base_addr(&reg);

	knl0_ini_base_addr(reg);
	knl0_ini_sw_reg();

	knl1_ini_hw_reg();
	knl1_get_base_addr(&reg);

	knl1_ini_base_addr(reg);
	knl1_ini_sw_reg();

	knl2_ini_hw_reg();
	knl2_get_base_addr(&reg);

	knl2_ini_base_addr(reg);
	knl2_ini_sw_reg();
}

/**************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
static void *sw_cve_thread(void* arg);
static void *sw_cve_thread(void* arg)
{
	/*״̬������*/
	for (;;)
	{
		sw_cve_main_opr();
		usleep(10000);
		sw_cve_main_irq();
		sw_cve_main_err();
	}
	return(arg);
}

/**************************************************/
static void ini_cve_thread(void);
static void ini_cve_thread(void)
{

	int *p_arg;
	pthread_t *sw_cve_id;
	sw_cve_id = (pthread_t *)malloc(sizeof(pthread_t));
	p_arg=(int *)malloc(sizeof(int));
	pthread_create(sw_cve_id, NULL, sw_cve_thread, p_arg);
}

/**************************************************/
void ini_sw_cve(void);
void ini_sw_cve(void)
{
	ini_cve_reg();
	ini_cve_thread();
}

/* end of sw_cve.c */
