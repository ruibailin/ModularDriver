/*---------------------------
 * hw_knl1_trs.c
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
void opr_sel_TRS8(BYTE low,BYTE high,BYTE vmode,BYTE v0,BYTE v1,BYTE v2);
void opr_sel_TRS8(BYTE low,BYTE high,BYTE vmode,BYTE v0,BYTE v1,BYTE v2)
{
	knl1_set_TRS8_mode(vmode);
	knl1_set_TRS8_trs(low,high);
	knl1_set_TRS8_value(v0,v1,v2);
	knl1_set_TRS8_opr();
}

/**************************************************/
void opr_rev_TRS8(void);
void opr_rev_TRS8()
{
	knl1_clr_TRS8_opr();
}

/*************************************************/
void hw_opr_TRS8(BYTE *out, BYTE *in, int width, int height, BYTE low,BYTE high,BYTE vmode,BYTE v0,BYTE v1,BYTE v2);
void hw_opr_TRS8(BYTE *out, BYTE *in, int width, int height, BYTE low,BYTE high,BYTE vmode,BYTE v0,BYTE v1,BYTE v2)
{
	top_set_wb_addr(out);
	top_set_frm_addr(in,(BYTE *)0);
	top_set_img_size(width,height);
	knl1_set_TRS8_mode(vmode);
	knl1_set_TRS8_trs(low,high);
	knl1_set_TRS8_value(v0,v1,v2);
	knl1_set_TRS8_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(2000,10);

	top_set_clr_irq_state(0x01);
	knl1_clr_TRS8_opr();
	top_set_start_reg(0x00);
}

/**************************************************/
void opr_sel_TRS16(BYTE low,BYTE high,BYTE smode,BYTE vmode,BYTE v0,BYTE v1,BYTE v2);
void opr_sel_TRS16(BYTE low,BYTE high,BYTE smode,BYTE vmode,BYTE v0,BYTE v1,BYTE v2)
{
	knl1_set_TRS16_mode_sign(smode);
	knl1_set_TRS16_mode_value(vmode);
	knl1_set_TRS16_trs(low,high);
	knl1_set_TRS16_value(v0,v1,v2);
	knl1_set_TRS16_opr();
}

/**************************************************/
void opr_rev_TRS16(void);
void opr_rev_TRS16()
{
	knl1_clr_TRS16_opr();
}

/*************************************************/
void hw_opr_TRS16(BYTE *out, BYTE *in, int width, int height, WORD low,WORD high,BYTE smode,BYTE vmode,BYTE v0,BYTE v1,BYTE v2);
void hw_opr_TRS16(BYTE *out, BYTE *in, int width, int height, WORD low,WORD high,BYTE smode,BYTE vmode,BYTE v0,BYTE v1,BYTE v2)
{
	top_set_wb_addr(out);
	top_set_frm_addr(in,(BYTE *)0);
	top_set_img_size(width,height);
	knl1_set_TRS16_mode_sign(smode);
	knl1_set_TRS16_mode_value(vmode);
	knl1_set_TRS16_trs(low,high);
	knl1_set_TRS16_value(v0,v1,v2);
	knl1_set_TRS16_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(2000,10);

	top_set_clr_irq_state(0x01);
	knl1_clr_TRS16_opr();
	top_set_start_reg(0x00);
}
/* end of hw_knl1_trs.c */
