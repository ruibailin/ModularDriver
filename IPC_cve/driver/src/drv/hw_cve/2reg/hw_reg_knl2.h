/*---------------------------
 * hw_reg_knl2.h
 *  Created on: Jun 11, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *abbreviated Syntax
 * opr-operator
 * knl-kernal
 *
 * Operators:
 * VAR-VARIANCE
 *
 *---------------------------
 */


#ifndef HW_CVE_2REG_HW_REG_KNL2_H_
#define HW_CVE_2REG_HW_REG_KNL2_H_

#include "h_share.h"

/* ����������ֵ�ģ�һ�ɱ�ʾ�����Ƿ�ɹ�*/
extern void knl2_ini_base_addr(void *knl2);
extern void knl2_ini_sw_reg(void);

extern void knl2_set_opr_enabler(DWORD opr);
extern void knl2_clr_opr_enabler(DWORD opr);

extern void knl2_set_SAD_opr(void);
extern void knl2_set_SAD_mode(BYTE mode);
extern void knl2_clr_SAD_opr(void);

extern void knl2_set_VAR_opr(void);
extern void knl2_set_VAR_mode(BYTE mode);
extern void knl2_set_VAR_input(BYTE a, BYTE b);
extern void knl2_get_VAR_output(long *output);
extern void knl2_clr_VAR_opr(void);

extern void knl2_set_SUB_opr(void);
extern void knl2_set_SUB_mode(BYTE mode);
extern void knl2_clr_SUB_opr(void);

extern void knl2_set_ADD_opr(void);
extern void knl2_set_ADD_mode(BYTE mode);
extern void knl2_clr_ADD_opr(void);

extern void knl2_set_XOR_opr(void);
extern void knl2_clr_XOR_opr(void);

extern void knl2_set_OR_opr(void);
extern void knl2_clr_OR_opr(void);

extern void knl2_set_AND_opr(void);
extern void knl2_clr_AND_opr(void);

#endif 
/* end of hw_reg_knl2.h */
