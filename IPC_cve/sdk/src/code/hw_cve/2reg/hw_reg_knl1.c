/*---------------------------
 * hw_reg_knl1.c
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

#ifndef T_HW_KNL1_REG
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
}T_HW_KNL1_REG;
#endif

static	T_HW_KNL1_REG	hsw_knl1_reg, *hhw_knl1_reg;
static	WORD	sw_knl1_map[256];

/**************************************************/
void knl1_ini_base_addr(void *knl1);
void knl1_ini_base_addr(void *knl1)
{
	hhw_knl1_reg=(T_HW_KNL1_REG *)knl1;
}

/**************************************************/
void knl1_ini_sw_reg(void);
void knl1_ini_sw_reg(void)
{

	hsw_knl1_reg.KNL_EN1=ram_read_dword((void *)&(hhw_knl1_reg->KNL_EN1));

	hsw_knl1_reg.CTRL_TRS8_0=ram_read_dword((void *)&(hhw_knl1_reg->CTRL_TRS8_0));
	hsw_knl1_reg.CTRL_TRS8_1=ram_read_dword((void *)&(hhw_knl1_reg->CTRL_TRS8_1));
	hsw_knl1_reg.CTRL_TRS16_0=ram_read_dword((void *)&(hhw_knl1_reg->CTRL_TRS16_0));
	hsw_knl1_reg.CTRL_TRS16_1=ram_read_dword((void *)&(hhw_knl1_reg->CTRL_TRS16_1));
	hsw_knl1_reg.CTRL_BLK16=ram_read_dword((void *)&(hhw_knl1_reg->CTRL_BLK16));
	hsw_knl1_reg.CTRL_MAP=ram_read_dword((void *)&(hhw_knl1_reg->CTRL_MAP));
	hsw_knl1_reg.MAP_RESTORE=0;
	hsw_knl1_reg.SUM16_SIGN=ram_read_dword((void *)&(hhw_knl1_reg->SUM16_SIGN));
	hsw_knl1_reg.SUM16_0=ram_read_dword((void *)&(hhw_knl1_reg->SUM16_0));
	hsw_knl1_reg.SUM16_1=ram_read_dword((void *)&(hhw_knl1_reg->SUM16_1));
	hsw_knl1_reg.SUM8=ram_read_dword((void *)&(hhw_knl1_reg->SUM8));
	hsw_knl1_reg.CTRL_HST=ram_read_dword((void *)&(hhw_knl1_reg->CTRL_HST));

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
void knl1_set_opr_enabler(DWORD opr);
void knl1_set_opr_enabler(DWORD opr)
{
	hsw_knl1_reg.KNL_EN1 |= opr;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}
/**************************************************/
void knl1_clr_opr_enabler(DWORD opr);
void knl1_clr_opr_enabler(DWORD opr)
{
	hsw_knl1_reg.KNL_EN1 &= (~opr);
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}

/**************************************************/
void knl1_set_MAP_opr(void);
void knl1_set_MAP_opr(void)
{
	hsw_knl1_reg.KNL_EN1 |= OPR_MAP_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}
/**************************************************/
void knl1_set_MAP_mode(BYTE mode);
void knl1_set_MAP_mode(BYTE mode)
{
	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x00000001;
	old=hsw_knl1_reg.CTRL_MAP;
	old &= (~0x00000001);
	old |= new;
	hsw_knl1_reg.CTRL_MAP=old;

	ram_write_dword((void *)&(hhw_knl1_reg->CTRL_MAP),hsw_knl1_reg.CTRL_MAP);
}
/**************************************************/
void knl1_set_MAP_write(WORD data,BYTE addr);
void knl1_set_MAP_write(WORD data,BYTE addr)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
		BYTE   b[4];
	}B_W2DW;

	B_W2DW  b2dw;
	b2dw.dw=hsw_knl1_reg.MAP_RESTORE;
	b2dw.w[0]=data;
	b2dw.b[2]=addr;
	hsw_knl1_reg.MAP_RESTORE=b2dw.dw;

	ram_write_dword((void *)&(hhw_knl1_reg->MAP_RESTORE),hsw_knl1_reg.MAP_RESTORE);
	sw_knl1_map[addr]=data;
}
/**************************************************/
/*used by software CVE*/
WORD *knl1_get_MAP_table(void);
WORD *knl1_get_MAP_table(void)
{
	return(sw_knl1_map);
}
/**************************************************/
void knl1_clr_MAP_opr(void);
void knl1_clr_MAP_opr(void)
{
	hsw_knl1_reg.KNL_EN1 &= ~OPR_MAP_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}

/**************************************************/
void knl1_set_HST_opr(void);
void knl1_set_HST_opr(void)
{
	hsw_knl1_reg.KNL_EN1 |= OPR_HST_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}
