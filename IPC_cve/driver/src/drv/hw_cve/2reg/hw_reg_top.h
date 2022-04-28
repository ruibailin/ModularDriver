/*---------------------------
 * hw_reg_top.h
 *  Created on: Jun 9, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 **abbreviated Syntax
 * addr-physical address
 * frm-frame
 * img-image
 * blk_block
 * pos-position
  *---------------------------
 */


#ifndef HW_CVE_2REG_HW_REG_TOP_H_
#define HW_CVE_2REG_HW_REG_TOP_H_

#include "h_share.h"

/* ����������ֵ�ģ�һ�ɱ�ʾ�����Ƿ�ɹ�*/
extern void top_ini_base_addr(void *top);
extern void top_ini_sw_reg(void);
extern void top_set_start_reg(DWORD status);
extern void top_set_ddr_addr(void *start,void *end);
extern int top_set_frm_addr(void *frm1, void *frm2);
extern int top_set_wb_addr(void *wb);
extern int top_set_img_size(WORD w,WORD h);
extern int top_set_blk_size(WORD w,WORD h);
extern int top_set_blk1_pos(WORD x,WORD y);
extern int top_set_blk2_pos(WORD x,WORD y);
extern void top_get_irq_state(DWORD *state);
extern int top_wait_cve_done(int sleep,int max);
extern void top_set_clr_irq_state(DWORD bit);
extern void top_wait_cve_clr_irq_state(DWORD bit);

extern void top_set_writeback_id(BYTE id);
extern void top_set_frame_id(BYTE id);
extern void top_set_lowband_parameter(WORD para);
extern void top_get_lowband_counter(WORD *cnt);
extern void top_get_read_error_addr(void *addr);
extern void top_get_write_error_addr(void *addr);

#endif 
/* end of hw_reg_top.h */
