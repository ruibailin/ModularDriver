/*---------------------------
 * hw_knl2_var.c
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


#include "c_share.h"

/**************************************************/
void opr_sel_VAR(BYTE mode,BYTE a, BYTE b);
void opr_sel_VAR(BYTE mode,BYTE a, BYTE b)
{

	knl2_set_VAR_mode(mode);
	knl2_set_VAR_input(a, b);
	knl2_set_VAR_opr();
}

/**************************************************/
void opr_get_VAR(long *out);
void opr_get_VAR(long *out)
{
	knl2_get_VAR_output(out);
}
/**************************************************/
void opr_rev_VAR(void);
void opr_rev_VAR()
{
	knl2_clr_VAR_opr();
}

/*************************************************/
void hw_opr_VAR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode, BYTE a, BYTE b, int blk0_x, int blk0_y, int blk1_x, int blk1_y, int blk_w,int blk_h);
void hw_opr_VAR(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode, BYTE a, BYTE b, int blk0_x, int blk0_y, int blk1_x, int blk1_y, int blk_w,int blk_h)
{
	top_set_wb_addr(out);
	top_set_frm_addr(in0,in1);
	top_set_img_size(width,height);
	top_set_blk_size(blk_w,blk_h);
	top_set_blk1_pos(blk0_x,blk0_y);
	top_set_blk2_pos(blk1_x,blk1_y);
	knl2_set_VAR_mode(mode);
	knl2_set_VAR_input(a, b);
	knl2_set_VAR_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(1000,10);
	top_set_clr_irq_state(0x01);
	knl2_get_VAR_output((long *)out);
	knl2_clr_VAR_opr();
	top_set_start_reg(0x00);
}
/* end of hw_knl2_var.c */
