/*---------------------------
 * sw_reg_top.c
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


#ifndef T_SW_TOP_REG
typedef struct{
    DWORD VERSION;                 	// 0x0
    void *START_ADDR;          		// 0x4
    void *END_ADDR;            		// 0x8
    DWORD CLR_INT;           		// 0xc

    DWORD IRQ_STATE;               	// 0x10
    DWORD AXI_ID;           		// 0x14
    void *FRM1_ADDR;             	// 0x18
    void *FRM2_ADDR;             	// 0x1c

    void *WB_ADDR;           		// 0x20
    DWORD IMG_SIZE;              	// 0x24
    DWORD Start;                   	// 0x28
    DWORD ENDIAN_MODE;             	// 0x2c

    DWORD BLK1_ADDR;             	// 0x30
    DWORD BLK2_ADDR;             	// 0x34
    DWORD BLK_SIZE;              	// 0x38
    DWORD AXILW_CNT;               	// 0x3c

    void *RD_ERRADDR;              // 0x40
    void *WR_ERRADDR;              // 0x44
}T_SW_TOP_REG;
#endif

static	T_SW_TOP_REG	ssw_top_reg, shw_top_reg;

/**************************************************/
void top_get_base_addr(void **top);
void top_get_base_addr(void **top)
{
	*top=(void *)&shw_top_reg;
}

/**************************************************/
void top_ini_hw_reg(void);
void top_ini_hw_reg(void)
{
	ram_write_dword((void *)&(shw_top_reg.CLR_INT),0x00);
	ram_write_dword((void *)&(shw_top_reg.IRQ_STATE),0x00);
	ram_write_dword((void *)&(shw_top_reg.Start),0x00);
}
/**************************************************/
void top_get_start_reg(DWORD *status);
void top_get_start_reg(DWORD *status)
{
	ssw_top_reg.Start=ram_read_dword((void *)&(shw_top_reg.Start));
	*status= ssw_top_reg.Start;
}

/**************************************************/
void top_get_ddr_addr(void **start,void **end);
void top_get_ddr_addr(void **start,void **end)
{
		ssw_top_reg.START_ADDR=ram_read_addr((void *)&(shw_top_reg.START_ADDR));
		*start=ssw_top_reg.START_ADDR;
		ssw_top_reg.END_ADDR=ram_read_addr((void *)&(shw_top_reg.END_ADDR));
		*end=ssw_top_reg.END_ADDR;
}

/**************************************************/
#define ERR_FRM_ADDR	-1
int top_get_frm_addr(void **frm1, void **frm2);
int top_get_frm_addr(void **frm1, void **frm2)
{
	ssw_top_reg.FRM1_ADDR=ram_read_addr((void *)&(shw_top_reg.FRM1_ADDR));
	ssw_top_reg.FRM2_ADDR=ram_read_addr((void *)&(shw_top_reg.FRM2_ADDR));

	*frm1=ssw_top_reg.FRM1_ADDR;
	*frm2=ssw_top_reg.FRM2_ADDR;
	if(((int)ssw_top_reg.FRM1_ADDR&0x7)!=0)	return ERR_FRM_ADDR;
	if(((int)ssw_top_reg.FRM2_ADDR&0x7)!=0)	return ERR_FRM_ADDR;

	return 0;
}

/**************************************************/
#define ERR_WB_ADDR	-2
int top_get_wb_addr(void **wb);
int top_get_wb_addr(void **wb)
{
	ssw_top_reg.WB_ADDR=ram_read_addr((void *)&(shw_top_reg.WB_ADDR));
	*wb=ssw_top_reg.WB_ADDR;
	if(((int)ssw_top_reg.WB_ADDR&0x7)!=0)	return ERR_WB_ADDR;
	return 0;
}

/**************************************************/
#define IMAGE_D1	4
#define IMAGE_VGA	3
#define IMAGE_CIF	2
#define IMAGE_QCIF	1
#define IMAGE_ERROR	0
static int is_valid_img_size(void);
static int is_valid_img_size()
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
	}W2DW;
	W2DW	size;
	size.dw=ssw_top_reg.IMG_SIZE;
	if((size.w[1]==720)&&(size.w[0]==576)) return(IMAGE_D1);
	if((size.w[1]==640)&&(size.w[0]==480)) return(IMAGE_VGA);
	if((size.w[1]==352)&&(size.w[0]==288)) return(IMAGE_CIF);
	if((size.w[1]==176)&&(size.w[0]==144)) return(IMAGE_QCIF);
	return(0);
}

#define ERR_IMG_SIZE	-3
int top_get_img_size(int *w,int *h);
int top_get_img_size(int *w,int *h)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
	}W2DW;
	W2DW	size;
	ssw_top_reg.IMG_SIZE=ram_read_dword((void *)&(shw_top_reg.IMG_SIZE));
	size.dw=ssw_top_reg.IMG_SIZE;

	*w=(int)size.w[1];
	*h=(int)size.w[0];
	if(is_valid_img_size()==0) return ERR_IMG_SIZE;
	return(0);
}

