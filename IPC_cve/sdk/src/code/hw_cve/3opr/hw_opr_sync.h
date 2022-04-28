/*---------------------------
 * hw_opr_sync.h
 *  Created on: Jun 24, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#ifndef HW_CVE_3OPR_HW_OPR_SYNC_H_
#define HW_CVE_3OPR_HW_OPR_SYNC_H_

#include "h_share.h"

extern void hw_opr_DLT5(BYTE *out, BYTE *in, int width, int height, BYTE mode);
extern void hw_opr_DLT3(BYTE *out, BYTE *in, int width, int height, BYTE mode);
extern void hw_opr_ERD5(BYTE *out, BYTE *in, int width, int height, BYTE mode);
extern void hw_opr_ERD3(BYTE *out, BYTE *in, int width, int height, BYTE mode);
extern void hw_opr_FLT(BYTE *out, BYTE *in, int width, int height,BYTE power,BYTE co[][5]);
extern void hw_opr_MAX(BYTE *out, BYTE *in, int width, int height);
extern void hw_opr_MED(BYTE *out, BYTE *in, int width, int height);
extern void hw_opr_MIN(BYTE *out, BYTE *in, int width, int height);
extern void hw_opr_SBL(BYTE *out, BYTE *in, int width, int height,BYTE output,BYTE angle,BYTE ang,BYTE mag,BYTE hco[][5],BYTE vco[][5]);

extern void hw_opr_BLK(BYTE *out, BYTE *in, int width, int height, BYTE mode, BYTE shift);
extern void hw_opr_HST(BYTE *out, BYTE *in, int width, int height, BYTE mode);
extern void hw_opr_MAP(BYTE *out, BYTE *in, int width, int height, BYTE mode, WORD *map);
extern void hw_opr_SUM8(BYTE *out, BYTE *in, int width, int height, int blk0_x, int blk0_y, int blk_w,int blk_h);
extern void hw_opr_SUM16(BYTE *out, BYTE *in, int width, int height, BYTE mode,int blk0_x, int blk0_y, int blk_w,int blk_h);
extern void hw_opr_TRS8(BYTE *out, BYTE *in, int width, int height, BYTE low,BYTE high,BYTE vmode,BYTE v0,BYTE v1,BYTE v2);
extern void hw_opr_TRS16(BYTE *out, BYTE *in, int width, int height, WORD low,WORD high,BYTE smode,BYTE vmode,BYTE v0,BYTE v1,BYTE v2);

extern void hw_opr_ADD(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode);
extern void hw_opr_AND(BYTE *out, BYTE *in0, BYTE *in1, int width, int height);
extern void  hw_opr_OR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height);
extern void hw_opr_SAD(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode);
extern void hw_opr_SUB(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode);
extern void hw_opr_VAR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode, BYTE a, BYTE b, int blk0_x, int blk0_y, int blk1_x, int blk1_y, int blk_w,int blk_h);
extern void hw_opr_XOR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height);

#endif 
/* end of hw_opr_sync.h */
