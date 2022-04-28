/*---------------------------
 * sw_reg_knl2.h
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


#ifndef SW_CVE_4REG_SW_REG_KNL2_H_
#define SW_CVE_4REG_SW_REG_KNL2_H_

#include "../../code/sw_cve/4reg/h_share.h"

extern void knl2_get_base_addr(void *knl2);
extern void knl2_ini_hw_reg(void);
extern void knl2_get_opr_enabler(DWORD *opr);
extern void knl2_get_SAD_ctrl(int *ctrl);
extern void knl2_get_VAR_ctrl(int *ctrl);
extern void knl2_set_VAR_output(long output);
extern void knl2_get_SUB_ctrl(int *ctrl);
extern void knl2_get_ADD_ctrl(int *ctrl);

#endif 
/* end of sw_reg_knl2.h */
