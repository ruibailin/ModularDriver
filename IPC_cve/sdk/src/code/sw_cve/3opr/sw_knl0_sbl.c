/*---------------------------
 * sw_knl0_sbl.c
 *  Created on: Jun 16, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Sobel 5*5
 *Sobel 3*3
 *Signed Operator
 *
 *---------------------------
 */

#include "../../code/sw_cve/3opr/c_share.h"

/**************************************************/
static	void ini_SBL5x5_coeff(char hCoeff[][5],char vCoeff[][5]);
static	void ini_SBL5x5_coeff(char hCoeff[][5],char vCoeff[][5])
{
	hCoeff[0][0] = 1;		hCoeff[0][1] = 2;		hCoeff[0][2] = 0;		hCoeff[0][3] = -2;		hCoeff[0][4] = -1;
	hCoeff[1][0] = 4;		hCoeff[1][1] = 8;		hCoeff[1][2] = 0;		hCoeff[1][3] = -8;		hCoeff[1][4] = -4;
	hCoeff[2][0] = 6;		hCoeff[2][1] = 12;		hCoeff[2][2] = 0;		hCoeff[2][3] = -12;		hCoeff[2][4] = -6;
	hCoeff[3][0] = 4;		hCoeff[3][1] = 8;		hCoeff[3][2] = 0;		hCoeff[3][3] = -8;		hCoeff[3][4] = -4;
	hCoeff[4][0] = 1;		hCoeff[4][1] = 2;		hCoeff[4][2] = 0;		hCoeff[4][3] = -2;		hCoeff[4][4] = -1;

	vCoeff[0][0] = -1;		vCoeff[0][1] = -4;		vCoeff[0][2] = -6;		vCoeff[0][3] = -4;		vCoeff[0][4] = -1;
	vCoeff[1][0] = -2;		vCoeff[1][1] = -8;		vCoeff[1][2] = -12;		vCoeff[1][3] = -8;		vCoeff[1][4] = -2;
	vCoeff[2][0] = 0;		vCoeff[2][1] = 0;		vCoeff[2][2] = 0;		vCoeff[2][3] = 0;		vCoeff[2][4] = 0;
	vCoeff[3][0] = 2;		vCoeff[3][1] = 8;		vCoeff[3][2] = 12;		vCoeff[3][3] = 8;		vCoeff[3][4] = 2;
	vCoeff[4][0] = 1;		vCoeff[4][1] = 4;		vCoeff[4][2] = 6;		vCoeff[4][3] = 4;		vCoeff[4][4] = 1;
}

/**************************************************/
static	short int shift_sobel_dword(int hv32, int ctrl);
static	short int shift_sobel_dword(int hv32, int ctrl)
{
	int shift;
	shift=(ctrl&(0x0000000F<<4))>>4;
	if (hv32 >= 0)
	{
		hv32 >>= shift;
	}
	else
	{
		hv32 = 0x00-hv32;
		hv32 >>= shift;
		hv32 = 0x00-hv32;
	}

	short int hv16;
	hv16 = (short int)hv32;
	return(hv16);
}
/**************************************************/
static	char get_sobel_mag(short int h16, short int v16,int ctrl);
static	char get_sobel_mag(short int h16, short int v16,int ctrl)
{
	if (h16 < 0)
		h16 = 0- h16;
	if (v16 < 0)
		v16 = 0- v16;
	short int hv16;
	hv16=h16+v16;

	int	shift;
	shift=(ctrl&0x0000000F);		/*magnitude shift*/
	hv16 >>= shift;

	char ma8;
	ma8=(char)hv16;

	return(ma8);
}

