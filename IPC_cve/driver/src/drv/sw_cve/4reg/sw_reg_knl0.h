/*---------------------------
 * sw_reg_knl0.h
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


#ifndef SW_CVE_4REG_SW_REG_KNL0_H_
#define SW_CVE_4REG_SW_REG_KNL0_H_

#include "../../code/sw_cve/4reg/h_share.h"

extern void knl0_get_base_addr(void *knl0);
extern void knl0_ini_hw_reg(void);
extern void knl0_get_opr_enabler(DWORD *opr);
extern void knl0_get_ERD5x5_ctrl(int *ctrl);
extern void knl0_get_ERD3x3_ctrl(int *ctrl);
extern void knl0_get_DLT5x5_ctrl(int *ctrl);
extern void knl0_get_DLT3x3_ctrl(int *ctrl);
extern void knl0_get_FLT_ctrl(int *ctrl);
extern void knl0_get_FLT_coeff(BYTE co[][5]);
extern void knl0_get_SBL_ctrl(int *ctrl);
extern void knl0_get_SBL_hcoeff(BYTE hco[][5]);
extern void knl0_get_SBL_vcoeff(BYTE vco[][5]);

#endif 
/* end of sw_reg_knl0.h */
