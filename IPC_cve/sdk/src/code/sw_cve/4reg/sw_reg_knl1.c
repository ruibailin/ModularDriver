/*---------------------------
 * sw_reg_knl1.c
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

#ifndef T_SW_KNL1_REG
typedef struct{
    DWORD KNL_EN1;         	// 0x800

    DWORD CTRL_TRS8_0;    	// 0x804
    DWORD CTRL_TRS8_1;    	// 0x808

    DWORD CTRL_TRS16_0;   	// 0x80c
    DWORD CTRL_TRS16_1;   	// 0x810

    DWORD CTRL_BLK16;      	// 0x814

    DWORD CTRL_MAP;        	// 0x818
    DWORD MAP_RESTORE;     	// 0x81c

    DWORD SUM16_SIGN;     	// 0x820
    DWORD SUM16_0;      	// 0x824
    DWORD SUM16_1;       	// 0x828

    DWORD SUM8;         	// 0x82c

    DWORD CTRL_HST;       	// 0x830
}T_SW_KNL1_REG;
#endif

static	T_SW_KNL1_REG	ssw_knl1_reg, shw_knl1_reg;

/**************************************************/
void knl1_get_base_addr(void **knl1);
void knl1_get_base_addr(void **knl1)
{
	*knl1=(void *)&shw_knl1_reg;
}

/**************************************************/
void knl1_ini_hw_reg(void);
void knl1_ini_hw_reg(void)
{

	ram_write_dword((void *)&(shw_knl1_reg.KNL_EN1),0x00);

	ram_write_dword((void *)&(shw_knl1_reg.CTRL_TRS8_0),0x00);
	ram_write_dword((void *)&(shw_knl1_reg.CTRL_TRS8_1),0x00);
	ram_write_dword((void *)&(shw_knl1_reg.CTRL_TRS16_0),0x00);
	ram_write_dword((void *)&(shw_knl1_reg.CTRL_TRS16_1),0x00);
	ram_write_dword((void *)&(shw_knl1_reg.CTRL_BLK16),0x00);
	ram_write_dword((void *)&(shw_knl1_reg.CTRL_MAP),0x00);
	ram_write_dword((void *)&(shw_knl1_reg.MAP_RESTORE),0x00);
	ram_write_dword((void *)&(shw_knl1_reg.SUM16_SIGN),0x00);
	ram_write_dword((void *)&(shw_knl1_reg.SUM16_0),0x00);
	ram_write_dword((void *)&(shw_knl1_reg.SUM16_1),0x00);
	ram_write_dword((void *)&(shw_knl1_reg.SUM8),0x00);
	ram_write_dword((void *)&(shw_knl1_reg.CTRL_HST),0x00);

}

/**************************************************/
/*  ������()�Ǳ���ģ�ӦΪ������~���㣬Ҫ��֤˳�� */
#define  OPR_MAP_EN					((DWORD)0x00000001<<6)
#define  OPR_HST_EN					((DWORD)0x00000001<<5)
#define  OPR_TRS8_EN				((DWORD)0x00000001<<4)
#define  OPR_SUM8_EN				((DWORD)0x00000001<<3)
#define  OPR_SUM16_EN				((DWORD)0x00000001<<2)
#define  OPR_TRS16_EN				((DWORD)0x00000001<<1)
#define  OPR_BLK16_EN				((DWORD)0x00000001<<0)
void knl1_get_opr_enabler(DWORD *opr);
void knl1_get_opr_enabler(DWORD *opr)
{
	ssw_knl1_reg.KNL_EN1=ram_read_dword((void *)&(shw_knl1_reg.KNL_EN1));
	*opr=ssw_knl1_reg.KNL_EN1;
}

