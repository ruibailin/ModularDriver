/*---------------------------
 * sw_knl1_trs.c
 *  Created on: Jun 18, 2017
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
static UINT8 get_trs_u8_value(UINT8 input,int ctrl0,int ctrl1);
static UINT8 get_trs_u8_value(UINT8 input,int ctrl0,int ctrl1)
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}DW2B;
	DW2B	dw2b;
	dw2b.dw=ctrl0;

	UINT8 trsL,trsH;
	trsL=dw2b.b[0];
	trsH=dw2b.b[1];

	dw2b.dw=ctrl1;   		/*b[0]:mode, b[1~3]:value0~1*/

	if(input<=trsL)
	{
		if((dw2b.b[0]&0x01)==0)
			return(input);
		else
			return(dw2b.b[1]);
	}
	if(input<=trsH)
	{
		if((dw2b.b[0]&0x02)==0)
			return(input);
		else
			return(dw2b.b[2]);
	}
	else /*input>trsH*/
	{
		if((dw2b.b[0]&0x04)==0)
			return(input);
		else
			return(dw2b.b[3]);
	}

}

/**************************************************/
void sw_knl1_TRS_8(char *out, char *in, int width, int height,int ctrl0,int ctrl1);
void sw_knl1_TRS_8(char *out, char *in, int width, int height,int ctrl0,int ctrl1)
{

	int i,j,k;
	UINT8 value;
	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			value=get_trs_u8_value(in[k],ctrl0,ctrl1);
			out[k]=value;
			k++;
		}
	}
}

/**************************************************/
static UINT8 get_trs_u16u8_value(UINT16 input,int ctrl0,int ctrl1);
static UINT8 get_trs_u16u8_value(UINT16 input,int ctrl0,int ctrl1)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
		BYTE   b[4];
	}DW2B;
	DW2B	dw2b;
	dw2b.dw=ctrl0;

	UINT16 trsL,trsH;
	trsL=dw2b.w[0];
	trsH=dw2b.w[1];

	dw2b.dw=ctrl1;   		/*b[0]:mode, b[1~3]:value0~1*/

	if(input<=trsL)
	{
		if((dw2b.b[0]&0x01)==0)
			return((UINT8)input);
		else
			return(dw2b.b[1]);
	}
	if(input<=trsH)
	{
		if((dw2b.b[0]&0x02)==0)
			return((UINT8)input);
		else
			return(dw2b.b[2]);
	}
	else /*input>trsH*/
	{
		if((dw2b.b[0]&0x04)==0)
			return((UINT8)input);
		else
			return(dw2b.b[3]);
	}

}
/**************************************************/
void sw_knl1_TRS_u16u8(char *out, char *in, int width, int height,int ctrl0,int ctrl1);
void sw_knl1_TRS_u16u8(char *out, char *in, int width, int height,int ctrl0,int ctrl1)
{

	int i,j,k;
	UINT8 value;
	UINT16 *in16;

	in16=(UINT16 *)in;
	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			value=get_trs_u16u8_value(in16[k],ctrl0,ctrl1);
			out[k]=value;
			k++;
		}
	}
}

/**************************************************/
static UINT8 s16tou8(INT16 input);
static UINT8 s16tou8(INT16 input)
{
	if(input<0)
		return(0x00);
	if(input>0xFF)
		return(0xFF);
	return((UINT8)input);
}

/**************************************************/
static UINT8 get_trs_s16u8_value(INT16 input,int ctrl0,int ctrl1);
static UINT8 get_trs_s16u8_value(INT16 input,int ctrl0,int ctrl1)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
		BYTE   b[4];
	}DW2B;
	DW2B	dw2b;
	dw2b.dw=ctrl0;

	INT16 trsL,trsH;
	trsL=dw2b.w[0];
	trsH=dw2b.w[1];

	dw2b.dw=ctrl1;   		/*b[0]:mode, b[1~3]:value0~1*/

	if(input<=trsL)
	{
		if((dw2b.b[0]&0x01)==0)
			return(s16tou8(input));
		else
			return(dw2b.b[1]);
	}
	if(input<=trsH)
	{
		if((dw2b.b[0]&0x02)==0)
			return(s16tou8(input));
		else
			return(dw2b.b[2]);
	}
	else /*input>trsH*/
	{
		if((dw2b.b[0]&0x04)==0)
			return(s16tou8(input));
		else
			return(dw2b.b[3]);
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
static UINT8 get_trs_s16s8_value(INT16 input,int ctrl0,int ctrl1);
static UINT8 get_trs_s16s8_value(INT16 input,int ctrl0,int ctrl1)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
		BYTE   b[4];
	}DW2B;
	DW2B	dw2b;
	dw2b.dw=ctrl0;

	INT16 trsL,trsH;
	trsL=dw2b.w[0];
	trsH=dw2b.w[1];

	dw2b.dw=ctrl1;   		/*b[0]:mode, b[1~3]:value0~1*/

	if(input<=trsL)
	{
		if((dw2b.b[0]&0x01)==0)
			return(s16tos8(input));
		else
			return(dw2b.b[1]);
	}
	if(input<=trsH)
	{
		if((dw2b.b[0]&0x02)==0)
			return(s16tos8(input));
		else
			return(dw2b.b[2]);
	}
	else /*input>trsH*/
	{
		if((dw2b.b[0]&0x04)==0)
			return(s16tos8(input));
		else
			return(dw2b.b[3]);
	}

}

/**************************************************/
void sw_knl1_TRS_16(char *out, char *in, int width, int height,int ctrl0,int ctrl1);
void sw_knl1_TRS_16(char *out, char *in, int width, int height,int ctrl0,int ctrl1)
{
	INT16 *in16;
	in16=(INT16 *)in;

	UINT32 mode;
	mode=(ctrl1&(0x00000001<<3));

	int i,j,k;
	UINT8 value;
	if(mode==0)
	{
		k=0;
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				value=get_trs_s16u8_value(in16[k],ctrl0,ctrl1);
				out[k]=value;
				k++;
			}
		}
	}
	else
	{
		k=0;
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				value=get_trs_s16s8_value(in16[k],ctrl0,ctrl1);
				out[k]=value;
				k++;
			}
		}
	}
}
/* end of sw_knl1_trs.c */
