/*---------------------------
 * sw_knl2_sub.c
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
void sw_knl2_SUB(char *out, char *in0, char *in1, int width, int height,int ctrl);
void sw_knl2_SUB(char *out, char *in0, char *in1, int width, int height,int ctrl)
{
	int i, j, k;
	UINT8 t;

	ctrl &= 0x01;
	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			t=(BYTE)in0[k]-(BYTE)in1[k];
			if(ctrl==0)
			{
				out[k] = ABS(t);
			}
			else
			{
				if(t>=0)
					out[k]=(t>>1);
				else
				{
					t=0x00-t;
					t >>= 1;
					out[k]=0x00-t;
				}
			}
			k++;
		}
	}

}
/* end of sw_knl2_sub.c */
