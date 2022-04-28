/*---------------------------
 * sw_knl1_hst.c
 *  Created on: Jun 19, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Unsigned Operator
 *
 *
 *
 *---------------------------
 */


#include "../../code/sw_cve/3opr/c_share.h"

/**************************************************/
void sw_knl1_HST(char *out, char *in, int width, int height, int ctrl);
void sw_knl1_HST(char *out, char *in, int width, int height, int ctrl)
{
	int i,j,k;
	BYTE val;

	UINT32 *out32;
	out32=(UINT32 *)out;
	for (i = 0; i < 256; i++)
	{
		out32[i] = 0;
	}

	k=0;
	ctrl &= 0x07;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			val=(BYTE)in[k];
			switch (ctrl)
			{
			case 0:
				out[(val >> 5)] += 1;
				break;
			case 1:
				out[(val >> 4)] += 1;
				break;
			case 2:
				out[(val >> 3)] += 1;
				break;
			case 3:
				out[(val >> 2)] += 1;
				break;
			case 4:
				out[(val >> 1)] += 1;
				break;
			case 5:
				out[(val >> 0)] += 1;
				break;
			default:
				out[(val >> 0)] += 1;
				break;
			}
			k++;
		}
	}
}
/* end of sw_knl1_hst.c */
