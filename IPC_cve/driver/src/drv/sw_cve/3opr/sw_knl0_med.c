/*---------------------------
 * sw_knl0_med.c
 *  Created on: Jun 18, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *MED:MEDIAN
 *MED should be unsigned operator.
 *
 *
 *---------------------------
 */


#include "../../code/sw_cve/3opr/c_share.h"
/**************************************************/
static BYTE get_3_max(BYTE v1,BYTE v2,BYTE v3);
static BYTE get_3_max(BYTE v1,BYTE v2,BYTE v3)
{
	if(v1>=v2)
		if(v2>=v3)
			return(v1);
		else
			return(MAX(v1,v3));
	else
		if(v2<=v3)
			return(v3);
		else
			return(MAX(v1,v3));
}

/**************************************************/
static BYTE get_3_med(BYTE v1,BYTE v2,BYTE v3);
static BYTE get_3_med(BYTE v1,BYTE v2,BYTE v3)
{
	if(v1>=v2)
		if(v2>=v3)
			return(v2);
		else
			return(MIN(v1,v3));
	else
		if(v2<=v3)
			return(v2);
		else
			return(MAX(v1,v3));
}
/**************************************************/
static BYTE get_3_min(BYTE v1,BYTE v2,BYTE v3);
static BYTE get_3_min(BYTE v1,BYTE v2,BYTE v3)
{
	if(v1>=v2)
		if(v2>=v3)
			return(v3);
		else
			return(MIN(v1,v3));
	else
		if(v2<=v3)
			return(v1);
		else
			return(MIN(v1,v3));
}

/**************************************************/
static BYTE get_blk3x3_med(BYTE blk[][3]);
static BYTE get_blk3x3_med(BYTE blk[][3])
{
	int i;
	BYTE v[3];
	BYTE maxmin,minmax,medmed,med;

	for (i = 0; i < 3; i++)
		v[i]=get_3_max(blk[i][0],blk[i][1],blk[i][2]);
	maxmin=get_3_min(v[0],v[1],v[2]);

	for (i = 0; i < 3; i++)
		v[i]=get_3_min(blk[i][0],blk[i][1],blk[i][2]);
	minmax=get_3_max(v[0],v[1],v[2]);

	for (i = 0; i < 3; i++)
		v[i]=get_3_med(blk[i][0],blk[i][1],blk[i][2]);
	medmed=get_3_med(v[0],v[1],v[2]);

	med=get_3_med(maxmin,minmax,medmed);

	return(med);
}


/**************************************************/
void sw_knl0_MED3x3(char *out, char *in, int width, int height);
void sw_knl0_MED3x3(char *out, char *in, int width, int height)
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
			value=get_blk3x3_med(block);

			out[k]=value;
			k++;
		}
	}
}
/* end of sw_knl0_med.c */
