/*---------------------------
 * hw_knl2_add.c
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
void opr_sel_ADD(BYTE mode);
void opr_sel_ADD(BYTE mode)
{
	knl2_set_ADD_mode(mode);
	knl2_set_ADD_opr();
}

/**************************************************/
void opr_rev_ADD(void);
void opr_rev_ADD()
{
	knl2_clr_ADD_opr();
}

/*************************************************/
void hw_opr_ADD(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode);
void hw_opr_ADD(BYTE *out, BYTE *in0, BYTE *in1, int width, int height, BYTE mode)
{
	top_set_wb_addr(out);
	top_set_frm_addr(in0,in1);
	top_set_img_size(width,height);
	knl2_set_ADD_mode(mode);
	knl2_set_ADD_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(1000,10);
	top_set_clr_irq_state(0x01);
	knl2_clr_ADD_opr();
	top_set_start_reg(0x00);
}
/* end of hw_knl2_add.c */
