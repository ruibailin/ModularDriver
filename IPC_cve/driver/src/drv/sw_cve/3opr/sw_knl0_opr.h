/*---------------------------
 * sw_knl0_opr.h
 *  Created on: Jun 20, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#ifndef SW_CVE_3OPR_SW_KNL0_OPR_H_
#define SW_CVE_3OPR_SW_KNL0_OPR_H_

#include "h_share.h"

extern void sw_knl0_DLT5x5(char *out, char *in0, int width, int height,int ctrl);
extern void sw_knl0_DLT3x3(char *out, char *in0, int width, int height,int ctrl);
extern void sw_knl0_ERD3x3(char *out, char *in0, int width, int height,int ctrl);
extern void sw_knl0_ERD5x5(char *out, char *in0, int width, int height,int ctrl);
extern void sw_knl0_FLT5x5(char *out, char *in0, int width, int height,int ctrl, char coeff[][5]);
extern void sw_knl0_MAX3x3(char *out, char *in0, int width, int height);
extern void sw_knl0_MED3x3(char *out, char *in0, int width, int height);
extern void sw_knl0_MIN3x3(char *out, char *in0, int width, int height);
extern void sw_knl0_SBL5x5(char *out, char *in0, int width, int height,int ctrl, char hCoeff[][5],char vCoeff[][5]);
extern void sw_knl0_SBL3x3(char *out, char *in0, int width, int height,int ctrl, char hCoeff[][3],char vCoeff[][3]);



#endif 
/* end of sw_knl0_opr.h */
