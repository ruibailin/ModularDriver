/*---------------------------
 * sw_knl0_flt.c
 *  Created on: Jun 14, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Filter 5*5
 *FLT should be sign
 *
 *
 *---------------------------
 */

#include "../../code/sw_cve/3opr/c_share.h"
/**************************************************/
static	void ini_FLT5x5_coeff(char coeff[][5]);
static	void ini_FLT5x5_coeff(char coeff[][5])
{
/*	coeff[0][0] = 1;		coeff[0][1] = 2;		coeff[0][2] = 0;		coeff[0][3] = -2;		coeff[0][4] = -1;
	coeff[1][0] = 4;		coeff[1][1] = 8;		coeff[1][2] = 0;		coeff[1][3] = -8;		coeff[1][4] = -4;
	coeff[2][0] = 6;		coeff[2][1] = 12;		coeff[2][2] = 0;		coeff[2][3] = -12;		coeff[2][4] = -6;
	coeff[3][0] = 4;		coeff[3][1] = 8;		coeff[3][2] = 0;		coeff[3][3] = -8;		coeff[3][4] = -4;
	coeff[4][0] = 1;		coeff[4][1] = 2;		coeff[4][2] = 0;		coeff[4][3] = -2;		coeff[4][4] = -1;
*/
	coeff[0][0] = -1;		coeff[0][1] = -4;		coeff[0][2] = -6;		coeff[0][3] = -4;		coeff[0][4] = -1;
	coeff[1][0] = -2;		coeff[1][1] = -8;		coeff[1][2] = -12;		coeff[1][3] = -8;		coeff[1][4] = -2;
	coeff[2][0] = 0;		coeff[2][1] = 0;		coeff[2][2] = 0;		coeff[2][3] = 0;		coeff[2][4] = 0;
	coeff[3][0] = 2;		coeff[3][1] = 8;		coeff[3][2] = 12;		coeff[3][3] = 8;		coeff[3][4] = 2;
	coeff[4][0] = 1;		coeff[4][1] = 4;		coeff[4][2] = 6;		coeff[4][3] = 4;		coeff[4][4] = 1;

}
/**************************************************/
static void filter_output(char *out,int ctrl,int value);
static void filter_output(char *out,int ctrl,int value)
{
	if(value < 0)
	{
      *out = 0;
      return;
	}

	int	temp;
    ctrl &= 0x0F;
    temp = (value >> ctrl);
    if	((temp & 0xffffff00) > 0)
    {
    	*out = 255;
    	return;
    }
	*out = temp & 0xff;
}

/**************************************************/
void sw_knl0_FLT5x5(char *out, char *in, int width, int height,int ctrl, char coeff[][5]);
void sw_knl0_FLT5x5(char *out, char *in, int width, int height,int ctrl, char coeff[][5])
{

	char block[5][5] = { 0 };

	int value;
	ini_FLT5x5_coeff(coeff);
	int i,j,k;
	int num;
	k=0;
    for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			num=knl_get_blk5x5(in,block,i,j,width,height);
			value=knl_conv_blk5x5(block,coeff);
			if(num != 25)
			{
				value /= num;
				value *= 25;
			}

			filter_output(&out[k],ctrl,value);
			k++;
		}
	}
}

/*end of sw_knl0_flt*/
