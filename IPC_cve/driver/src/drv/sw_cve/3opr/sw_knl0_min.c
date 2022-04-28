/*---------------------------
 * sw_knl0_min.c
 *  Created on: Jun 18, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *MIN should be a unsigned operator
 *
 *
 *
 *---------------------------
 */


#include "../../code/sw_cve/3opr/c_share.h"

/**************************************************/
/*can't use knl_get_blk3x3()*/
static int min_get_blk3x3(BYTE *in,BYTE block[][3],int i,int j,int width,int height);
static int min_get_blk3x3(BYTE *in,BYTE block[][3],int i,int j,int width,int height)
{
	int m,n;
	int xPos, yPos;
	int num;

	num=0;
	for (m = 0; m < 3; m++)
	{
		for (n = 0; n < 3; n++)
		{
			yPos = i + m-1;
			xPos = j + n-1;
			block[m][n]=0x7F;		/*avoid invalid point to impact min value*/

			if(yPos< 0) continue;
			if(xPos< 0) continue;

			if(yPos >= height) continue;
			if(xPos >= width) continue;

			block[m][n] = in[yPos*width + xPos];
			num ++;
		}
	}
	return(num);
}

/**************************************************/
static BYTE get_blk3x3_min(BYTE blk[][3]);
static BYTE get_blk3x3_min(BYTE blk[][3])
{
	int ii,jj;
	BYTE min;

	min=blk[0][0];
	for(ii=0;ii<3;ii++)
		for(jj=0;jj<3;jj++)
		{
			min=MIN(min,blk[ii][jj]);
		}
	return(min);
}


/**************************************************/
void sw_knl0_MIN3x3(char *out, char *in, int width, int height);
void sw_knl0_MIN3x3(char *out, char *in, int width, int height)
{
	char block[3][3];
	BYTE value;

	int i, j, k;
	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			min_get_blk3x3(in,block,i,j,width,height);
			value=get_blk3x3_min(block);

			out[k]=(char)value;
			k++;
		}
	}
}
/* end of sw_knl0_min.c */
