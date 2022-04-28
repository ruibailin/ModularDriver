/*---------------------------
 * hw_reg_knl2.c
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


#ifndef T_HW_KNL2_REG
typedef struct{
    DWORD KNL_EN2;           	// 0xc00

    DWORD CTRL_ADD;             // 0xc04

    DWORD CTRL_SUB;             // 0xc08

    DWORD CTRL_SAD;             // 0xc0c

    DWORD CTRL_VAR;        		// 0xc10
    DWORD VAR_0;           		// 0xc14
    DWORD VAR_1;           		// 0xc18
}T_HW_KNL2_REG;
#endif

static	T_HW_KNL2_REG	hsw_knl2_reg, *hhw_knl2_reg;

/**************************************************/
void knl2_ini_base_addr(void *knl2);
void knl2_ini_base_addr(void *knl2)
{
	hhw_knl2_reg=(T_HW_KNL2_REG *)knl2;
}

/**************************************************/
void knl2_ini_sw_reg(void);
void knl2_ini_sw_reg(void)
{
	hsw_knl2_reg.KNL_EN2=ram_read_dword((void *)&(hhw_knl2_reg->KNL_EN2));
	hsw_knl2_reg.CTRL_ADD=ram_read_dword((void *)&(hhw_knl2_reg->CTRL_ADD));
	hsw_knl2_reg.CTRL_SUB=ram_read_dword((void *)&(hhw_knl2_reg->CTRL_SUB));
	hsw_knl2_reg.CTRL_SAD=ram_read_dword((void *)&(hhw_knl2_reg->CTRL_SAD));
	hsw_knl2_reg.CTRL_VAR=ram_read_dword((void *)&(hhw_knl2_reg->CTRL_VAR));

}

/**************************************************/
/*  ������()�Ǳ���ģ�ӦΪ������~���㣬Ҫ��֤˳�� */
#define OPR_SAD_EN   	((DWORD)0x00000001<<6)
#define OPR_VAR_EN   	((DWORD)0x00000001<<5)
#define OPR_SUB_EN   	((DWORD)0x00000001<<4)
#define OPR_ADD_EN   	((DWORD)0x00000001<<3)
#define OPR_XOR_EN   	((DWORD)0x00000001<<2)
#define OPR_OR_EN   	((DWORD)0x00000001<<1)
#define OPR_AND_EN   	((DWORD)0x00000001<<0)
void knl2_set_opr_enabler(DWORD opr);
void knl2_set_opr_enabler(DWORD opr)
{
	hsw_knl2_reg.KNL_EN2 |= opr;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}
/**************************************************/
void knl2_clr_opr_enabler(DWORD opr);
void knl2_clr_opr_enabler(DWORD opr)
{
	hsw_knl2_reg.KNL_EN2 &= (~opr);
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}
/**************************************************/
void knl2_set_SAD_opr(void);
void knl2_set_SAD_opr(void)
{
	hsw_knl2_reg.KNL_EN2 |= OPR_SAD_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}
/**************************************************/
void knl2_set_SAD_mode(BYTE mode);
void knl2_set_SAD_mode(BYTE mode)
{
	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x00000003;
	old=hsw_knl2_reg.CTRL_SAD;
	old &= (~0x00000003);
	old |= new;
	hsw_knl2_reg.CTRL_SAD=old;

	ram_write_dword((void *)&(hhw_knl2_reg->CTRL_SAD),hsw_knl2_reg.CTRL_SAD);
}
/**************************************************/
void knl2_clr_SAD_opr(void);
void knl2_clr_SAD_opr(void)
{
	hsw_knl2_reg.KNL_EN2 &= ~OPR_SAD_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}

/**************************************************/
void knl2_set_VAR_opr(void);
void knl2_set_VAR_opr(void)
{
	hsw_knl2_reg.KNL_EN2 |= OPR_VAR_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}
