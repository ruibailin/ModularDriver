/*---------------------------
 * sw_reg_knl0.c
 *  Created on: Jun 25, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#include "../../code/sw_cve/4reg/c_share.h"


#ifndef T_SW_KNL0_REG
typedef struct{
    DWORD KNL_EN0;                  		// 0x400

    DWORD CTRL_FILTER;          		 	// 0x404
    DWORD FLT_COEFF[10];            		// 0x408~0x422c

    DWORD CTRL_SBL;           		 		// 0x430
    DWORD SBL_HCOEFF[10];            		// 0x434~0x458
    DWORD SBL_VCOEFF[10];            		// 0x45c~0x480

    DWORD CTRL_ERD5x5;        		 		// 0x484
    DWORD CTRL_ERD3x3;        		 		// 0x488

    DWORD CTRL_DLT5x5;       		 		// 0x48c
    DWORD CTRL_DLT3x3;              		// 0x490
}T_SW_KNL0_REG;
#endif

static	T_SW_KNL0_REG	ssw_knl0_reg, shw_knl0_reg;

/**************************************************/
void knl0_get_base_addr(void **knl0);
void knl0_get_base_addr(void **knl0)
{
	*knl0=(void *)&shw_knl0_reg;
}

/**************************************************/
void knl0_ini_hw_reg(void);
void knl0_ini_hw_reg(void)
{
	int ii;
	ram_write_dword((void *)&(shw_knl0_reg.KNL_EN0),0x00);
	ram_write_dword((void *)&(shw_knl0_reg.CTRL_FILTER),0x00);
	for(ii=0;ii<5;ii++)
		ram_write_dword((void *)&(shw_knl0_reg.FLT_COEFF[2*ii+1]),0x00);
	ram_write_dword((void *)&(shw_knl0_reg.CTRL_SBL),0x00);
	for(ii=0;ii<5;ii++)
		ram_write_dword((void *)&(shw_knl0_reg.SBL_HCOEFF[2*ii+1]),0x00);
	for(ii=0;ii<5;ii++)
		ram_write_dword((void *)&(shw_knl0_reg.SBL_VCOEFF[2*ii+1]),0x00);
	ram_write_dword((void *)&(shw_knl0_reg.CTRL_ERD5x5),0x00);
	ram_write_dword((void *)&(shw_knl0_reg.CTRL_ERD3x3),0x00);
	ram_write_dword((void *)&(shw_knl0_reg.CTRL_DLT5x5),0x00);
	ram_write_dword((void *)&(shw_knl0_reg.CTRL_DLT3x3),0x00);
}
/**************************************************/
/*  ������()�Ǳ���ģ�ӦΪ������~���㣬Ҫ��֤˳�� */
#define	OPR_MED3x3_EN		((DWORD)0x00000001<<8)
#define	OPR_MIN3x3_EN		((DWORD)0x00000001<<7)
#define	OPR_MAX3x3_EN		((DWORD)0x00000001<<6)
#define	OPR_DLT3x3_EN		((DWORD)0x00000001<<5)
#define	OPR_ERD3x3_EN		((DWORD)0x00000001<<4)
#define	OPR_DLT5x5_EN		((DWORD)0x00000001<<3)
#define	OPR_ERD5x5_EN		((DWORD)0x00000001<<2)
#define	OPR_SBL5x5_EN		((DWORD)0x00000001<<1)
#define	OPR_FLT5x5_EN		((DWORD)0x00000001<<0)
void knl0_get_opr_enabler(DWORD *opr);
void knl0_get_opr_enabler(DWORD *opr)
{
	ssw_knl0_reg.KNL_EN0=ram_read_dword((void *)&(shw_knl0_reg.KNL_EN0));
	*opr=ssw_knl0_reg.KNL_EN0;
}
/**************************************************/
void knl0_get_ERD5x5_ctrl(int *ctrl);
void knl0_get_ERD5x5_ctrl(int *ctrl)
{
	ssw_knl0_reg.CTRL_ERD5x5=ram_read_dword((void *)&(shw_knl0_reg.CTRL_ERD5x5));
	*ctrl=ssw_knl0_reg.CTRL_ERD5x5;
}
/**************************************************/
void knl0_get_ERD3x3_ctrl(int *ctrl);
void knl0_get_ERD3x3_ctrl(int *ctrl)
{
	ssw_knl0_reg.CTRL_ERD3x3=ram_read_dword((void *)&(shw_knl0_reg.CTRL_ERD3x3));
	*ctrl=ssw_knl0_reg.CTRL_ERD3x3;
}

