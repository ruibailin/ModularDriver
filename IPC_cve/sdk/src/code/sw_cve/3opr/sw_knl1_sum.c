/*---------------------------
 * sw_knl1_sum.c
 *  Created on: Jun 18, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *SUM8 is signed Operator
 *
 *
 *
 *---------------------------
 */


#include "../../code/sw_cve/3opr/c_share.h"

/**************************************************/
void sw_knl1_SUM_8(char *out, char *in, int width, int height, int offsetX, int offsetY, int blockW, int blockH);
void sw_knl1_SUM_8(char *out, char *in, int width, int height, int offsetX, int offsetY, int blockW, int blockH)
{
	int i, j;
	int xPos, yPos;
	int sum;

    sum = 0;

    for (i = 0; i < blockH; i++)
	{
		for (j = 0; j < blockW; j++)
		{
			yPos = i + offsetY;
			xPos = j + offsetX;

			sum += in[yPos*width + xPos];
		}
	}

	*((int *)out)=sum;
}

/**************************************************/
void sw_knl1_SUM_16(char *out, char *in, int width, int height, int ctrl, int offsetX, int offsetY, int blockW, int blockH);
void sw_knl1_SUM_16(char *out, char *in, int width, int height, int ctrl, int offsetX, int offsetY, int blockW, int blockH)
{
	int i, j;
	int xPos, yPos;
	INT64 sum;

	sum = 0;

	if((ctrl&0x01)==0)
	{
		UINT16 *uin16;
		uin16=(UINT16 *)in;
	    sum = 0;
		for (i = 0; i < blockH; i++)
		{
			for (j = 0; j < blockW; j++)
			{
				yPos = i + offsetY;
				xPos = j + offsetX;

				sum += uin16[yPos*width + xPos];
			}
		}
	}
	else
	{
		INT16 *sin16;
		sin16=(INT16 *)in;
		for (i = 0; i < blockH; i++)
		{
			for (j = 0; j < blockW; j++)
			{
				yPos = i + offsetY;
				xPos = j + offsetX;

				sum += sin16[yPos*width + xPos];
			}
		}
	}

	*((INT64 *)out)=sum;
}
/* end of sw_knl1_sum.c */
