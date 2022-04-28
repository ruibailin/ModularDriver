/*---------------------------
 * hw_knl0_med.c
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
void opr_sel_MED(void);
void opr_sel_MED(void)
{
	 knl0_set_MED3x3_opr();
}

/**************************************************/
void opr_rev_MED(void);
void opr_rev_MED()
{
	 knl0_clr_MED3x3_opr();
}

/*************************************************/
void hw_opr_MED(BYTE *out, BYTE *in, int width, int height);
void hw_opr_MED(BYTE *out, BYTE *in, int width, int height)
{
	top_set_wb_addr(out);
	top_set_frm_addr(in,(BYTE *)0);
	top_set_img_size(width,height);
	knl0_set_MED3x3_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(1000,10);
	top_set_clr_irq_state(0x01);
	knl0_clr_MED3x3_opr();
	top_set_start_reg(0x00);
}
/* end of hw_knl0_med.c */
