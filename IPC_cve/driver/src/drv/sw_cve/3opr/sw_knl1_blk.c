/*---------------------------
 * sw_knl1_blk.c
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
static UINT8 u16tou8(UINT16 input);
static UINT8 u16tou8(UINT16 input)
{
	if(input>0xFF)
		return(0xFF);
	return((UINT8)input);
}
/**************************************************/
static void sw_knl1_BLK_u16u8(UINT8 *out, UINT16 *in, int width, int height,int shift);
static void sw_knl1_BLK_u16u8(UINT8 *out, UINT16 *in, int width, int height,int shift)
{
	int i, j,k;
	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			out[k] = u16tou8(in[k] >> shift);
			k++;
		}
	}
}
/**************************************************/
static INT8 s16tos8(INT16 input);
static INT8 s16tos8(INT16 input)
{
	if(input<-128)
		return(-128);
	if(input>127)
		return(127);
	return((INT8)input);
}
/**************************************************/
static void sw_knl1_BLK_s16s8(INT8 *out, INT16 *in, int width, int height,int shift);
static void sw_knl1_BLK_s16s8(INT8 *out, INT16 *in, int width, int height,int shift)
{
	int i, j,k;
	INT16 temp;
	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			temp=in[k];
			if(temp>=0)
			{
				temp >>= shift;
				out[k] = s16tos8(temp);
			}
			else
			{
				temp=0-temp;
				temp >>= shift;
				temp=0-temp;
				out[k] = s16tos8(temp);
			}
			k++;
		}
	}
}

/**************************************************/
static UINT8 s16tou8(INT16 input);
static UINT8 s16tou8(INT16 input)
{
	if(input>255)
		return(255);
	input &= 0xFF;
	return((UINT8)input);
}
/**************************************************/
static void sw_knl1_BLK_s16u8(UINT8 *out, INT16 *in, int width, int height,int shift);
static void sw_knl1_BLK_s16u8(UINT8 *out, INT16 *in, int width, int height,int shift)
{
	int i, j,k;
	INT16 temp;
	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			temp=in[k];
			if(temp>=0)
			{
				temp >>= shift;
				out[k] = s16tou8(temp);
			}
			else
			{
				temp=0-temp;
				temp >>= shift;
				out[k] = s16tou8(temp);
			}
			k++;
		}
	}
}
/**************************************************/
void sw_knl1_BLK(char *out, char *in, int width, int height,int ctrl);
void sw_knl1_BLK(char *out, char *in, int width, int height,int ctrl)
{
	UINT32 mode;

	mode=(ctrl&(0x00000003<<4))>>4;

	ctrl &= 0x0f;
	switch(mode)
	{
	case	0:
		sw_knl1_BLK_u16u8(out,(UINT16 *)in,width,height,ctrl);
		break;
	case    1:
		sw_knl1_BLK_s16s8((INT8 *)out,(INT16 *)in,width,height,ctrl);
		break;
	case    2:
		sw_knl1_BLK_s16u8(out,(INT16 *)in,width,height,ctrl);
		break;
	default:
		break;
	}
}
/* end of sw_knl1_blk.c */
