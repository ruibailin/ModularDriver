/*---------------------------
 * sw_knl_opr.c
 *  Created on: Jun 25, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Provide the counterparts of Hardware Operators.
 *Can be directly called by App.
 *
 *
 *---------------------------
 */


#include "../../sw_cve/3opr/sw_knl0_opr.h"
#include "../../sw_cve/3opr/sw_knl1_opr.h"
#include "../../sw_cve/3opr/sw_knl2_opr.h"
#include "c_share.h"
/**************************************************/
static int get_DLT5_ctrl(BYTE mode);
static int get_DLT5_ctrl(BYTE mode)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x000000FF;
	old=ctrl;
	old &= (~0x000000FF);
	old |= new;
	ctrl=old;

	return(ctrl);
}
/**************************************************/
void sw_opr_DLT5(BYTE *out, BYTE *in0, int width, int height, BYTE mode);
void sw_opr_DLT5(BYTE *out, BYTE *in0, int width, int height, BYTE mode)
{
	int ctrl;
	ctrl=get_DLT5_ctrl(mode);
	sw_knl0_DLT5x5(out, in0, width, height, ctrl);
}

/**************************************************/
static int get_DLT3_ctrl(BYTE mode);
static int get_DLT3_ctrl(BYTE mode)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;
	new=(DWORD)mode;
	new &= 0x0000000FF;
	old=ctrl;
	old &= (~0x0000000FF);
	old |= new;
	ctrl=old;

	return(ctrl);
}
/**************************************************/
void sw_opr_DLT3(BYTE *out, BYTE *in0, int width, int height, BYTE mode);
void sw_opr_DLT3(BYTE *out, BYTE *in0, int width, int height, BYTE mode)
{
	int ctrl;
	ctrl=get_DLT3_ctrl(mode);
	sw_knl0_DLT3x3(out, in0, width, height, ctrl);
}

/**************************************************/
static int get_ERD5_ctrl(BYTE mode);
static int get_ERD5_ctrl(BYTE mode)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x000000FF;
	old=ctrl;
	old &= (~0x000000FF);
	old |= new;
	ctrl=old;

	return(ctrl);
}
/**************************************************/
void sw_opr_ERD5(BYTE *out, BYTE *in0, int width, int height, BYTE mode);
void sw_opr_ERD5(BYTE *out, BYTE *in0, int width, int height, BYTE mode)
{
	int ctrl;
	ctrl=get_ERD5_ctrl(mode);
	sw_knl0_ERD5x5(out, in0, width, height, ctrl);
}

/**************************************************/
static int get_ERD3_ctrl(BYTE mode);
static int get_ERD3_ctrl(BYTE mode)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x0000000FF;
	old=ctrl;
	old &= (~0x0000000FF);
	old |= new;
	ctrl=old;

	return(ctrl);
}
/**************************************************/
void sw_opr_ERD3(BYTE *out, BYTE *in0, int width, int height, BYTE mode);
void sw_opr_ERD3(BYTE *out, BYTE *in0, int width, int height, BYTE mode)
{
	int ctrl;
	ctrl=get_ERD3_ctrl(mode);
	sw_knl0_ERD3x3(out, in0, width, height, ctrl);
}

/**************************************************/
static int get_FLT_ctrl(BYTE mode);
static int get_FLT_ctrl(BYTE mode)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x0000000F;
	old=ctrl;
	old &= (~0x0000000F);
	old |= new;
	ctrl=old;

	return(ctrl);
}
/**************************************************/
void sw_opr_FLT(BYTE *out, BYTE *in0, int width, int height,BYTE power,char co[][5]);
void sw_opr_FLT(BYTE *out, BYTE *in0, int width, int height,BYTE power,char co[][5])
{
	int ctrl;
	ctrl=get_FLT_ctrl(power);
	sw_knl0_FLT5x5(out, in0, width, height, ctrl, co);
}

/**************************************************/
void sw_opr_MAX(BYTE *out, BYTE *in0, int width, int height);
void sw_opr_MAX(BYTE *out, BYTE *in0, int width, int height)
{
	sw_knl0_MAX3x3(out, in0, width, height);
}

