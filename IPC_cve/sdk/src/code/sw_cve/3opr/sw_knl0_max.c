/*---------------------------
 * sw_knl0_max.c
 *  Created on: Jun 18, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *MAX 3*3
 *MAX should be unsigned operator
 *
 *
 *---------------------------
 */


#include "../../code/sw_cve/3opr/c_share.h"

/**************************************************/
static BYTE get_blk3x3_max(BYTE blk[][3]);
static BYTE get_blk3x3_max(BYTE blk[][3])
{
	int ii,jj;
	BYTE max;

	max=blk[0][0];
	for(ii=0;ii<3;ii++)
		for(jj=0;jj<3;jj++)
			max=MAX(max,blk[ii][jj]);
	return(max);
}

/**************************************************/
void sw_knl0_MAX3x3(char *out, char *in, int width, int height);
void sw_knl0_MAX3x3(char *out, char *in, int width, int height)
{
	BYTE block[3][3];
	BYTE value;

	int i, j, k;
	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			knl_get_blk3x3(in,block,i,j,width,height);
			value=get_blk3x3_max(block);

			out[k]=(char)value;
			k++;
		}
	}
}

/* end of sw_knl0_max.c */
