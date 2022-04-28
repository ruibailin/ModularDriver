/*---------------------------
 * hw_reg_knl0.c
 *  Created on: Jun 8, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#include "c_share.h"

#ifndef T_HW_KNL0_REG
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
}T_HW_KNL0_REG;
#endif

static	T_HW_KNL0_REG	hsw_knl0_reg, *hhw_knl0_reg;

/**************************************************/
void knl0_ini_base_addr(void *knl0);
void knl0_ini_base_addr(void *knl0)
{
	hhw_knl0_reg=(T_HW_KNL0_REG *)knl0;
}

/**************************************************/
void knl0_ini_sw_reg(void);
void knl0_ini_sw_reg(void)
{
	int ii;
	hsw_knl0_reg.KNL_EN0=ram_read_dword((void *)&(hhw_knl0_reg->KNL_EN0));
	hsw_knl0_reg.CTRL_FILTER=ram_read_dword((void *)&(hhw_knl0_reg->CTRL_FILTER));
	for(ii=0;ii<5;ii++)
		hsw_knl0_reg.FLT_COEFF[2*ii+1]=ram_read_dword((void *)&(hhw_knl0_reg->FLT_COEFF[2*ii+1]));
	hsw_knl0_reg.CTRL_SBL=ram_read_dword((void *)&(hhw_knl0_reg->CTRL_SBL));
	for(ii=0;ii<5;ii++)
		hsw_knl0_reg.SBL_HCOEFF[2*ii+1]=ram_read_dword((void *)&(hhw_knl0_reg->SBL_HCOEFF[2*ii+1]));
	for(ii=0;ii<5;ii++)
		hsw_knl0_reg.SBL_VCOEFF[2*ii+1]=ram_read_dword((void *)&(hhw_knl0_reg->SBL_VCOEFF[2*ii+1]));
	hsw_knl0_reg.CTRL_ERD5x5=ram_read_dword((void *)&(hhw_knl0_reg->CTRL_ERD5x5));
	hsw_knl0_reg.CTRL_ERD3x3=ram_read_dword((void *)&(hhw_knl0_reg->CTRL_ERD3x3));
	hsw_knl0_reg.CTRL_DLT5x5=ram_read_dword((void *)&(hhw_knl0_reg->CTRL_DLT5x5));
	hsw_knl0_reg.CTRL_DLT3x3=ram_read_dword((void *)&(hhw_knl0_reg->CTRL_DLT3x3));
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
void knl0_set_opr_enabler(DWORD opr);
void knl0_set_opr_enabler(DWORD opr)
{
	hsw_knl0_reg.KNL_EN0 |= opr;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}
/**************************************************/
void knl0_clr_opr_enabler(DWORD opr);
void knl0_clr_opr_enabler(DWORD opr)
{
	hsw_knl0_reg.KNL_EN0 &= (~opr);
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}
/**************************************************/
void knl0_set_MED3x3_opr(void);
void knl0_set_MED3x3_opr(void)
{
	hsw_knl0_reg.KNL_EN0 |= OPR_MED3x3_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}
/**************************************************/
void knl0_clr_MED3x3_opr(void);
void knl0_clr_MED3x3_opr(void)
{
	hsw_knl0_reg.KNL_EN0 &= ~OPR_MED3x3_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}

/**************************************************/
void knl0_set_MIN3x3_opr(void);
void knl0_set_MIN3x3_opr(void)
{
	hsw_knl0_reg.KNL_EN0 |= OPR_MIN3x3_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}
/**************************************************/
void knl0_clr_MIN3x3_opr(void);
void knl0_clr_MIN3x3_opr(void)
{
	hsw_knl0_reg.KNL_EN0 &= ~OPR_MIN3x3_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}

/**************************************************/
void knl0_set_MAX3x3_opr(void);
void knl0_set_MAX3x3_opr(void)
{
	hsw_knl0_reg.KNL_EN0 |= OPR_MAX3x3_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}

/**************************************************/
void knl0_clr_MAX3x3_opr(void);
void knl0_clr_MAX3x3_opr(void)
{
	hsw_knl0_reg.KNL_EN0 &= ~OPR_MAX3x3_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}

/**************************************************/
void knl0_set_ERD5x5_opr(void);
void knl0_set_ERD5x5_opr(void)
{
	hsw_knl0_reg.KNL_EN0 |= OPR_ERD5x5_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}

/**************************************************/
void knl0_clr_ERD5x5_opr(void);
void knl0_clr_ERD5x5_opr(void)
{
	hsw_knl0_reg.KNL_EN0 &= ~OPR_ERD5x5_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}
/**************************************************/
void knl0_set_ERD5x5_mode(BYTE mode);
void knl0_set_ERD5x5_mode(BYTE mode)
{
	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x0000001F;
	old=hsw_knl0_reg.CTRL_ERD5x5;
	old &= (~0x0000001F);
	old |= new;
	hsw_knl0_reg.CTRL_ERD5x5=old;

	ram_write_dword((void *)&(hhw_knl0_reg->CTRL_ERD5x5),hsw_knl0_reg.CTRL_ERD5x5);
}
/**************************************************/
void knl0_set_ERD3x3_opr(void);
void knl0_set_ERD3x3_opr(void)
{
	hsw_knl0_reg.KNL_EN0 |= OPR_ERD3x3_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}

/**************************************************/
void knl0_clr_ERD3x3_opr(void);
void knl0_clr_ERD3x3_opr(void)
{
	hsw_knl0_reg.KNL_EN0 &= ~OPR_ERD3x3_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}
/**************************************************/
void knl0_set_ERD3x3_mode(BYTE mode);
void knl0_set_ERD3x3_mode(BYTE mode)
{
	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x0000000F;
	old=hsw_knl0_reg.CTRL_ERD3x3;
	old &= (~0x0000000F);
	old |= new;
	hsw_knl0_reg.CTRL_ERD3x3=old;

	ram_write_dword((void *)&(hhw_knl0_reg->CTRL_ERD3x3),hsw_knl0_reg.CTRL_ERD3x3);
}

/**************************************************/
void knl0_set_DLT5x5_opr(void);
void knl0_set_DLT5x5_opr(void)
{
	hsw_knl0_reg.KNL_EN0 |= OPR_DLT5x5_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}

/**************************************************/
void knl0_clr_DLT5x5_opr(void);
void knl0_clr_DLT5x5_opr(void)
{
	hsw_knl0_reg.KNL_EN0 &= ~OPR_DLT5x5_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}
/**************************************************/
void knl0_set_DLT5x5_mode(BYTE mode);
void knl0_set_DLT5x5_mode(BYTE mode)
{
	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x0000001F;
	old=hsw_knl0_reg.CTRL_DLT5x5;
	old &= (~0x0000001F);
	old |= new;
	hsw_knl0_reg.CTRL_DLT5x5=old;

	ram_write_dword((void *)&(hhw_knl0_reg->CTRL_DLT5x5),hsw_knl0_reg.CTRL_DLT5x5);
}
/**************************************************/
void knl0_set_DLT3x3_opr(void);
void knl0_set_DLT3x3_opr(void)
{
	hsw_knl0_reg.KNL_EN0 |= OPR_DLT3x3_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}

/**************************************************/
void knl0_clr_DLT3x3_opr(void);
void knl0_clr_DLT3x3_opr(void)
{
	hsw_knl0_reg.KNL_EN0 &= ~OPR_DLT3x3_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}
/**************************************************/
void knl0_set_DLT3x3_mode(BYTE mode);
void knl0_set_DLT3x3_mode(BYTE mode)
{
	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x0000000F;
	old=hsw_knl0_reg.CTRL_DLT3x3;
	old &= (~0x0000000F);
	old |= new;
	hsw_knl0_reg.CTRL_DLT3x3=old;

	ram_write_dword((void *)&(hhw_knl0_reg->CTRL_DLT3x3),hsw_knl0_reg.CTRL_DLT3x3);
}

/**************************************************/
void knl0_set_FLT_opr(void);
void knl0_set_FLT_opr(void)
{
	hsw_knl0_reg.KNL_EN0 |= OPR_FLT5x5_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}
/**************************************************/
void knl0_clr_FLT_opr(void);
void knl0_clr_FLT_opr(void)
{
	hsw_knl0_reg.KNL_EN0 &= ~OPR_FLT5x5_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}
/**************************************************/
void knl0_set_FLT_power(BYTE power);
void knl0_set_FLT_power(BYTE power)
{
	DWORD	new,old;

	new=(DWORD)power;
	new &= 0x0000000F;
	old=hsw_knl0_reg.CTRL_FILTER;
	old &= (~0x0000000F);
	old |= new;
	hsw_knl0_reg.CTRL_FILTER=old;

	ram_write_dword((void *)&(hhw_knl0_reg->CTRL_FILTER),hsw_knl0_reg.CTRL_FILTER);
}


/**************************************************/
void knl0_set_FLT_coeff(BYTE co[][5]);
void knl0_set_FLT_coeff(BYTE co[][5])
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	int ii,jj;
	B2DW b2dw[2];

	for(ii=0;ii<5;ii++)
	{
		for(jj=0;jj<5;jj++)
		{
			if(jj==4) break;
			b2dw[0].b[jj]=co[ii][jj];
		}
		b2dw[1].dw=hsw_knl0_reg.FLT_COEFF[2*ii+1];
		b2dw[1].b[3]=co[ii][jj];

		hsw_knl0_reg.FLT_COEFF[2*ii+0]=b2dw[0].dw;
		hsw_knl0_reg.FLT_COEFF[2*ii+1]=b2dw[1].dw;
	}

	for(ii=0;ii<10;ii++)
		ram_write_dword((void *)&(hhw_knl0_reg->FLT_COEFF[ii]),hsw_knl0_reg.FLT_COEFF[ii]);
}


