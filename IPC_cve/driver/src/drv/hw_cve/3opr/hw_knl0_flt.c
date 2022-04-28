/*---------------------------
 * hw_knl0_flt.c
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
void opr_sel_FLT(BYTE power,BYTE co[][5]);
void opr_sel_FLT(BYTE power,BYTE co[][5])
{
	 knl0_set_FLT_power(power);
	 knl0_set_FLT_coeff(co);
	 knl0_set_FLT_opr();
}

/**************************************************/
void opr_rev_FLT(void);
void opr_rev_FLT()
{
	 knl0_clr_FLT_opr();
}

/*************************************************/
void hw_opr_FLT(BYTE *out, BYTE *in, int width, int height,BYTE power,BYTE co[][5]);
void hw_opr_FLT(BYTE *out, BYTE *in, int width, int height,BYTE power,BYTE co[][5])
{
	top_set_wb_addr(out);
	top_set_frm_addr(in,(BYTE *)0);
	top_set_img_size(width,height);
	knl0_set_FLT_power(power);
	knl0_set_FLT_coeff(co);
	knl0_set_FLT_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(1000,10);

	top_set_clr_irq_state(0x01);
	knl0_clr_FLT_opr();
	top_set_start_reg(0x00);
}
/* end of hw_knl0_flt.c */