/**************************************************/
static int	get_quadrant(short int h16, short int v16);
static int	get_quadrant(short int h16, short int v16)
{
	int Quadrant;
	if (h16 >= 0)
		if (v16 >= 0)
			Quadrant = 0;
		else
			Quadrant = 3;
	else
		if (v16 >= 0)
			Quadrant = 1;
		else
			Quadrant = 2;
	return(Quadrant);
}
static int	get_greaterh(short int h16, short int v16);
static int	get_greaterh(short int h16, short int v16)
{
	int GreaterH;
	if (ABS(h16) >= ABS(v16))
		GreaterH = 1;
	else
		GreaterH = 0;
	return(GreaterH);
}
/**************************************************/
static char	get_max_angle(int value);
static char	get_max_angle(int value)
{
	char angle;
	switch (value)
	{
	case 0://67.5
		angle = 13;
		break;
	case 1://22.5
		angle = 0;
		break;
	case 2://112.5
		angle = 12;
		break;
	case 3://157.5
		angle = 9;
		break;
	case 4://247.5
		angle = 5;
		break;
	case 5://202.5
		angle = 8;
		break;
	case 6://292.5
		angle = 4;
		break;
	case 7://337.5
		angle = 1;
		break;
	default:
		break;
	}
	return(angle);
}
/**************************************************/
static char	get_min_angle(int value);
static char	get_min_angle(int value)
{
	char angle;
	switch (value)
	{
	case 0://67.5
		angle = 14;// 7;
		break;
	case 1://22.5
		angle = 15;// 7;
		break;
	case 2://112.5
		angle = 11;// 5;
		break;
	case 3://157.5
		angle = 10;// 5;
		break;
	case 4://247.5
		angle = 6;// 3;
		break;
	case 5://202.5
		angle = 7;// 3;
		break;
	case 6://292.5
		angle = 3;// 1;
		break;
	case 7://337.5
		angle = 2;// 1;
		break;
	default:
		break;
	}
	return(angle);
}
/**************************************************/
static char get_sobel_ang(short int h16, short int v16,int ctrl);
static char get_sobel_ang(short int h16, short int v16,int ctrl)
{


	int Quadrant;
	Quadrant=get_quadrant(h16,v16);

	int GreaterH;
	GreaterH=get_greaterh(h16,v16);

	int maxV, minV;

	maxV = (MAX(ABS(h16), ABS(v16)));
	maxV *= 106;
	minV = (MIN(ABS(h16), ABS(v16)));
	minV *= 256;

	char angle;
	if(maxV>minV)
		angle=get_max_angle((Quadrant << 1) | GreaterH);
	else
		angle=get_min_angle((Quadrant << 1) | GreaterH);

	int mode;
	mode =(ctrl&(0x00000001<<8))>>8;

	if(mode==0)
		angle >>= 1;		/*8bit mode*/

	return(angle);
}

/**************************************************/
#define	MAG_OUPUT_ONLY	0
#define	ANG_OUPUT_ONLY	1
#define	MAG_AND_ANG		2
#define	H_OUPUT_ONLY	3
#define	V_OUPUT_ONLY	4
#define	H_AND_V			5
static void get_sobel_output(char *out,int ctrl,char angbuf,char magbuf,short int hbuf,short int vbuf);
static void get_sobel_output(char *out,int ctrl,char angbuf,char magbuf,short int hbuf,short int vbuf)
{
	char	*out8;
	short int	*out16;
	int		mode;
	out8=(char *)out;
	out16=(short int *)out;

	mode=(ctrl&(0x00000003<<9))>>9;
	switch(mode)
	{
	case	MAG_OUPUT_ONLY:
		*out8=magbuf;
		out8++;
		break;
	case	ANG_OUPUT_ONLY:
		*out8=angbuf;
		out8++;
		break;
	case	MAG_AND_ANG:
		*out8=magbuf;
		out8++;
		*out8=angbuf;
		out8++;
		break;
	case	H_OUPUT_ONLY:
		*out16=hbuf;
		out16++;
		break;
	case	V_OUPUT_ONLY:
		*out16=vbuf;
		out16++;
		break;
	case	H_AND_V:
		*out16=hbuf;
		out16++;
		*out16=vbuf;
		out16++;
		break;
	default:
		break;

	}

}
/**************************************************/
void sw_knl0_SBL5x5(char *out, char *in, int width, int height,int ctrl, char hCoeff[][5],char vCoeff[][5]);
void sw_knl0_SBL5x5(char *out, char *in, int width, int height,int ctrl, char hCoeff[][5],char vCoeff[][5])
{
	ini_SBL5x5_coeff(hCoeff,vCoeff);

	char	block[5][5];
	int	h32,v32;
	short int	h16,v16;
	char	m8,a8;

	int	i,j,k;
	int num;
	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			num=knl_get_blk5x5(in,block,i,j,width,height);
			h32=knl_conv_blk5x5(block,hCoeff);
			v32=knl_conv_blk5x5(block,vCoeff);
			if(num != 25)
			{
				h32 /= num;
				h32 *= 25;
				v32 /= num;
				v32 *= 25;
			}

			h16=shift_sobel_dword(h32,ctrl);
			v16=shift_sobel_dword(h32,ctrl);
			m8=get_sobel_mag(h16,v16,ctrl);
			a8=get_sobel_ang(h16,v16,ctrl);
			get_sobel_output(&out[k],ctrl,a8,m8,h16,v16);
			k++;
		}
	}
}

