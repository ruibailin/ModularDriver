/*---------------------------
 * sw_knl0_dlt.c
 *  Created on: Jun 18, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Dilate 5*5
 *Dilate 3*3
 *
 *
 *---------------------------
 */


#include "../../code/sw_cve/3opr/c_share.h"

/**************************************************/
static char get_dlt5x5_sum(char block[][5],int ctrl);
static char get_dlt5x5_sum(char block[][5],int ctrl)
{
	int m, n;
	char sum;
	BYTE val,trs;

	trs=(BYTE)(ctrl&0xFF);
	sum=0;
	for (m=0; m<5; m++)
	{
		for (n=0; n<5; n++)
		{
			val=(BYTE)block[m][n];
			if(val>=trs)
				sum ++;
		}
	}
	return(sum);
}

/**************************************************/
static  char get_dlt5x5_output(char sum,char num);
static  char get_dlt5x5_output(char sum,char num)
{
	if(sum ==0)
		return(0x00);
	else
		return(0xFF);
}


/**************************************************/
void sw_knl0_DLT5x5(char *out, char *in, int width, int height,int ctrl);
void sw_knl0_DLT5x5(char *out, char *in, int width, int height,int ctrl)
{

	char block[5][5];
	char	sum,num;

	int i, j, k;
	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			num=knl_get_blk5x5(in,block,i,j,width,height);
			sum=get_dlt5x5_sum(block,ctrl);

			out[k]=get_dlt5x5_output(sum,num);
			k++;
		}
	}
}

/**************************************************/
static  char get_dlt3x3_sum(char block[][3],int ctrl);
static  char get_dlt3x3_sum(char block[][3],int ctrl)
{
	int m, n;
	char sum;
	BYTE val,trs;

	trs=(char)(ctrl&0xFF);
	sum=0;
	for (m=0; m<3; m++)
	{
		for (n=0; n<3; n++)
		{
			val=(BYTE)block[m][n];
			if(val>=trs)
				sum ++;
		}
	}
	return(sum);
}

/**************************************************/
static  char get_dlt3x3_output(char sum,char num);
static  char get_dlt3x3_output(char sum,char num)
{
	if(sum ==0)
		return(0x00);
	else
		return(0xFF);
}


/**************************************************/
void sw_knl0_DLT3x3(char *out, char *in, int width, int height,int ctrl);
void sw_knl0_DLT3x3(char *out, char *in, int width, int height,int ctrl)
{

	char block[3][3];
	char	sum,num;

	int i, j, k;
	k=0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			num=knl_get_blk3x3(in,block,i,j,width,height);
			sum=get_dlt3x3_sum(block,ctrl);

			out[k]=get_dlt3x3_output(sum,num);
			k++;
		}
	}
}

/* end of sw_knl0_dlt.c */