/**************************************************/
void knl0_set_SBL_opr(void);
void knl0_set_SBL_opr(void)
{
	hsw_knl0_reg.KNL_EN0 |= OPR_SBL5x5_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}
/**************************************************/
void knl0_clr_SBL_opr(void);
void knl0_clr_SBL_opr(void)
{
	hsw_knl0_reg.KNL_EN0 &= ~OPR_SBL5x5_EN;
	ram_write_dword((void *)&(hhw_knl0_reg->KNL_EN0),hsw_knl0_reg.KNL_EN0);
}
/**************************************************/
void knl0_set_SBL_mode(BYTE output,BYTE angle);
void knl0_set_SBL_mode(BYTE output,BYTE angle)
{
	DWORD	new,old;

	new=(DWORD)output;
	new &= 0x00000007;
	new <<= 9;
	old=hsw_knl0_reg.CTRL_SBL;
	old &= (~(0x00000007<<9));
	old |= new;
	hsw_knl0_reg.CTRL_SBL=old;

	new=(DWORD)angle;
	new &= 0x00000001;
	new <<= 8;
	old=hsw_knl0_reg.CTRL_SBL;
	old &= (~(0x00000001<<8));
	old |= new;
	hsw_knl0_reg.CTRL_SBL=old;

	ram_write_dword((void *)&(hhw_knl0_reg->CTRL_SBL),hsw_knl0_reg.CTRL_SBL);
}
/**************************************************/
void knl0_set_SBL_mode_output(BYTE output);
void knl0_set_SBL_mode_output(BYTE output)
{
	DWORD	new,old;

	new=(DWORD)output;
	new &= 0x00000007;
	new <<= 9;
	old=hsw_knl0_reg.CTRL_SBL;
	old &= (~(0x00000007<<9));
	old |= new;
	hsw_knl0_reg.CTRL_SBL=old;

	ram_write_dword((void *)&(hhw_knl0_reg->CTRL_SBL),hsw_knl0_reg.CTRL_SBL);
}
/**************************************************/
void knl0_set_SBL_mode_angle(BYTE angle);
void knl0_set_SBL_mode_angle(BYTE angle)
{
	DWORD	new,old;

	new=(DWORD)angle;
	new &= 0x00000001;
	new <<= 8;
	old=hsw_knl0_reg.CTRL_SBL;
	old &= (~(0x00000001<<8));
	old |= new;
	hsw_knl0_reg.CTRL_SBL=old;

	ram_write_dword((void *)&(hhw_knl0_reg->CTRL_SBL),hsw_knl0_reg.CTRL_SBL);
}