/**************************************************/
static	void ini_SBL3x3_coeff( char hCoeff[][5],char vCoeff[][5]);
static	void ini_SBL3x3_coeff( char hCoeff[][5],char vCoeff[][5])
{
	hCoeff[0][0] = 0;		hCoeff[0][1] = 0;		hCoeff[0][2] = 0;		hCoeff[0][3] = 0;		hCoeff[0][4] = 0;
	hCoeff[1][0] = 0;		hCoeff[1][1] = 1;		hCoeff[1][2] = 0;		hCoeff[1][3] = -1;		hCoeff[1][4] = 0;
	hCoeff[2][0] = 0;		hCoeff[2][1] = 2;		hCoeff[2][2] = 0;		hCoeff[2][3] = -2;		hCoeff[2][4] = 0;
	hCoeff[3][0] = 0;		hCoeff[3][1] = 1;		hCoeff[3][2] = 0;		hCoeff[3][3] = -1;		hCoeff[3][4] = 0;
	hCoeff[4][0] = 0;		hCoeff[4][1] = 0;		hCoeff[4][2] = 0;		hCoeff[4][3] = 0;		hCoeff[4][4] = 0;

	vCoeff[0][0] = 0;		vCoeff[0][1] = 0;		vCoeff[0][2] = 0;		vCoeff[0][3] = 0;		vCoeff[0][4] = 0;
	vCoeff[1][0] = 0;		vCoeff[1][1] = 1;		vCoeff[1][2] = 2;		vCoeff[1][3] = 1;		vCoeff[1][4] = 0;
	vCoeff[2][0] = 0;		vCoeff[2][1] = 0;		vCoeff[2][2] = 0;		vCoeff[2][3] = 0;		vCoeff[2][4] = 0;
	vCoeff[3][0] = 0;		vCoeff[3][1] = -1;		vCoeff[3][2] = -2;		vCoeff[3][3] = -1;		vCoeff[3][4] = 0;
	vCoeff[4][0] = 0;		vCoeff[4][1] = 0;		vCoeff[4][2] = 0;		vCoeff[4][3] = 0;		vCoeff[4][4] = 0;
}
void sw_knl0_SBL3x3(char *out, char *in, int width, int height,int ctrl, char hCoeff[][5],char vCoeff[][5]);
void sw_knl0_SBL3x3(char *out, char *in, int width, int height,int ctrl, char hCoeff[][5],char vCoeff[][5])
{
	ini_SBL3x3_coeff(hCoeff,vCoeff);

	char	block[3][3];
	int	h32,v32;
	short int	h16,v16;
	char	m8,a8;

	int	i,j,k;
	int num;
	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			num=knl_get_blk3x3(in,block,i,j,width,height);
			h32=knl_conv_blk3x3(block,hCoeff);
			v32=knl_conv_blk3x3(block,vCoeff);
			if(num != 9)
			{
				h32 /= num;
				h32 *= 9;
				v32 /= num;
				v32 *= 9;
			}

			h16=shift_sobel_dword(h32,ctrl);
			v16=shift_sobel_dword(h32,ctrl);
			m8=get_sobel_mag(h16,v16,ctrl);
			a8=get_sobel_ang(h16,v16,ctrl);
			get_sobel_output(&out[k],ctrl,a8,m8,h16,v16);
			k++;
		}
	}
}


/**************************************************/