/**************************************************/
void knl1_set_HST_mode(BYTE mode);
void knl1_set_HST_mode(BYTE mode)
{
	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x00000007;
	old=hsw_knl1_reg.CTRL_HST;
	old &= (~0x00000007);
	old |= new;
	hsw_knl1_reg.CTRL_TRS8_1=old;

	ram_write_dword((void *)&(hhw_knl1_reg->CTRL_HST),hsw_knl1_reg.CTRL_HST);
}
/**************************************************/
void knl1_clr_HST_opr(void);
void knl1_clr_HST_opr(void)
{
	hsw_knl1_reg.KNL_EN1 &= ~OPR_HST_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}


/**************************************************/
void knl1_set_TRS8_opr(void);
void knl1_set_TRS8_opr(void)
{
	hsw_knl1_reg.KNL_EN1 |= OPR_TRS8_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}
/**************************************************/
void knl1_set_TRS8_mode(BYTE vmode);
void knl1_set_TRS8_mode(BYTE vmode)
{
	DWORD	new,old;

	new=(DWORD)vmode;
	new &= 0x00000007;
	old=hsw_knl1_reg.CTRL_TRS8_1;
	old &= (~0x00000007);
	old |= new;
	hsw_knl1_reg.CTRL_TRS8_1=old;

	ram_write_dword((void *)&(hhw_knl1_reg->CTRL_TRS8_1),hsw_knl1_reg.CTRL_TRS8_1);
}

/**************************************************/
void knl1_set_TRS8_trs(BYTE low,BYTE high);
void knl1_set_TRS8_trs(BYTE low,BYTE high)
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	B2DW  b2dw;
	b2dw.dw=hsw_knl1_reg.CTRL_TRS8_0;
	b2dw.b[0]=low;
	b2dw.b[1]=high;
	hsw_knl1_reg.CTRL_TRS8_0=b2dw.dw;

	ram_write_dword((void *)&(hhw_knl1_reg->CTRL_TRS8_0),hsw_knl1_reg.CTRL_TRS8_0);
}

/**************************************************/
void knl1_set_TRS8_value(BYTE v0,BYTE v1,BYTE v2);
void knl1_set_TRS8_value(BYTE v0,BYTE v1,BYTE v2)
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	B2DW  b2dw;
	b2dw.dw=hsw_knl1_reg.CTRL_TRS8_1;
	b2dw.b[1]=v0;
	b2dw.b[2]=v1;
	b2dw.b[3]=v2;
	hsw_knl1_reg.CTRL_TRS8_1=b2dw.dw;

	ram_write_dword((void *)&(hhw_knl1_reg->CTRL_TRS8_1),hsw_knl1_reg.CTRL_TRS8_1);
}
/**************************************************/
void knl1_clr_TRS8_opr(void);
void knl1_clr_TRS8_opr(void)
{
	hsw_knl1_reg.KNL_EN1 &= ~OPR_TRS8_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}

/**************************************************/
void knl1_set_SUM8_opr(void);
void knl1_set_SUM8_opr(void)
{
	hsw_knl1_reg.KNL_EN1 |= OPR_SUM8_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}
/**************************************************/
void knl1_get_SUM8_output(int *output);
void knl1_get_SUM8_output(int *output)
{
	hsw_knl1_reg.SUM8=ram_read_dword((void *)&(hhw_knl1_reg->SUM8));
	*output=hsw_knl1_reg.SUM8;
}
/**************************************************/
void knl1_clr_SUM8_opr(void);
void knl1_clr_SUM8_opr(void)
{
	hsw_knl1_reg.KNL_EN1 &= ~OPR_SUM8_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}

/**************************************************/
void knl1_set_SUM16_opr(void);
void knl1_set_SUM16_opr(void)
{
	hsw_knl1_reg.KNL_EN1 |= OPR_SUM16_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}
/**************************************************/
void knl1_set_SUM16_mode(BYTE mode);
void knl1_set_SUM16_mode(BYTE mode)
{
	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x00000001;
	old=hsw_knl1_reg.SUM16_SIGN;
	old &= (~0x00000001);
	old |= new;
	hsw_knl1_reg.SUM16_SIGN=old;

	ram_write_dword((void *)&(hhw_knl1_reg->SUM16_SIGN),hsw_knl1_reg.SUM16_SIGN);
}
void knl1_get_SUM16_output(long *output);
void knl1_get_SUM16_output(long *output)
{
	typedef union{
		long   qw;
		int    dw[2];
	}DW2QW;
	DW2QW	d2q;
	hsw_knl1_reg.SUM16_0=ram_read_dword((void *)&(hhw_knl1_reg->SUM16_0));
	hsw_knl1_reg.SUM16_1=ram_read_dword((void *)&(hhw_knl1_reg->SUM16_1));
	d2q.dw[0]=hsw_knl1_reg.SUM16_1;
	d2q.dw[1]=hsw_knl1_reg.SUM16_0;

	*output=d2q.qw;
}
/**************************************************/
void knl1_clr_SUM16_opr(void);
void knl1_clr_SUM16_opr(void)
{
	hsw_knl1_reg.KNL_EN1 &= ~OPR_SUM16_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}

