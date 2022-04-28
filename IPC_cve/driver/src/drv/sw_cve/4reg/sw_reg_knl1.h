/*---------------------------
 * sw_reg_knl1.h
 *  Created on: Jun 25, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#ifndef SW_CVE_4REG_SW_REG_KNL1_H_
#define SW_CVE_4REG_SW_REG_KNL1_H_

#include "../../code/sw_cve/4reg/h_share.h"

extern void knl1_get_base_addr(void *knl1);
extern void knl1_ini_hw_reg(void);
extern void knl1_get_opr_enabler(DWORD *opr);
extern void knl1_get_MAP_ctrl(int *ctrl);
extern void knl1_get_MAP_write(WORD *data,BYTE *addr);
extern WORD *knl1_get_MAP_table(void);	/*defined in hw_reg_knl1.c*/
extern void knl1_get_HST_ctrl(int *ctrl);
extern void knl1_get_TRS8_ctrl0(int *ctrl);
extern void knl1_get_TRS8_ctrl1(int *ctrl);
extern void knl1_set_SUM8_output(int output);
extern void knl1_get_SUM16_ctrl(int *ctrl);
extern void knl1_set_SUM16_output(long output);
extern void knl1_get_TRS16_ctrl0(int *ctrl);
extern void knl1_get_TRS16_ctrl1(int *ctrl);
extern void knl1_get_BLK16_ctrl(int *ctrl);


#endif 
/* end of sw_reg_knl1.h */
