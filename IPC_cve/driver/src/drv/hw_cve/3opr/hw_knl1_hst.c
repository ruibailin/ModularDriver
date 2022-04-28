/*---------------------------
 * hw_knl1_hst.c
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
void opr_sel_HST(BYTE mode);
void opr_sel_HST(BYTE mode)
{
	knl1_set_HST_mode(mode);
	knl1_set_HST_opr();
}

/**************************************************/
void opr_rev_HST(void);
void opr_rev_HST()
{
	knl1_clr_HST_opr();
}

/*************************************************/
void hw_opr_HST(BYTE *out, BYTE *in, int width, int height, BYTE mode);
void hw_opr_HST(BYTE *out, BYTE *in, int width, int height, BYTE mode)
{
	top_set_wb_addr(out);
	top_set_frm_addr(in,(BYTE *)0);
	top_set_img_size(width,height);
	knl1_set_HST_mode(mode);
	knl1_set_HST_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(1000,10);

	top_set_clr_irq_state(0x01);
	knl1_clr_HST_opr();
	top_set_start_reg(0x00);
}
/* end of hw_knl1_hst.c */