/**************************************************/
void knl1_get_MAP_ctrl(int *ctrl);
void knl1_get_MAP_ctrl(int *ctrl)
{
	DWORD	old;

	ssw_knl1_reg.CTRL_MAP=ram_read_dword((void *)&(shw_knl1_reg.CTRL_MAP));
	old=ssw_knl1_reg.CTRL_MAP;
	old &= (0x00000001);
	*ctrl=old;
}
/**************************************************/
void knl1_get_MAP_write(WORD *data,BYTE *addr);
void knl1_get_MAP_write(WORD *data,BYTE *addr)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
		BYTE   b[4];
	}B_W2DW;

	B_W2DW  b2dw;

	ssw_knl1_reg.MAP_RESTORE=ram_read_dword((void *)&(shw_knl1_reg.MAP_RESTORE));

	b2dw.dw=ssw_knl1_reg.MAP_RESTORE;
	*data=b2dw.w[0];
	*addr=b2dw.b[2];
}
/**************************************************/
void knl1_get_HST_ctrl(int *ctrl);
void knl1_get_HST_ctrl(int *ctrl)
{
	ssw_knl1_reg.CTRL_HST=ram_read_dword((void *)&(shw_knl1_reg.CTRL_HST));
	*ctrl=ssw_knl1_reg.CTRL_HST;
}

/**************************************************/
void knl1_get_TRS8_ctrl0(int *ctrl);
void knl1_get_TRS8_ctrl0(int *ctrl)
{
	ssw_knl1_reg.CTRL_TRS8_0=ram_read_dword((void *)&(shw_knl1_reg.CTRL_TRS8_0));
	*ctrl=ssw_knl1_reg.CTRL_TRS8_0;
}

/**************************************************/
void knl1_get_TRS8_ctrl1(int *ctrl);
void knl1_get_TRS8_ctrl1(int *ctrl)
{
	ssw_knl1_reg.CTRL_TRS8_1=ram_read_dword((void *)&(shw_knl1_reg.CTRL_TRS8_1));
	*ctrl=ssw_knl1_reg.CTRL_TRS8_1;
}
/**************************************************/
void knl1_set_SUM8_output(DWORD output);
void knl1_set_SUM8_output(DWORD output)
{
	ssw_knl1_reg.SUM8=output;
	ram_write_dword((void *)&(shw_knl1_reg.SUM8),ssw_knl1_reg.SUM8);
}
/**************************************************/
void knl1_get_SUM16_ctrl(int *ctrl);
void knl1_get_SUM16_ctrl(int *ctrl)
{
	ssw_knl1_reg.SUM16_SIGN=ram_read_dword((void *)&(shw_knl1_reg.SUM16_SIGN));
	*ctrl=ssw_knl1_reg.SUM16_SIGN;
}
/**************************************************/
void knl1_set_SUM16_output(long output);
void knl1_set_SUM16_output(long output)
{
	typedef union{
		long   qw;
		int    dw[2];
	}DW2QW;
	DW2QW	d2q;

	d2q.qw=output;
	ssw_knl1_reg.SUM16_1=d2q.dw[0];
	ssw_knl1_reg.SUM16_0=d2q.dw[1];
	ram_write_dword((void *)&(shw_knl1_reg.SUM16_0),ssw_knl1_reg.SUM16_0);
	ram_write_dword((void *)&(shw_knl1_reg.SUM16_1),ssw_knl1_reg.SUM16_1);
}
/**************************************************/
void knl1_get_TRS16_ctrl1(int *ctrl);
void knl1_get_TRS16_ctrl1(int *ctrl)
{
	ssw_knl1_reg.CTRL_TRS16_1=ram_read_dword((void *)&(shw_knl1_reg.CTRL_TRS16_1));
	*ctrl=ssw_knl1_reg.CTRL_TRS16_1;
}
/**************************************************/
void knl1_get_TRS16_ctrl0(int *ctrl);
void knl1_get_TRS16_ctrl0(int *ctrl)
{
	ssw_knl1_reg.CTRL_TRS16_1=ram_read_dword((void *)&(shw_knl1_reg.CTRL_TRS16_0));
	*ctrl=ssw_knl1_reg.CTRL_TRS16_0;
}

/**************************************************/
void knl1_get_BLK16_ctrl(int *ctrl);
void knl1_get_BLK16_ctrl(int *ctrl)
{
	ssw_knl1_reg.CTRL_BLK16=ram_read_dword((void *)&(shw_knl1_reg.CTRL_BLK16));
	*ctrl=ssw_knl1_reg.CTRL_BLK16;
}

/* end of sw_reg_knl1.c */
