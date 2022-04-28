/*---------------------------
 * hw_opr_asyn.h
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


#ifndef HW_CVE_3OPR_HW_OPR_ASYN_H_
#define HW_CVE_3OPR_HW_OPR_ASYN_H_

#include "h_share.h"

extern int  opr_set_out_para(UINT8 *out);
extern int  opr_set_frm_para(UINT8 *in0, UINT8 *in1, int width, int height);
extern int  opr_set_blk_para(int blk0_x, int blk0_y, int blk1_x, int blk1_y, int blk_w,int blk_h);
extern void opr_set_cve_run();
extern void opr_clr_cve_run();
extern int  opr_is_cve_done();
extern int  opr_is_cve_error();

extern void opr_sel_DLT5(BYTE mode);
extern void opr_rev_DLT5(void);
extern void opr_sel_DLT3(BYTE mode);
extern void opr_rev_DLT3(void);
extern void opr_sel_ERD5(BYTE mode);
extern void opr_rev_ERD5(void);
extern void opr_sel_ERD3(BYTE mode);
extern void opr_rev_ERD3(void);
extern void opr_sel_FLT(BYTE power,BYTE co[][5]);
extern void opr_rev_FLT(void);
extern void opr_sel_MAX(void);
extern void opr_rev_MAX(void);
extern void opr_sel_MED(void);
extern void opr_rev_MED(void);
extern void opr_sel_MIN(void);
extern void opr_rev_MIN(void);
extern void opr_sel_SBL(BYTE output,BYTE angle,BYTE ang,BYTE mag,BYTE hco[][5],BYTE vco[][5]);
extern void opr_rev_SBL(void);

extern void opr_sel_BLK(BYTE mode, BYTE shift);
extern void opr_rev_BLK(void);
extern void opr_sel_HST(BYTE mode);
extern void opr_rev_HST(void);
extern void opr_sel_MAP(BYTE mode, WORD *map);
extern void opr_rev_MAP(void);
extern void opr_sel_SUM8(void);
extern void opr_get_SUM8(int *out);
extern void opr_rev_SUM8(void);
extern void opr_sel_SUM16(BYTE mode);
extern void opr_get_SUM16(long *out);
extern void opr_rev_SUM16(void);
extern void opr_sel_TRS8(BYTE low,BYTE high,BYTE vmode, BYTE v0,BYTE v1,BYTE v2);
extern void opr_rev_TRS8(void);
extern void opr_sel_TRS16(BYTE low,BYTE high,BYTE smode, BYTE vmode,BYTE v0,BYTE v1,BYTE v2);
extern void opr_rev_TRS16(void);

extern void opr_sel_ADD(BYTE mode);
extern void opr_rev_ADD(void);
extern void opr_sel_AND(void);
extern void opr_rev_AND(void);
extern void opr_sel_OR(void);
extern void opr_rev_OR(void);
extern void opr_sel_SAD(BYTE mode);
extern void opr_rev_SAD(void);
extern void opr_sel_SUB(BYTE mode);
extern void opr_rev_SUB(void);
extern void opr_sel_VAR(BYTE mode,BYTE a, BYTE b);
extern void opr_get_VAR(QWORD *out);
extern void opr_rev_VAR(void);
extern void opr_sel_XOR(void);
extern void opr_rev_XOR(void);

#endif 
/* end of hw_opr_asyn.h */
