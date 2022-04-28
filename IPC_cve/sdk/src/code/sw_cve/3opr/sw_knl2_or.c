/*---------------------------
 * sw_knl2_or.c
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
void sw_knl2_OR(char *out, char *in0, char *in1, int width, int height);
void sw_knl2_OR(char *out, char *in0, char *in1, int width, int height)
{
	int i, j, k;

	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			out[k] = (BYTE)in0[k] | (BYTE)in1[k];
			k++;
		}
	}

}
/* end of sw_knl2_or.c */