/**************************************************/
void knl0_set_SBL_power(BYTE ang,BYTE mag);
void knl0_set_SBL_power(BYTE ang,BYTE mag)
{
	DWORD	new,old;

	new=(DWORD)ang;
	new &= 0x0000000F;
	new <<= 4;
	old=hsw_knl0_reg.CTRL_SBL;
	old &= (~(0x0000000F<<4));
	old |= new;
	hsw_knl0_reg.CTRL_SBL=old;

	new=(DWORD)mag;
	new &= 0x0000000F;
	old=hsw_knl0_reg.CTRL_SBL;
	old &= (~0x0000000F);
	old |= new;
	hsw_knl0_reg.CTRL_SBL=old;

	ram_write_dword((void *)&(hhw_knl0_reg->CTRL_SBL),hsw_knl0_reg.CTRL_SBL);
}
/**************************************************/
void knl0_set_SBL_power_ang(BYTE ang);
void knl0_set_SBL_power_ang(BYTE ang)
{
	DWORD	new,old;

	new=(DWORD)ang;
	new &= 0x0000000F;
	new <<= 4;
	old=hsw_knl0_reg.CTRL_SBL;
	old &= (~(0x0000000F<<4));
	old |= new;
	hsw_knl0_reg.CTRL_SBL=old;

	ram_write_dword((void *)&(hhw_knl0_reg->CTRL_SBL),hsw_knl0_reg.CTRL_SBL);
}
/**************************************************/
void knl0_set_SBL_power_mag(BYTE mag);
void knl0_set_SBL_power_mag(BYTE mag)
{
	DWORD	new,old;

	new=(DWORD)mag;
	new &= 0x0000000F;
	old=hsw_knl0_reg.CTRL_SBL;
	old &= (~0x0000000F);
	old |= new;
	hsw_knl0_reg.CTRL_SBL=old;

	ram_write_dword((void *)&(hhw_knl0_reg->CTRL_SBL),hsw_knl0_reg.CTRL_SBL);
}

