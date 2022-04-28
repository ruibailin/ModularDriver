/*---------------------------
 * sw_knl_base.c
 *  Created on: Jun 17, 2017
 *      Author: Bailin Rui
 *          ×÷Õß£ºÜÇ°ØÁÖ
 *---------------------------
 * sw_knl_base.c
 * Define base function:
 * 1.5*5 Block
 * 2.3*3 Block
 * 3.5*5 matrix convolution
 * 4.3*3 matrix convolution
 *
 *---------------------------
 */

/**************************************************/
int  knl_get_blk5x5(char *in,char block[][5],int i,int j,int width,int height);
int  knl_get_blk5x5(char *in,char block[][5],int i,int j,int width,int height)
{
	int m,n;
	int xPos, yPos;
	int num;

	num=0;
	for (m = 0; m < 5; m++)
	{
		for (n = 0; n < 5; n++)
		{
			yPos = i + m-2;
			xPos = j + n-2;
			block[m][n]=0;

			if(yPos< 0) continue;
			if(xPos< 0) continue;

			if(yPos >= height) continue;
			if(xPos >= width)  continue;

			block[m][n] = in[yPos*width + xPos];
			num++;
		}
	}
	return(num);
}
/**************************************************/
int knl_conv_blk5x5( char block[][5],char coeff[][5]);
int knl_conv_blk5x5( char block[][5],char coeff[][5])
{
	int ii,jj;
	int value,tmp1,tmp2,temp;

	value=0;
	for(ii=0;ii<5;ii++)
		for(jj=0;jj<5;jj++)
		{
			tmp1=(int)block[ii][jj];
			tmp2=(int)coeff[ii][jj];
			temp=tmp1*tmp2;
			value += temp;
		}
	return(value);
}
/**************************************************/
int knl_get_blk3x3(char *in,char block[][3],int i,int j,int width,int height);
int knl_get_blk3x3(char *in,char block[][3],int i,int j,int width,int height)
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
			block[m][n]=0;

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
int knl_conv_blk3x3(char block[][3],char coeff[][3]);
int knl_conv_blk3x3(char block[][3],char coeff[][3])
{
	int ii,jj;
	int value,tmp1,tmp2,temp;

	value=0;
	for(ii=0;ii<3;ii++)
		for(jj=0;jj<3;jj++)
		{
			tmp1=(int)block[ii][jj];
			tmp2=(int)coeff[ii][jj];
			temp=tmp1*tmp2;
			value += temp;
		}
	return(value);
}

/**************************************************/
void knl_copy_hori(char *out,char *in, int width, int i);
void knl_copy_hori(char *out,char *in, int width, int i)
{
	int j,k;
	for (j = 0; j < width; j++)
	{
		k=i*width+j;
		out[k]=in[k];
	}
}
/**************************************************/
void knl_copy_vert(char *out,char *in, int width,int j,int height);
void knl_copy_vert(char *out,char *in, int width,int j,int height)
{
	int i,k;
	for (i = 0; i < height; i++)
	{
		k=i*width+j;
		out[k]=in[k];
	}
}
/**************************************************/
void knl_set_hori(char *out,char value, int width, int i);
void knl_set_hori(char *out,char value, int width, int i)
{
	int j,k;
	for (j = 0; j < width; j++)
	{
		k=i*width+j;
		out[k]=value;
	}
}
/**************************************************/
void knl_set_vert(char *out,char value, int width,int j,int height);
void knl_set_vert(char *out,char value, int width,int j,int height)
{
	int i,k;
	for (i = 0; i < height; i++)
	{
		k=i*width+j;
		out[k]=value;
	}
}

/*end of sw_knl_base.c*/
