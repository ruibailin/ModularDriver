/*---------------------------
 * hw_knl1_map.c
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
void opr_sel_MAP(BYTE mode, WORD *map);
void opr_sel_MAP(BYTE mode, WORD *map)
{
	knl1_set_MAP_mode(mode);
	int i;
	for(i=0;i<256;i++)
		knl1_set_MAP_write(map[i],(BYTE)i);
	knl1_set_MAP_opr();
}

/**************************************************/
void opr_rev_MAP(void);
void opr_rev_MAP()
{
	knl1_clr_MAP_opr();
}

/*************************************************/
void hw_opr_MAP(BYTE *out, BYTE *in, int width, int height, BYTE mode, WORD *map);
void hw_opr_MAP(BYTE *out, BYTE *in, int width, int height, BYTE mode, WORD *map)
{
	top_set_wb_addr(out);
	top_set_frm_addr(in,(BYTE *)0);
	top_set_img_size(width,height);
	knl1_set_MAP_mode(mode);
	int i;
	for(i=0;i<256;i++)
		knl1_set_MAP_write(map[i],(BYTE)i);
	knl1_set_MAP_opr();
	top_set_start_reg(0x01);

	top_wait_cve_done(1000,10);

	top_set_clr_irq_state(0x01);
	knl1_clr_MAP_opr();
	top_set_start_reg(0x00);
}
/* end of hw_knl1_map.c */
