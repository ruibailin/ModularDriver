
/*---------------------------
 * sw_knl2_opr.h
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

#ifndef SRC_CODE_SW_CVE_3OPR_SW_KNL2_OPR_H_
#define SRC_CODE_SW_CVE_3OPR_SW_KNL2_OPR_H_

#include "h_share.h"

extern void sw_knl2_ADD(char *out, char *in0, char *in1, int width, int height,int ctrl);
extern void sw_knl2_AND(char *out, char *in0, char *in1, int width, int height);
extern void  sw_knl2_OR(char *out, char *in0, char *in1, int width, int height);
extern void sw_knl2_SAD(char *out, char *in0, char *in1, int width, int height,int ctrl);
extern void sw_knl2_SUB(char *out, char *in0, char *in1, int width, int height,int ctrl);
extern void sw_knl2_VAR(char *out, char *in0, char *in1, int w, int h, int ctrl,int blk0_x, int blk0_y, int blk1_x, int blk1_y, int blk_w,int blk_h);
extern void sw_knl2_XOR(char *out, char *in0, char *in1, int width, int height);


#endif 
/* end of sw_knl2_opr.h */