/**************************************************/
void sw_opr_MED(BYTE *out, BYTE *in0, int width, int height);
void sw_opr_MED(BYTE *out, BYTE *in0, int width, int height)
{
	sw_knl0_MED3x3(out, in0, width, height);
}

/**************************************************/
void sw_opr_MIN(BYTE *out, BYTE *in0, int width, int height);
void sw_opr_MIN(BYTE *out, BYTE *in0, int width, int height)
{
	sw_knl0_MIN3x3(out, in0, width, height);
}

/**************************************************/
static int get_SBL_ctrl(BYTE output,BYTE angle,BYTE ang,BYTE mag);
static int get_SBL_ctrl(BYTE output,BYTE angle,BYTE ang,BYTE mag)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;

	new=(DWORD)output;
	new &= 0x00000007;
	new <<= 9;
	old=ctrl;
	old &= (~(0x00000007<<9));
	old |= new;
	ctrl=old;

	new=(DWORD)angle;
	new &= 0x00000001;
	new <<= 8;
	old=ctrl;
	old &= (~(0x00000001<<8));
	old |= new;
	ctrl=old;

	new=(DWORD)ang;
	new &= 0x0000000F;
	new <<= 4;
	old=ctrl;
	old &= (~(0x0000000F<<4));
	old |= new;
	ctrl=old;

	new=(DWORD)mag;
	new &= 0x0000000F;
	old=ctrl;
	old &= (~0x0000000F);
	old |= new;
	ctrl=old;

	return(ctrl);
}
/**************************************************/
void sw_opr_SBL(BYTE *out, BYTE *in0, int width, int height,BYTE output,BYTE angle,BYTE ang,BYTE mag,char hco[][5],char vco[][5]);
void sw_opr_SBL(BYTE *out, BYTE *in0, int width, int height,BYTE output,BYTE angle,BYTE ang,BYTE mag,char hco[][5],char vco[][5])
{
	int ctrl;
	ctrl=get_SBL_ctrl(output,angle,ang,mag);
	sw_knl0_SBL5x5(out, in0, width, height, ctrl,hco,vco);
}


/**************************************************/
void sw_opr_BLK(BYTE *out, BYTE *in0, int width, int height, BYTE mode, BYTE shift);
void sw_opr_BLK(BYTE *out, BYTE *in0, int width, int height, BYTE mode, BYTE shift)
{
	int ctrl;
	ctrl=0;

	sw_knl1_BLK(out, in0, width, height, ctrl);
}

/**************************************************/
void sw_opr_HST(BYTE *out, BYTE *in0, int width, int height, BYTE mode);
void sw_opr_HST(BYTE *out, BYTE *in0, int width, int height, BYTE mode)
{
	int ctrl;
	ctrl=0;

	sw_knl1_HST(out, in0, width, height, ctrl);
}

/**************************************************/
static int get_MAP_ctrl(BYTE mode);
static int get_MAP_ctrl(BYTE mode)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;
	new=(DWORD)mode;
	new &= 0x00000001;
	old=ctrl;
	old &= (~0x00000001);
	old |= new;
	ctrl=old;

	return(ctrl);
}
/**************************************************/
void sw_opr_MAP(BYTE *out, BYTE *in0, int width, int height, BYTE mode, WORD *map);
void sw_opr_MAP(BYTE *out, BYTE *in0, int width, int height, BYTE mode, WORD *map)
{
	int ctrl;
	ctrl=get_MAP_ctrl(mode);
	sw_knl1_MAP(out, in0, width, height, ctrl, map);
}

/**************************************************/
void sw_opr_SUM8(BYTE *out, BYTE *in0, int width, int height,int blk0_x, int blk0_y, int blk_w,int blk_h);
void sw_opr_SUM8(BYTE *out, BYTE *in0, int width, int height,int blk0_x, int blk0_y, int blk_w,int blk_h)
{
	sw_knl1_SUM_8(out, in0, width, height,blk0_x, blk0_y, blk_w,blk_h);
}