/**************************************************/
void knl2_set_VAR_mode(BYTE mode);
void knl2_set_VAR_mode(BYTE mode)
{
	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x00000001;
	new <<= 16;
	old=hsw_knl2_reg.CTRL_VAR;
	old &= (~(0x00000001<<16));
	old |= new;
	hsw_knl2_reg.CTRL_VAR=old;

	ram_write_dword((void *)&(hhw_knl2_reg->CTRL_VAR),hsw_knl2_reg.CTRL_VAR);
}
/**************************************************/
void knl2_set_VAR_input(BYTE a,BYTE b);
void knl2_set_VAR_input(BYTE a,BYTE b)
{
	DWORD	new,old;

	new=(DWORD)a;
	new &= 0x000000FF;
	old=hsw_knl2_reg.CTRL_VAR;
	old &= (~0x000000FF);
	old |= new;
	hsw_knl2_reg.CTRL_VAR=old;

	new=(DWORD)b;
	new &= 0x000000FF;
	new <<= 8;
	old=hsw_knl2_reg.CTRL_VAR;
	old &= (~(0x000000FF<<8));
	old |= new;
	hsw_knl2_reg.CTRL_VAR=old;


	ram_write_dword((void *)&(hhw_knl2_reg->CTRL_VAR),hsw_knl2_reg.CTRL_VAR);
}
/**************************************************/
void knl2_get_VAR_output(long *output);
void knl2_get_VAR_output(long *output)
{
	typedef union{
		long	qw;
		int		dw[2];
	}DW2QW;
	DW2QW	dtoq;

	hsw_knl2_reg.VAR_1=ram_read_dword((void *)&(hhw_knl2_reg->VAR_1));
	hsw_knl2_reg.VAR_0=ram_read_dword((void *)&(hhw_knl2_reg->VAR_0));
	dtoq.dw[0]=hsw_knl2_reg.VAR_1;
	dtoq.dw[1]=hsw_knl2_reg.VAR_0;

	*output=dtoq.qw;
}
/**************************************************/
void knl2_clr_VAR_opr(void);
void knl2_clr_VAR_opr(void)
{
	hsw_knl2_reg.KNL_EN2 &= ~OPR_VAR_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}

/**************************************************/
void knl2_set_SUB_opr(void);
void knl2_set_SUB_opr(void)
{
	hsw_knl2_reg.KNL_EN2 |= OPR_SUB_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}
/**************************************************/
void knl2_set_SUB_mode(BYTE mode);
void knl2_set_SUB_mode(BYTE mode)
{

	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x00000001;
	old=hsw_knl2_reg.CTRL_SUB;
	old &= (~0x00000001);
	old |= new;
	hsw_knl2_reg.CTRL_SUB=old;

	ram_write_dword((void *)&(hhw_knl2_reg->CTRL_SUB),hsw_knl2_reg.CTRL_SUB);
}
/**************************************************/
void knl2_clr_SUB_opr(void);
void knl2_clr_SUB_opr(void)
{
	hsw_knl2_reg.KNL_EN2 &= ~OPR_SUB_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}

/**************************************************/
void knl2_set_ADD_opr(void);
void knl2_set_ADD_opr(void)
{
	hsw_knl2_reg.KNL_EN2 |= OPR_ADD_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}
/**************************************************/
void knl2_set_ADD_mode(BYTE mode);
void knl2_set_ADD_mode(BYTE mode)
{
	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x000000FF;
	old=hsw_knl2_reg.CTRL_ADD;
	old &= (~0x000000FF);
	old |= new;
	hsw_knl2_reg.CTRL_ADD=old;

	ram_write_dword((void *)&(hhw_knl2_reg->CTRL_ADD),hsw_knl2_reg.CTRL_ADD);
}
/**************************************************/
void knl2_clr_ADD_opr(void);
void knl2_clr_ADD_opr(void)
{
	hsw_knl2_reg.KNL_EN2 &= ~OPR_ADD_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}

/**************************************************/
void knl2_set_XOR_opr(void);
void knl2_set_XOR_opr(void)
{
	hsw_knl2_reg.KNL_EN2 |= OPR_XOR_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}

/**************************************************/
void knl2_clr_XOR_opr(void);
void knl2_clr_XOR_opr(void)
{
	hsw_knl2_reg.KNL_EN2 &= ~OPR_XOR_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}

/**************************************************/
void knl2_set_OR_opr(void);
void knl2_set_OR_opr(void)
{
	hsw_knl2_reg.KNL_EN2 |= OPR_OR_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}

/**************************************************/
void knl2_clr_OR_opr(void);
void knl2_clr_OR_opr(void)
{
	hsw_knl2_reg.KNL_EN2 &= ~OPR_OR_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}

/**************************************************/
void knl2_set_AND_opr(void);
void knl2_set_AND_opr(void)
{
	hsw_knl2_reg.KNL_EN2 |= OPR_AND_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}

/**************************************************/
void knl2_clr_AND_opr(void);
void knl2_clr_AND_opr(void)
{
	hsw_knl2_reg.KNL_EN2 &= ~OPR_AND_EN;
	ram_write_dword((void *)&(hhw_knl2_reg->KNL_EN2),hsw_knl2_reg.KNL_EN2);
}
/* end of hw_reg_knl2.c */
