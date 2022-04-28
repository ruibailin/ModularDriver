/*---------------------------
 * hw_reg_knl0.h
 *  Created on: Jun 9, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *abbreviated Syntax
 * opr-operator
 * knl-kernal
 * coeff-coefficient
 *
 * Operators:
 * FLT-filter
 * SBL-Sobel
 * ERD-ERODE
 * DLT-DILATE
 * MED-MEDIAN
 *
 *
 *
 *---------------------------
 */


#ifndef HW_CVE_2REG_HW_REG_KNL0_H_
#define HW_CVE_2REG_HW_REG_KNL0_H_

#include "h_share.h"

/* ����������ֵ�ģ�һ�ɱ�ʾ�����Ƿ�ɹ�*/
extern void knl0_ini_base_addr(void *knl0);
extern void knl0_ini_sw_reg(void);

extern void knl0_set_opr_enabler(DWORD opr);
extern void knl0_clr_opr_enabler(DWORD opr);

extern void knl0_set_MED3x3_opr(void);
extern void knl0_clr_MED3x3_opr(void);

extern void knl0_set_MIN3x3_opr(void);
extern void knl0_clr_MIN3x3_opr(void);

extern void knl0_set_MAX3x3_opr(void);
extern void knl0_clr_MAX3x3_opr(void);

extern void knl0_set_ERD3x3_opr(void);
extern void knl0_clr_ERD3x3_opr(void);
extern void knl0_set_ERD3x3_mode(BYTE mode);

extern void knl0_set_ERD5x5_opr(void);
extern void knl0_clr_ERD5x5_opr(void);
extern void knl0_set_ERD5x5_mode(BYTE mode);

extern void knl0_set_DLT3x3_opr(void);
extern void knl0_clr_DLT3x3_opr(void);
extern void knl0_set_DLT3x3_mode(BYTE mode);

extern void knl0_set_DLT5x5_opr(void);
extern void knl0_clr_DLT5x5_opr(void);
extern void knl0_set_DLT5x5_mode(BYTE mode);

extern void knl0_set_FLT_opr(void);
extern void knl0_clr_FLT_opr(void);
extern void knl0_set_FLT_power(BYTE power);
extern void knl0_set_FLT_coeff(BYTE co[][5]);

extern void knl0_set_SBL_opr(void);
extern void knl0_clr_SBL_opr(void);
extern void knl0_set_SBL_mode(BYTE output,BYTE angle);
extern void knl0_set_SBL_mode_output(BYTE output);
extern void knl0_set_SBL_mode_angle(BYTE angle);
extern void knl0_set_SBL_power(BYTE ang,BYTE mag);
extern void knl0_set_SBL_power_ang(BYTE ang);
extern void knl0_set_SBL_power_mag(BYTE mag);
extern void knl0_set_SBL_hcoeff(BYTE hco[][5]);
extern void knl0_set_SBL_vcoeff(BYTE vco[][5]);

#endif 
/* end of hw_reg_knl0.h */