/**************************************************/
void sw_opr_SUM16(BYTE *out, BYTE *in0, int width, int height, BYTE mode,int blk0_x, int blk0_y, int blk_w,int blk_h);
void sw_opr_SUM16(BYTE *out, BYTE *in0, int width, int height, BYTE mode,int blk0_x, int blk0_y, int blk_w,int blk_h)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;
	new=(DWORD)mode;
	new &= 0x00000001;
	old=ctrl;
	old &= (~0x00000001);
	old |= new;
	ctrl=old;

	sw_knl1_SUM_16(out, in0, width, height, ctrl,blk0_x, blk0_y, blk_w,blk_h);
}
/**************************************************/
static int get_TRS8_ctrl0(BYTE low,BYTE high);
static int get_TRS8_ctrl0(BYTE low,BYTE high)
{
	int ctrl;
	ctrl=0;

	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	B2DW  b2dw;
	b2dw.dw=ctrl;
	b2dw.b[0]=low;
	b2dw.b[1]=high;
	ctrl=b2dw.dw;

	return(ctrl);
}

/**************************************************/
static int get_TRS8_ctrl1(BYTE vmode,BYTE v0,BYTE v1,BYTE v2);
static int get_TRS8_ctrl1(BYTE vmode,BYTE v0,BYTE v1,BYTE v2)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;
	new=(DWORD)vmode;
	new &= 0x00000007;
	old=ctrl;
	old &= (~0x00000007);
	old |= new;
	ctrl=old;

	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	B2DW  b2dw;
	b2dw.dw=ctrl;
	b2dw.b[1]=v0;
	b2dw.b[2]=v1;
	b2dw.b[3]=v2;
	ctrl=b2dw.dw;

	return(ctrl);
}
/**************************************************/
void sw_opr_TRS8(BYTE *out, BYTE *in0, int width, int height, BYTE low,BYTE high,BYTE vmode,BYTE v0,BYTE v1,BYTE v2);
void sw_opr_TRS8(BYTE *out, BYTE *in0, int width, int height, BYTE low,BYTE high,BYTE vmode,BYTE v0,BYTE v1,BYTE v2)
{
	int ctrl0,ctrl1;
	ctrl0=get_TRS8_ctrl0(low,high);
	ctrl1=get_TRS8_ctrl1(vmode,v0,v1,v2);
	sw_knl1_TRS_8(out, in0, width, height, ctrl0,ctrl1);
}

/**************************************************/
static int get_TRS16_ctrl0(WORD low,WORD high);
static int get_TRS16_ctrl0(WORD low,WORD high)
{
	int ctrl;
	ctrl=0;

	typedef union{
		DWORD  dw;
		BYTE   w[2];
	}W2DW;
	W2DW  w2dw;
	w2dw.dw=ctrl;
	w2dw.w[0]=low;
	w2dw.w[1]=high;
	ctrl=w2dw.dw;

	return(ctrl);
}

/**************************************************/
static int get_TRS16_ctrl1(BYTE smode,BYTE vmode,BYTE v0,BYTE v1,BYTE v2);
static int get_TRS16_ctrl1(BYTE smode,BYTE vmode,BYTE v0,BYTE v1,BYTE v2)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;
	new=(DWORD)smode;
	new &= 0x00000001;
	new <<= 3;
	old=ctrl;
	old &= (~(0x00000001<<3));
	old |= new;
	ctrl=old;

	new=(DWORD)vmode;
	new &= 0x00000007;
	old=ctrl;
	old &= (~0x00000007);
	old |= new;
	ctrl=old;

	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	B2DW  b2dw;
	b2dw.dw=ctrl;
	b2dw.b[1]=v0;
	b2dw.b[2]=v1;
	b2dw.b[3]=v2;
	ctrl=b2dw.dw;
	return(ctrl);
}
/**************************************************/
void sw_opr_TRS16(BYTE *out, BYTE *in0, int width, int height, WORD low,WORD high,BYTE smode,BYTE vmode,BYTE v0,BYTE v1,BYTE v2);
void sw_opr_TRS16(BYTE *out, BYTE *in0, int width, int height, WORD low,WORD high,BYTE smode,BYTE vmode,BYTE v0,BYTE v1,BYTE v2)
{
	int ctrl0,ctrl1;
	ctrl0=get_TRS16_ctrl0(low,high);
	ctrl1=get_TRS16_ctrl1(smode,vmode,v0,v1,v2);
	sw_knl1_TRS_16(out, in0, width, height, ctrl0,ctrl1);
}

