
/*---------------------------
 * sw_knl1_opr.h
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

#ifndef SRC_CODE_SW_CVE_3OPR_SW_KNL1_OPR_H_
#define SRC_CODE_SW_CVE_3OPR_SW_KNL1_OPR_H_

#include "h_share.h"

extern void    sw_knl1_BLK(char *out, char *in0, int width, int height,int ctrl);
extern void    sw_knl1_HST(char *out, char *in0, int width, int height,int ctrl);
extern void    sw_knl1_MAP(char *out, char *in0, int width, int height,int ctrl, UINT16 *LUT);
extern void  sw_knl1_TRS_8(char *out, char *in0, int width, int height,int ctrl0,int ctrl1);
extern void sw_knl1_TRS_16(char *out, char *in0, int width, int height,int ctrl0,int ctrl1);
extern void  sw_knl1_SUM_8(char *out, char *in0, int width, int height,int blk0_x, int blk0_y, int blk_w,int blk_h);
extern void sw_knl1_SUM_16(char *out, char *in0, int width, int height,int ctrl, int blk0_x, int blk0_y, int blk_w,int blk_h);

#endif 
/* end of sw_knl1_opr.h */