/**************************************************/
#define ERR_BLK_SIZE	-4
int top_get_blk_size(int *w,int *h);
int top_get_blk_size(int *w,int *h)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
	}W2DW;
	W2DW	size;

	ssw_top_reg.BLK_SIZE=ram_read_dword((void *)&(shw_top_reg.BLK_SIZE));
	size.dw=ssw_top_reg.BLK_SIZE;
	*w=(int)size.w[1];
	*h=(int)size.w[0];

	if((*w&&0x7)!=0) return ERR_BLK_SIZE;
	if((*h&&0x7)!=0) return ERR_BLK_SIZE;
	return 0;
}

/**************************************************/
#define ERR_BLK_POS	-5
int top_get_blk1_pos(int *x,int *y);
int top_get_blk1_pos(int *x,int *y)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
	}W2DW;
	W2DW	size;

	ssw_top_reg.BLK1_ADDR=ram_read_dword((void *)&(shw_top_reg.BLK1_ADDR));
	size.dw=ssw_top_reg.BLK1_ADDR;
	*y=(int)size.w[1];
	*x=(int)size.w[0];

	if((*x&&0x7)!=0) return ERR_BLK_POS;
	if((*y&&0x7)!=0) return ERR_BLK_POS;

	return 0;
}

/**************************************************/
int top_get_blk2_pos(int *x,int *y);
int top_get_blk2_pos(int *x,int *y)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
	}W2DW;
	W2DW	size;

	ssw_top_reg.BLK2_ADDR=ram_read_dword((void *)&(shw_top_reg.BLK2_ADDR));
	size.dw=ssw_top_reg.BLK2_ADDR;
	*y=(int)size.w[1];
	*x=(int)size.w[0];

	if((*x&&0x7)!=0) return ERR_BLK_POS;
	if((*y&&0x7)!=0) return ERR_BLK_POS;

	return 0;
}


/**************************************************/
void top_set_irq_state(DWORD state);
void top_set_irq_state(DWORD state)
{
	ssw_top_reg.IRQ_STATE=state;
	ram_write_dword((void *)&(shw_top_reg.IRQ_STATE),ssw_top_reg.IRQ_STATE);
}

/**************************************************/
void top_get_clr_irq_state(DWORD *bit);
void top_get_clr_irq_state(DWORD *bit)
{
	ssw_top_reg.CLR_INT=ram_read_dword((void *)&(shw_top_reg.CLR_INT));
	ssw_top_reg.CLR_INT &= 0x03;
	*bit = ssw_top_reg.CLR_INT;
}

/**************************************************/
void top_clr_clr_irq_state(DWORD bit);
void top_clr_clr_irq_state(DWORD bit)
{
	DWORD	old;
	old=ssw_top_reg.CLR_INT;
	old &= (~bit);
	ssw_top_reg.CLR_INT = old;
	ram_write_dword((void *)&(shw_top_reg.CLR_INT),ssw_top_reg.CLR_INT);
}

/**************************************************/
void top_get_writeback_id(BYTE *id);
void top_get_writeback_id(BYTE *id)
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	B2DW	b2dw;

	ssw_top_reg.AXI_ID=ram_read_dword((void *)&(shw_top_reg.AXI_ID));
	b2dw.dw=ssw_top_reg.AXI_ID;
	b2dw.b[2] &= 0x0F;
	*id = b2dw.b[2];
}
/**************************************************/
void top_get_frame_id(BYTE *id);
void top_get_frame_id(BYTE *id)
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	B2DW	b2dw;

	ssw_top_reg.AXI_ID=ram_read_dword((void *)&(shw_top_reg.AXI_ID));
	b2dw.dw=ssw_top_reg.AXI_ID;
	b2dw.b[0] &= 0x0F;
	*id=b2dw.b[0];
}

/**************************************************/
void top_get_lowband_parameter(WORD *para);
void top_get_lowband_parameter(WORD *para)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
	}W2DW;
	W2DW	w2dw;
	ssw_top_reg.AXILW_CNT=ram_read_dword((void *)&(shw_top_reg.AXILW_CNT));
	w2dw.dw=ssw_top_reg.AXILW_CNT;
	*para=w2dw.w[0];
}

/**************************************************/
void top_set_lowband_counter(WORD cnt);
void top_set_lowband_counter(WORD cnt)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
	}W2DW;
	W2DW	w2dw;

	w2dw.dw=ssw_top_reg.AXILW_CNT;
	w2dw.w[0]=cnt;
	ssw_top_reg.AXILW_CNT=w2dw.dw;
	ram_write_dword((void *)&(shw_top_reg.AXILW_CNT),ssw_top_reg.AXILW_CNT);
}

/**************************************************/
void top_set_read_error_addr(void *addr);
void top_set_read_error_addr(void *addr)
{
	ssw_top_reg.RD_ERRADDR=addr;
	ram_write_addr((void *)&(shw_top_reg.RD_ERRADDR),ssw_top_reg.RD_ERRADDR);
}

/**************************************************/
void top_set_write_error_addr(void *addr);
void top_set_write_error_addr(void *addr)
{
	ssw_top_reg.WR_ERRADDR=addr;
	ram_write_addr((void *)&(shw_top_reg.WR_ERRADDR),ssw_top_reg.WR_ERRADDR);
}

/* end of sw_reg_top.c */
