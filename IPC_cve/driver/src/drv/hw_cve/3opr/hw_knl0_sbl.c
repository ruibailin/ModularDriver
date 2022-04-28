/*---------------------------
 * hw_knl0_sbl.c
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
void opr_sel_SBL(BYTE output,BYTE angle,BYTE ang,BYTE mag,BYTE hco[][5],BYTE vco[][5]);
void opr_sel_SBL(BYTE output,BYTE angle,BYTE ang,BYTE mag,BYTE hco[][5],BYTE vco[][5])
{
	knl0_set_SBL_mode_output(output);
	knl0_set_SBL_mode_angle(angle);
	knl0_set_SBL_power(ang,mag);
	knl0_set_SBL_hcoeff(hco);
	knl0_set_SBL_vcoeff(vco);
	knl0_set_SBL_opr();
}

/**************************************************/
void opr_rev_SBL(void);
void opr_rev_SBL()
{
	knl0_clr_SBL_opr();
}
/**************************************************/
void hw_opr_SBL(BYTE *out, BYTE *in, int width, int height,BYTE output,BYTE angle,BYTE ang,BYTE mag,BYTE hco[][5],BYTE vco[][5]);
void hw_opr_SBL(BYTE *out, BYTE *in, int width, int height,BYTE output,BYTE angle,BYTE ang,BYTE mag,BYTE hco[][5],BYTE vco[][5])
{
	top_set_wb_addr(out);
	top_set_frm_addr(in,(BYTE *)0);
	top_set_img_size(width,height);

	knl0_set_SBL_mode_output(output);
	knl0_set_SBL_mode_angle(angle);
	knl0_set_SBL_power(ang,mag);
	knl0_set_SBL_hcoeff(hco);
	knl0_set_SBL_vcoeff(vco);
	knl0_set_SBL_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(2000,20);

	top_set_clr_irq_state(0x01);
	knl0_clr_SBL_opr();
	top_set_start_reg(0x00);
}
/* end of hw_knl0_sbl.c */
