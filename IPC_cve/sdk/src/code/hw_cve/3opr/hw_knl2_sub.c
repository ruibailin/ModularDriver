/*---------------------------
 * hw_knl2_sub.c
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
void opr_sel_SUB(BYTE mode);
void opr_sel_SUB(BYTE mode)
{
	knl2_set_SUB_mode(mode);
	knl2_set_SUB_opr();
}

/**************************************************/
void opr_rev_SUB(void);
void opr_rev_SUB()
{
	knl2_clr_SUB_opr();
}

/*************************************************/
void hw_opr_SUB(BYTE *out, BYTE *in0, BYTE *in1,int width, int height, BYTE mode);
void hw_opr_SUB(BYTE *out, BYTE *in0, BYTE *in1,int width, int height, BYTE mode)
{
	top_set_wb_addr(out);
	top_set_frm_addr(in0,in1);
	top_set_img_size(width,height);
	knl2_set_SUB_mode(mode);
	knl2_set_SUB_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(1000,10);
	top_set_clr_irq_state(0x01);
	knl2_clr_SUB_opr();
	top_set_start_reg(0x00);
}
/* end of hw_knl2_sub.c */