/**************************************************/
void knl0_get_DLT5x5_ctrl(int *ctrl);
void knl0_get_DLT5x5_ctrl(int *ctrl)
{
	ssw_knl0_reg.CTRL_DLT5x5=ram_read_dword((void *)&(shw_knl0_reg.CTRL_DLT5x5));
	*ctrl=ssw_knl0_reg.CTRL_DLT5x5;
}
/**************************************************/
void knl0_get_DLT3x3_ctrl(int *ctrl);
void knl0_get_DLT3x3_ctrl(int *ctrl)
{
	ssw_knl0_reg.CTRL_DLT3x3=ram_read_dword((void *)&(shw_knl0_reg.CTRL_DLT3x3));
	*ctrl=ssw_knl0_reg.CTRL_DLT3x3;
}

/**************************************************/
void knl0_get_FLT_ctrl(int *ctrl);
void knl0_get_FLT_ctrl(int *ctrl)
{
	ssw_knl0_reg.CTRL_FILTER=ram_read_dword((void *)&(shw_knl0_reg.CTRL_FILTER));
	*ctrl=ssw_knl0_reg.CTRL_FILTER;
}


/**************************************************/
void knl0_get_FLT_coeff(BYTE co[][5]);
void knl0_get_FLT_coeff(BYTE co[][5])
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	int ii,jj;
	B2DW b2dw[2];

	for(ii=0;ii<10;ii++)
		ssw_knl0_reg.FLT_COEFF[ii]=ram_read_dword((void *)&(shw_knl0_reg.FLT_COEFF[ii]));

	for(ii=0;ii<5;ii++)
	{
		b2dw[0].dw=ssw_knl0_reg.FLT_COEFF[2*ii+0];
		b2dw[1].dw=ssw_knl0_reg.FLT_COEFF[2*ii+1];

		for(jj=0;jj<5;jj++)
		{
			if(jj==4) break;
			co[ii][jj]=b2dw[0].b[jj];
		}
		co[ii][jj]=b2dw[1].b[3];
	}
}


/**************************************************/
void knl0_get_SBL_ctrl(int *ctrl);
void knl0_get_SBL_ctrl(int *ctrl)
{
	ssw_knl0_reg.CTRL_SBL=ram_read_dword((void *)&(shw_knl0_reg.CTRL_SBL));
	*ctrl=ssw_knl0_reg.CTRL_SBL;
}

/**************************************************/
void knl0_get_SBL_hcoeff(BYTE hco[][5]);
void knl0_get_SBL_hcoeff(BYTE hco[][5])
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	int ii,jj;
	B2DW b2dw[2];

	for(ii=0;ii<10;ii++)
		ssw_knl0_reg.SBL_HCOEFF[ii]=ram_read_dword((void *)&(shw_knl0_reg.SBL_HCOEFF[ii]));

	for(ii=0;ii<5;ii++)
	{
		b2dw[0].dw=ssw_knl0_reg.SBL_HCOEFF[2*ii+0];
		b2dw[1].dw=ssw_knl0_reg.SBL_HCOEFF[2*ii+1];

		for(jj=0;jj<5;jj++)
		{
			if(jj==4) break;
			hco[ii][jj]=b2dw[0].b[jj];
		}
		hco[ii][jj]=b2dw[1].b[3];
	}
}

/**************************************************/
void knl0_get_SBL_vcoeff(BYTE vco[][5]);
void knl0_get_SBL_vcoeff(BYTE vco[][5])
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	int ii,jj;
	B2DW b2dw[2];

	for(ii=0;ii<10;ii++)
		ssw_knl0_reg.SBL_VCOEFF[ii]=ram_read_dword((void *)&(shw_knl0_reg.SBL_VCOEFF[ii]));

	for(ii=0;ii<5;ii++)
	{
		b2dw[0].dw=ssw_knl0_reg.SBL_VCOEFF[2*ii+0];
		b2dw[1].dw=ssw_knl0_reg.SBL_VCOEFF[2*ii+1];
		for(jj=0;jj<5;jj++)
		{
			if(jj==4) break;
			vco[ii][jj]=b2dw[0].b[jj];
		}
		vco[ii][jj]=b2dw[1].b[3];
	}
}

/* end of sw_reg_knl0.c */
