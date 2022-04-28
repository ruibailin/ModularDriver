/*---------------------------
 * sw_knl2_var.c
 *  Created on: Jun 19, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#include "../../code/sw_cve/3opr/c_share.h"

void sw_knl2_VAR(char *out,char *in0, char *in1, int w, int h, int ctrl,int blk0_x, int blk0_y, int blk1_x, int blk1_y, int blk_w,int blk_h);
void sw_knl2_VAR(char *out,char *in0, char *in1, int w, int h, int ctrl,int blk0_x, int blk0_y, int blk1_x, int blk1_y, int blk_w,int blk_h)
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}DW2B;
	DW2B	dw2b;
	dw2b.dw=ctrl;
	UINT8 avg0,avg1,mode;
	avg0=dw2b.b[0];
	avg1=dw2b.b[1];
	mode=dw2b.b[3]&0x01;

	int blk0_xPos, blk0_yPos;
	int blk1_xPos, blk1_yPos;

	INT64 sum;
	int t0,t1,t2,t3;
	t1=avg0;
	t3=avg1;

	sum = 0;
	int i, j, k,l,val;
    for (i = 0; i < blk_h; i++)
	{
		for (j = 0; j < blk_w; j++)
		{
			blk0_yPos = i + blk0_y;
			blk0_xPos = j + blk0_x;
            blk1_yPos = i + blk1_y;
			blk1_xPos = j + blk1_x;

			k=blk0_yPos*w + blk0_xPos;
			l=blk1_yPos*w + blk1_xPos;

			t0=(BYTE)in0[k];
			t0 &= 0xFF;
			t2=(BYTE)in1[l];
			t2 &= 0xFF;

			sum += (t0 - t1)*(t2 - t3);
		}
	}

    *(long *)out=sum;
}


/* end of sw_knl2_var.c */