/**************************************************/
static int get_ADD_ctrl(BYTE mode);
static int get_ADD_ctrl(BYTE mode)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;
	new=(DWORD)mode;
	new &= 0x000000FF;
	old=ctrl;
	old &= (~0x000000FF);
	old |= new;
	ctrl=old;

	return(ctrl);
}
/**************************************************/
void sw_opr_ADD(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode);
void sw_opr_ADD(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode)
{
	int ctrl;
	ctrl=get_ADD_ctrl(mode);
	sw_knl2_ADD(out, in0, in1, width, height, ctrl);
}

/**************************************************/
void sw_opr_AND(BYTE *out, BYTE *in0, BYTE *in1, int width, int height);
void sw_opr_AND(BYTE *out, BYTE *in0, BYTE *in1, int width, int height)
{
	sw_knl2_AND(out, in0, in1, width, height);
}

/**************************************************/
void  sw_opr_OR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height);
void  sw_opr_OR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height)
{
	sw_knl2_OR(out, in0, in1, width, height);
}

/**************************************************/
static int get_SAD_ctrl(BYTE mode);
static int get_SAD_ctrl(BYTE mode)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;
	new=(DWORD)mode;
	new &= 0x00000003;
	old=ctrl;
	old &= (~0x00000003);
	old |= new;
	ctrl=old;

	return(ctrl);
}
/**************************************************/
void sw_opr_SAD(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode);
void sw_opr_SAD(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode)
{
	int ctrl;
	ctrl= get_SAD_ctrl(mode);
	sw_knl2_SAD(out, in0, in1, width, height, ctrl);
}

/**************************************************/
static int get_SUB_ctrl(BYTE mode);
static int get_SUB_ctrl(BYTE mode)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;
	new=(DWORD)mode;
	new &= 0x00000001;
	old=ctrl;
	old &= (~0x00000001);
	old |= new;
	ctrl=old;

	return(ctrl);
}
/**************************************************/
void sw_opr_SUB(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode);
void sw_opr_SUB(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode)
{
	int ctrl;
	ctrl=get_SUB_ctrl(mode);
	sw_knl2_SUB(out, in0, in1, width, height, ctrl);
}

/**************************************************/
static int get_VAR_ctrl(BYTE mode, BYTE a, BYTE b);
static int get_VAR_ctrl(BYTE mode, BYTE a, BYTE b)
{
	int ctrl;
	ctrl=0;

	DWORD	new,old;
	new=(DWORD)mode;
	new &= 0x00000001;
	new <<= 16;
	old=ctrl;
	old &= (~(0x00000001<<16));
	old |= new;
	ctrl=old;

	new=(DWORD)a;
	new &= 0x000000FF;
	old=ctrl;
	old &= (~0x000000FF);
	old |= new;
	ctrl=old;

	new=(DWORD)b;
	new &= 0x000000FF;
	new <<= 8;
	old=ctrl;
	old &= (~(0x000000FF<<8));
	old |= new;
	ctrl=old;

	return(ctrl);
}
/**************************************************/
void sw_opr_VAR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode, BYTE a, BYTE b, int blk0_x, int blk0_y, int blk1_x, int blk1_y, int blk_w,int blk_h);
void sw_opr_VAR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode, BYTE a, BYTE b, int blk0_x, int blk0_y, int blk1_x, int blk1_y, int blk_w,int blk_h)
{
	int ctrl;

	ctrl=get_VAR_ctrl(mode, a, b);
	sw_knl2_VAR(out, in0, in1, width, height, ctrl, blk0_x, blk0_y, blk1_x, blk1_y, blk_w, blk_h );
}

/**************************************************/
void sw_opr_XOR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height);
void sw_opr_XOR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height)
{
	sw_knl2_XOR(out, in0, in1, width, height);
}

/* end of sw_knl_opr.c */
