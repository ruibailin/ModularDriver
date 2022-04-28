/*---------------------------
 * sw_knl2_add.c
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

/**************************************************/
void sw_knl2_ADD(char *out, char *in0, UINT8 *in1, int width, int height,int ctrl);
void sw_knl2_ADD(char *out, char *in0, UINT8 *in1, int width, int height,int ctrl)
{
	int i, j, k;

	UINT16 t0,t1,t2,gain;
	UINT8 t;

	gain=(UINT16)(ctrl&0xFF);
	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			t=in0[k];
			t1=(UINT16)t;
			t=in1[k];
			t2=(UINT16)t;

			t0=t1*gain+t2*(256-gain);
			t0 >>= 8;
			out[k] = (UINT8)t0;
			k++;
		}
	}

}
/* end of sw_knl2_add.c */
