/*---------------------------
 * sw_knl1_map.c
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
void sw_knl1_MAP(char *out, char *in, int width, int height, int ctrl, UINT16 *LUT);
void sw_knl1_MAP(char *out, char *in, int width, int height, int ctrl, UINT16 *LUT)
{
	int i,j,k;
	BYTE val,temp;

	k=0;
	if((ctrl&0x01)==0)
	{
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				temp=(BYTE)in[k];
				val=LUT[temp];
				out[k] =(char)val;
				k++;
			}
		}

	}
	else
	{
		UINT16 *out16,*LUT16;
		out16=(UINT16 *)out;
		LUT16=(UINT16 *)LUT;
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				val=(BYTE)in[k];
				out16[k] = LUT16[val];
				k++;
			}
		}
	}
}

/* end of sw_knl1_map.c */
