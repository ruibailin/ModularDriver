/*---------------------------
 * hw_top_opr.c
 *  Created on: Jun 22, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *�ṩһЩ����ȫ�ֲ����ĺ���
 *Define some functions to be shared with all operators
 *
 *
 *---------------------------
 */


#include "c_share.h"

/**************************************************/
int opr_set_out_para(UINT8 *out);
int opr_set_out_para(UINT8 *out)
{
	int r;
	r=top_set_wb_addr(out);
	return(r);
}
/**************************************************/
int opr_set_frm_para(UINT8 *in0, UINT8 *in1,int width, int height);
int opr_set_frm_para(UINT8 *in0, UINT8 *in1,int width, int height)
{
	int r;
	r=top_set_frm_addr(in0,in1);
	if(r !=0 ) return(r);
	r=top_set_img_size((WORD)width,(WORD)height);
	if(r !=0 ) return(r);
	return(0);
}
/**************************************************/
int opr_set_blk_para(int blk0_x, int blk0_y, int blk1_x, int blk1_y, int blk_w,int blk_h);
int opr_set_blk_para(int blk0_x, int blk0_y, int blk1_x, int blk1_y, int blk_w,int blk_h)
{
	int r;
	r=top_set_blk1_pos(blk0_x, blk0_y);
	if(r !=0 ) return(r);
	r=top_set_blk2_pos(blk1_x, blk1_y);
	if(r !=0 ) return(r);
	r=top_set_img_size(blk_w, blk_h);
	if(r !=0 ) return(r);
	return(0);
}

/**************************************************/
void opr_set_cve_run();
void opr_set_cve_run()
{
	 top_set_start_reg(0x01);
}
/**************************************************/
void opr_clr_cve_run();
void opr_clr_cve_run()
{
	 top_set_start_reg(0x00);
}

/**************************************************/
int opr_is_cve_done();
int opr_is_cve_done()
{
	DWORD state;
	top_get_irq_state(&state);
	if((state & 0x80000000)==0)
		return(0);
	top_set_clr_irq_state(0x01);
	return(1);
}

/**************************************************/
int opr_is_cve_error();
int opr_is_cve_error()
{
	DWORD state;
	top_get_irq_state(&state);
	state &= 0x00000FFF;
	if(state == 0)
		return(0);
	top_set_clr_irq_state(0x02);
	return(state);
}


/* end of hw_top_opr.c */
