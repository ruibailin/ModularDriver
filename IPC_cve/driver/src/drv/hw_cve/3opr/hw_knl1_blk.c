/*---------------------------
 * hw_knl1_blk.c
 *  Created on: Jun 22, 2017
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
void opr_sel_BLK(BYTE mode, BYTE shift);
void opr_sel_BLK(BYTE mode, BYTE shift)
{
	knl1_set_BLK16_mode(mode);
	knl1_set_BLK16_power(shift);
	knl1_set_BLK16_opr();
}

/**************************************************/
void opr_rev_BLK(void);
void opr_rev_BLK()
{
	knl1_clr_BLK16_opr();
}

/*************************************************/
void hw_opr_BLK(BYTE *out, BYTE *in, int width, int height, BYTE mode, BYTE shift);
void hw_opr_BLK(BYTE *out, BYTE *in, int width, int height, BYTE mode, BYTE shift)
{
	top_set_wb_addr(out);
	top_set_frm_addr(in,(BYTE *)0);
	top_set_img_size(width,height);
	knl1_set_BLK16_mode(mode);
	knl1_set_BLK16_power(shift);
	knl1_set_BLK16_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(1000,10);

	top_set_clr_irq_state(0x01);
	knl1_clr_BLK16_opr();
	top_set_start_reg(0x00);
}
/* end of hw_knl1_blk.c */
