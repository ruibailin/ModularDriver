/*---------------------------
 * sw_reg_knl2.c
 *  Created on: Jun 24, 2017
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


#ifndef T_SW_KNL2_REG
typedef struct{
    DWORD KNL_EN2;           	// 0xc00

    DWORD CTRL_ADD;             // 0xc04

    DWORD CTRL_SUB;             // 0xc08

    DWORD CTRL_SAD;             // 0xc0c

    DWORD CTRL_VAR;        		// 0xc10
    DWORD VAR_0;           		// 0xc14
    DWORD VAR_1;           		// 0xc18
}T_SW_KNL2_REG;
#endif

static	T_SW_KNL2_REG	ssw_knl2_reg, shw_knl2_reg;

/**************************************************/
void knl2_get_base_addr(void **knl2);
void knl2_get_base_addr(void **knl2)
{
	*knl2=(void *)&shw_knl2_reg;
}

/**************************************************/
void knl2_ini_hw_reg(void);
void knl2_ini_hw_reg(void)
{
	ram_write_dword((void *)&(shw_knl2_reg.KNL_EN2),0x00);
	ram_write_dword((void *)&(shw_knl2_reg.CTRL_ADD),0x00);
	ram_write_dword((void *)&(shw_knl2_reg.CTRL_SUB),0x00);
	ram_write_dword((void *)&(shw_knl2_reg.CTRL_SAD),0x00);
	ram_write_dword((void *)&(shw_knl2_reg.CTRL_VAR),0x00);

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
void knl2_get_opr_enabler(DWORD *opr);
void knl2_get_opr_enabler(DWORD *opr)
{
	ssw_knl2_reg.KNL_EN2=ram_read_dword((void *)&(shw_knl2_reg.KNL_EN2));
	*opr=ssw_knl2_reg.KNL_EN2;
}

/**************************************************/
void knl2_get_SAD_ctrl(int *ctrl);
void knl2_get_SAD_ctrl(int *ctrl)
{
	ssw_knl2_reg.CTRL_SAD=ram_read_dword((void *)&(shw_knl2_reg.CTRL_SAD));
	*ctrl=ssw_knl2_reg.CTRL_SAD;
}

/**************************************************/
void knl2_get_VAR_ctrl(int *ctrl);
void knl2_get_VAR_ctrl(int *ctrl)
{
	ssw_knl2_reg.CTRL_VAR=ram_read_dword((void *)&(shw_knl2_reg.CTRL_VAR));
	*ctrl=ssw_knl2_reg.CTRL_VAR;
}
/**************************************************/
void knl2_set_VAR_output(long output);
void knl2_set_VAR_output(long output)
{
	typedef union{
		long	qw;
		int		dw[2];
	}DW2QW;
	DW2QW	dtoq;
	dtoq.qw=output;
	ssw_knl2_reg.VAR_1=dtoq.dw[0];
	ssw_knl2_reg.VAR_0=dtoq.dw[1];

	ram_write_dword((void *)&(shw_knl2_reg.VAR_1),ssw_knl2_reg.VAR_1);
	ram_write_dword((void *)&(shw_knl2_reg.VAR_0),ssw_knl2_reg.VAR_0);
}
/**************************************************/
void knl2_get_SUB_ctrl(int *ctrl);
void knl2_get_SUB_ctrl(int *ctrl)
{
	ssw_knl2_reg.CTRL_SUB=ram_read_dword((void *)&(shw_knl2_reg.CTRL_SUB));
	*ctrl=ssw_knl2_reg.CTRL_SUB;
}
/**************************************************/
void knl2_get_ADD_ctrl(int *ctrl);
void knl2_get_ADD_ctrl(int *ctrl)
{
	ssw_knl2_reg.CTRL_ADD=ram_read_dword((void *)&(shw_knl2_reg.CTRL_ADD));
	*ctrl=ssw_knl2_reg.CTRL_ADD;
}
/* end of sw_reg_knl2.c */