/**************************************************/
void knl1_set_TRS16_opr(void);
void knl1_set_TRS16_opr(void)
{
	hsw_knl1_reg.KNL_EN1 |= OPR_TRS16_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}
/**************************************************/
void knl1_set_TRS16_mode_value(BYTE vmode);
void knl1_set_TRS16_mode_value(BYTE vmode)
{
	DWORD	new,old;

	new=(DWORD)vmode;
	new &= 0x00000007;
	old=hsw_knl1_reg.CTRL_TRS16_1;
	old &= (~0x00000007);
	old |= new;
	hsw_knl1_reg.CTRL_TRS16_1=old;

	ram_write_dword((void *)&(hhw_knl1_reg->CTRL_TRS16_1),hsw_knl1_reg.CTRL_TRS16_1);
}
/**************************************************/
void knl1_set_TRS16_mode_sign(BYTE smode);
void knl1_set_TRS16_mode_sign(BYTE smode)
{
	DWORD	new,old;

	new=(DWORD)smode;
	new &= 0x00000001;
	new <<= 3;
	old=hsw_knl1_reg.CTRL_TRS16_1;
	old &= (~(0x00000001<<3));
	old |= new;
	hsw_knl1_reg.CTRL_TRS16_1=old;

	ram_write_dword((void *)&(hhw_knl1_reg->CTRL_TRS16_1),hsw_knl1_reg.CTRL_TRS16_1);
}
/**************************************************/
void knl1_set_TRS16_trs(WORD low,WORD high);
void knl1_set_TRS16_trs(WORD low,WORD high)
{
	typedef union{
		DWORD  dw;
		BYTE   w[2];
	}W2DW;
	W2DW  w2dw;
	w2dw.dw=hsw_knl1_reg.CTRL_TRS16_0;
	w2dw.w[0]=low;
	w2dw.w[1]=high;
	hsw_knl1_reg.CTRL_TRS16_0=w2dw.dw;

	ram_write_dword((void *)&(hhw_knl1_reg->CTRL_TRS16_0),hsw_knl1_reg.CTRL_TRS16_0);
}

/**************************************************/
void knl1_set_TRS16_value(BYTE v0,BYTE v1,BYTE v2);
void knl1_set_TRS16_value(BYTE v0,BYTE v1,BYTE v2)
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	B2DW  b2dw;
	b2dw.dw=hsw_knl1_reg.CTRL_TRS16_1;
	b2dw.b[1]=v0;
	b2dw.b[2]=v1;
	b2dw.b[3]=v2;
	hsw_knl1_reg.CTRL_TRS16_1=b2dw.dw;

	ram_write_dword((void *)&(hhw_knl1_reg->CTRL_TRS16_1),hsw_knl1_reg.CTRL_TRS16_1);
}
/**************************************************/
void knl1_clr_TRS16_opr(void);
void knl1_clr_TRS16_opr(void)
{
	hsw_knl1_reg.KNL_EN1 &= ~OPR_TRS16_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}

/**************************************************/
void knl1_set_BLK16_opr(void);
void knl1_set_BLK16_opr(void)
{
	hsw_knl1_reg.KNL_EN1 |= OPR_BLK16_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}
/**************************************************/
void knl1_set_BLK16_mode(BYTE mode);
void knl1_set_BLK16_mode(BYTE mode)
{
	DWORD	new,old;

	new=(DWORD)mode;
	new &= 0x00000003;
	new <<= 4;
	old=hsw_knl1_reg.CTRL_BLK16;
	old &= (~(0x00000003<<4));
	old |= new;
	hsw_knl1_reg.CTRL_BLK16=old;

	ram_write_dword((void *)&(hhw_knl1_reg->CTRL_BLK16),hsw_knl1_reg.CTRL_BLK16);
}
/**************************************************/
void knl1_set_BLK16_power(BYTE shift);
void knl1_set_BLK16_power(BYTE shift)
{
	DWORD	new,old;

	new=(DWORD)shift;
	new &= 0x0000000F;
	old=hsw_knl1_reg.CTRL_BLK16;
	old &= (~0x0000000F);
	old |= new;
	hsw_knl1_reg.CTRL_BLK16=old;

	ram_write_dword((void *)&(hhw_knl1_reg->CTRL_BLK16),hsw_knl1_reg.CTRL_BLK16);
}
/**************************************************/
void knl1_clr_BLK16_opr(void);
void knl1_clr_BLK16_opr(void)
{
	hsw_knl1_reg.KNL_EN1 &= ~OPR_BLK16_EN;
	ram_write_dword((void *)&(hhw_knl1_reg->KNL_EN1),hsw_knl1_reg.KNL_EN1);
}

/* end of hw_reg_knl1.c */