/**************************************************/
void knl0_set_SBL_hcoeff(BYTE hco[][5]);
void knl0_set_SBL_hcoeff(BYTE hco[][5])
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	int ii,jj;
	B2DW b2dw[2];

	for(ii=0;ii<5;ii++)
	{
		for(jj=0;jj<5;jj++)
		{
			if(jj==4) break;
			b2dw[0].b[jj]=hco[ii][jj];
		}
		b2dw[1].dw=hsw_knl0_reg.SBL_HCOEFF[2*ii+1];
		b2dw[1].b[3]=hco[ii][jj];

		hsw_knl0_reg.SBL_HCOEFF[2*ii+0]=b2dw[0].dw;
		hsw_knl0_reg.SBL_HCOEFF[2*ii+1]=b2dw[1].dw;
	}

	for(ii=0;ii<10;ii++)
		ram_write_dword((void *)&(hhw_knl0_reg->SBL_HCOEFF[ii]),hsw_knl0_reg.SBL_HCOEFF[ii]);
}

/**************************************************/
void knl0_set_SBL_vcoeff(BYTE vco[][5]);
void knl0_set_SBL_vcoeff(BYTE vco[][5])
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	int ii,jj;
	B2DW b2dw[2];

	for(ii=0;ii<5;ii++)
	{
		for(jj=0;jj<5;jj++)
		{
			if(jj==4) break;
			b2dw[0].b[jj]=vco[ii][jj];
		}
		b2dw[1].dw=hsw_knl0_reg.SBL_VCOEFF[2*ii+1];
		b2dw[1].b[3]=vco[ii][jj];

		hsw_knl0_reg.SBL_VCOEFF[2*ii+0]=b2dw[0].dw;
		hsw_knl0_reg.SBL_VCOEFF[2*ii+1]=b2dw[1].dw;
	}

	for(ii=0;ii<10;ii++)
		ram_write_dword((void *)&(hhw_knl0_reg->SBL_VCOEFF[ii]),hsw_knl0_reg.SBL_VCOEFF[ii]);
}

/* end of hw_reg_knl0.c */
