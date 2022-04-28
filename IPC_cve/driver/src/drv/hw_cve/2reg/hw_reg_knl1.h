/*---------------------------
 * hw_reg_knl1.h
 *  Created on: Jun 11, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *abbreviated Syntax
 * opr-operator
 * knl-kernal
 *
 * Operators:
 * TRS-THRESHOLD
 * BLK-BLOCK
 * HST-HISTOGRAM
 *
 *---------------------------
 */


#ifndef HW_CVE_2REG_HW_REG_KNL1_H_
#define HW_CVE_2REG_HW_REG_KNL1_H_

#include "h_share.h"


/* ����������ֵ�ģ�һ�ɱ�ʾ�����Ƿ�ɹ�*/
extern void knl1_ini_base_addr(void *knl1);
extern void knl1_ini_sw_reg(void);

extern void knl1_set_opr_enabler(DWORD opr);
extern void knl1_clr_opr_enabler(DWORD opr);

extern void knl1_set_MAP_opr(void);
extern void knl1_set_MAP_mode(BYTE mode);
extern void knl1_set_MAP_write(WORD data,BYTE addr);
extern void knl1_clr_MAP_opr(void);

extern void knl1_set_HST_opr(void);
extern void knl1_set_HST_mode(BYTE mode);
extern void knl1_clr_HST_opr(void);

extern void knl1_set_TRS8_opr(void);
extern void knl1_set_TRS8_mode(BYTE mode);
extern void knl1_set_TRS8_trs(BYTE low,BYTE high);
extern void knl1_set_TRS8_value(BYTE v0,BYTE v1,BYTE v2);
extern void knl1_clr_TRS8_opr(void);

extern void knl1_set_SUM8_opr(void);
extern void knl1_get_SUM8_output(int *output);
extern void knl1_clr_SUM8_opr(void);

extern void knl1_set_SUM16_opr(void);
extern void knl1_set_SUM16_mode(BYTE mode);
extern void knl1_get_SUM16_output(long *output);
extern void knl1_clr_SUM16_opr(void);

extern void knl1_set_TRS16_opr(void);
extern void knl1_set_TRS16_mode_sign(BYTE mode);
extern void knl1_set_TRS16_mode_value(BYTE mode);
extern void knl1_set_TRS16_trs(WORD low,WORD high);
extern void knl1_set_TRS16_value(BYTE v0,BYTE v1,BYTE v2);
extern void knl1_clr_TRS16_opr(void);

extern void knl1_set_BLK16_opr(void);
extern void knl1_set_BLK16_mode(BYTE mode);
extern void knl1_set_BLK16_power(BYTE shift);
extern void knl1_clr_BLK16_opr(void);

#endif 
/* end of hw_reg_knl1.h */
