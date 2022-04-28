/*---------------------------
 * hw_knl1_sum.c
 *  Created on: Jun 23, 2017
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
void opr_sel_SUM8(void);
void opr_sel_SUM8(void)
{
	knl1_set_SUM8_opr();
}
/**************************************************/
void opr_get_SUM8(int *out);
void opr_get_SUM8(int *out)
{
	knl1_get_SUM8_output(out);
}
/**************************************************/
void opr_rev_SUM8(void);
void opr_rev_SUM8()
{
	knl1_clr_SUM8_opr();
}

/*************************************************/
void hw_opr_SUM8(BYTE *out, BYTE *in, int width, int height, int blk0_x, int blk0_y, int blk_w,int blk_h);
void hw_opr_SUM8(BYTE *out, BYTE *in, int width, int height, int blk0_x, int blk0_y, int blk_w,int blk_h)
{
	top_set_wb_addr(out);
	top_set_frm_addr(in,(BYTE *)0);
	top_set_img_size(width,height);
	top_set_blk_size(blk_w,blk_h);
	top_set_blk1_pos(blk0_x,blk0_y);

	knl1_set_SUM8_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(1000,10);

	int *out32;
	out32=(int *)out;
	knl1_get_SUM8_output(out32);

	top_set_clr_irq_state(0x01);
	knl1_clr_SUM8_opr();
	top_set_start_reg(0x00);
}

/**************************************************/
void opr_sel_SUM16(BYTE mode);
void opr_sel_SUM16(BYTE mode)
{
	knl1_set_SUM16_mode(mode);

	knl1_set_SUM16_opr();
}
/**************************************************/
void opr_get_SUM16(long *out);
void opr_get_SUM16(long *out)
{
	knl1_get_SUM16_output(out);
}
/**************************************************/
void opr_rev_SUM16(void);
void opr_rev_SUM16()
{
	knl1_clr_SUM16_opr();
}

/*************************************************/
void hw_opr_SUM16(BYTE *out, BYTE *in, int width, int height, BYTE mode,int blk0_x, int blk0_y, int blk_w,int blk_h);
void hw_opr_SUM16(BYTE *out, BYTE *in, int width, int height, BYTE mode,int blk0_x, int blk0_y, int blk_w,int blk_h)
{
	top_set_wb_addr(out);
	top_set_frm_addr(in,(BYTE *)0);
	top_set_img_size(width,height);
	top_set_blk_size(blk_w,blk_h);
	top_set_blk1_pos(blk0_x,blk0_y);

	knl1_set_SUM16_mode(mode);
	knl1_set_SUM16_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(1000,10);

	knl1_get_SUM16_output((long *)out);

	top_set_clr_irq_state(0x01);
	knl1_clr_SUM16_opr();
	top_set_start_reg(0x00);
}
/* end of hw_knl1_sum.c */
