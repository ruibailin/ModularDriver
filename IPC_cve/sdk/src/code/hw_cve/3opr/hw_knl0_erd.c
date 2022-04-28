/*---------------------------
 * hw_knl0_erd.c
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
void opr_sel_ERD5(BYTE mode);
void opr_sel_ERD5(BYTE mode)
{
	knl0_set_ERD5x5_mode(mode);
	knl0_set_ERD5x5_opr();
}

/**************************************************/
void opr_rev_ERD5(void);
void opr_rev_ERD5()
{
	knl0_clr_ERD5x5_opr();
}
/*************************************************/
void hw_opr_ERD5(BYTE *out, BYTE *in, int width, int height, BYTE mode);
void hw_opr_ERD5(BYTE *out, BYTE *in, int width, int height, BYTE mode)
{
	top_set_wb_addr(out);
	top_set_frm_addr(in,(BYTE *)0);
	top_set_img_size(width,height);
	knl0_set_ERD5x5_mode(mode);
	knl0_set_ERD5x5_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(1000,10);

	top_set_clr_irq_state(0x01);
	knl0_clr_ERD5x5_opr();
	top_set_start_reg(0x00);
}
/**************************************************/
void opr_sel_ERD3(BYTE mode);
void opr_sel_ERD3(BYTE mode)
{
	 knl0_set_ERD3x3_mode(mode);
	 knl0_set_ERD3x3_opr();
}

/**************************************************/
void opr_rev_ERD3(void);
void opr_rev_ERD3()
{
	 knl0_clr_ERD3x3_opr();
}

/*************************************************/
void hw_opr_ERD3(BYTE *out, BYTE *in, int width, int height, BYTE mode);
void hw_opr_ERD3(BYTE *out, BYTE *in, int width, int height, BYTE mode)
{
	top_set_wb_addr(out);
	top_set_frm_addr(in,(BYTE *)0);
	top_set_img_size(width,height);
	knl0_set_ERD3x3_mode(mode);
	knl0_set_ERD3x3_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(1000,10);

	top_set_clr_irq_state(0x01);
	knl0_clr_ERD3x3_opr();
	top_set_start_reg(0x00);
}
/* end of hw_knl0_erd.c */
