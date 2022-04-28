/*---------------------------
 * sw_reg_top.h
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


#ifndef SW_CVE_4REG_SW_REG_TOP_H_
#define SW_CVE_4REG_SW_REG_TOP_H_

#include "../../code/sw_cve/4reg/h_share.h"

extern void top_get_base_addr(void *top);
extern void top_ini_hw_reg(void);
extern void top_get_start_reg(DWORD *state);
extern void top_get_ddr_addr(void *start,void *end);
extern int top_get_frm_addr(void *frm1, void *frm2);
extern int top_get_wb_addr(void *wb);
extern int top_get_img_size(int *w,int *h);
extern int top_get_blk_size(int *w,int *h);
extern int top_get_blk1_pos(int *x,int *y);
extern int top_get_blk2_pos(int *x,int *y);
extern void top_set_irq_state(DWORD state);
extern void top_set_cve_done(void);
extern void top_set_cve_undone(void);
extern void top_get_clr_irq_state(DWORD *bit);
extern void top_set_clr_irq_state(DWORD bit);
extern void top_clr_clr_irq_state(DWORD bit);

extern void top_get_writeback_id(BYTE *id);
extern void top_get_frame_id(BYTE *id);
extern void top_get_lowband_parameter(WORD *para);
extern void top_set_lowband_counter(WORD cnt);
extern void top_set_read_error_addr(void *addr);
extern void top_set_write_error_addr(void *addr);

#endif 
/* end of sw_reg_top.h */
