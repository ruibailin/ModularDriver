/*---------------------------
 * sw_knl_opr.h
 *  Created on: Jun 25, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *These functions can be directly called by APP.
 *Software CVE will be triggered
 *
 *
 *---------------------------
 */


#ifndef HW_CVE_3OPR_SW_KNL_OPR_H_
#define HW_CVE_3OPR_SW_KNL_OPR_H_

#include "h_share.h"

extern void sw_opr_DLT5(BYTE *out, BYTE *in, int width, int height, BYTE mode);
extern void sw_opr_DLT3(BYTE *out, BYTE *in, int width, int height, BYTE mode);
extern void sw_opr_ERD5(BYTE *out, BYTE *in, int width, int height, BYTE mode);
extern void sw_opr_ERD3(BYTE *out, BYTE *in, int width, int height, BYTE mode);
extern void sw_opr_FLT(BYTE *out, BYTE *in, int width, int height,BYTE power,BYTE co[][5]);
extern void sw_opr_MAX(BYTE *out, BYTE *in, int width, int height);
extern void sw_opr_MED(BYTE *out, BYTE *in, int width, int height);
extern void sw_opr_MIN(BYTE *out, BYTE *in, int width, int height);
extern void sw_opr_SBL(BYTE *out, BYTE *in, int width, int height,BYTE output,BYTE angle,BYTE ang,BYTE mag,BYTE hco[][5],BYTE vco[][5]);

extern void sw_opr_BLK(BYTE *out, BYTE *in, int width, int height, BYTE mode, BYTE shift);
extern void sw_opr_HST(BYTE *out, BYTE *in, int width, int height, BYTE mode);
extern void sw_opr_MAP(BYTE *out, BYTE *in, int width, int height, BYTE mode, WORD *map);
extern void sw_opr_SUM8(BYTE *out, BYTE *in, int width, int height, int blk0_x, int blk0_y, int blk_w,int blk_h);
extern void sw_opr_SUM16(BYTE *out, BYTE *in, int width, int height, BYTE mode,int blk0_x, int blk0_y, int blk_w,int blk_h);
extern void sw_opr_TRS8(BYTE *out, BYTE *in, int width, int height, BYTE low,BYTE high,BYTE vmode,BYTE v0,BYTE v1,BYTE v2);
extern void sw_opr_TRS16(BYTE *out, BYTE *in, int width, int height, WORD low,WORD high,BYTE smode,BYTE vmode,BYTE v0,BYTE v1,BYTE v2);

extern void sw_opr_ADD(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode);
extern void sw_opr_AND(BYTE *out, BYTE *in0, BYTE *in1, int width, int height);
extern void  sw_opr_OR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height);
extern void sw_opr_SAD(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode);
extern void sw_opr_SUB(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode);
extern void sw_opr_VAR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode, BYTE a, BYTE b, int blk0_x, int blk0_y, int blk1_x, int blk1_y, int blk_w,int blk_h);
extern void sw_opr_XOR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height);

#endif 
/* end of sw_knl_opr.h */
