/*---------------------------
 * hw_reg_top.c
 *  Created on: Jun 8, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *���¶������Ӳ���ֲ��еĶ��壬��Щ���岻����
 * 1.�������淶������ͳһ
 * 2.�����壬��BLK1_ADDR.��ʵ��block��ͼ���е�λ��(position)
 * ��Щ�ں��������и�������
  *---------------------------
 */


#include "c_share.h"

#ifndef T_HW_TOP_REG
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
}T_HW_TOP_REG;
#endif

static	T_HW_TOP_REG	hsw_top_reg, *hhw_top_reg;

/**************************************************/
void top_ini_base_addr(void *top);
void top_ini_base_addr(void *top)
{
	hhw_top_reg=(T_HW_TOP_REG *)top;
}

/**************************************************/
void top_ini_sw_reg(void);
void top_ini_sw_reg(void)
{
	hsw_top_reg.CLR_INT=ram_read_dword((void *)&(hhw_top_reg->CLR_INT));
	hsw_top_reg.IRQ_STATE=ram_read_dword((void *)&(hhw_top_reg->IRQ_STATE));
	hsw_top_reg.Start=ram_read_dword((void *)&(hhw_top_reg->Start));
}

/**************************************************/
void top_set_start_reg(DWORD status);
void top_set_start_reg(DWORD status)
{
	hsw_top_reg.Start=status;
	ram_write_dword((void *)&(hhw_top_reg->Start),hsw_top_reg.Start);
}

/**************************************************/
void top_set_ddr_addr(void *start,void *end);
void top_set_ddr_addr(void *start,void *end)
{
	hsw_top_reg.START_ADDR=start;
	ram_write_addr((void *)&(hhw_top_reg->START_ADDR),hsw_top_reg.START_ADDR);
	hsw_top_reg.END_ADDR=end;
	ram_write_addr((void *)&(hhw_top_reg->END_ADDR),hsw_top_reg.END_ADDR);
}

/**************************************************/
#define ERR_FRM_ADDR	-1
int top_set_frm_addr(void *frm1, void *frm2);
int top_set_frm_addr(void *frm1, void *frm2)
{
	hsw_top_reg.FRM1_ADDR=frm1;
	hsw_top_reg.FRM2_ADDR=frm2;

	DWORD	ii;
	ii=(DWORD)hsw_top_reg.FRM1_ADDR;
	if((ii&0x7)!=0)	return ERR_FRM_ADDR;
	ii=(DWORD)hsw_top_reg.FRM2_ADDR;
	if((ii&0x7)!=0)	return ERR_FRM_ADDR;
	ram_write_addr((void *)&(hhw_top_reg->FRM1_ADDR),hsw_top_reg.FRM1_ADDR);
	ram_write_addr((void *)&(hhw_top_reg->FRM2_ADDR),hsw_top_reg.FRM2_ADDR);
	return 0;
}

/**************************************************/
#define ERR_WB_ADDR	-2
int top_set_wb_addr(void *wb);
int top_set_wb_addr(void *wb)
{
	hsw_top_reg.WB_ADDR=wb;
	DWORD	ii;
	ii=(DWORD)hsw_top_reg.WB_ADDR;
	if((ii&0x7)!=0)	return ERR_WB_ADDR;
	ram_write_addr((void *)&(hhw_top_reg->WB_ADDR),hsw_top_reg.WB_ADDR);
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
	size.dw=hsw_top_reg.IMG_SIZE;
	if((size.w[1]==720)&&(size.w[0]==576)) return(IMAGE_D1);
	if((size.w[1]==640)&&(size.w[0]==480)) return(IMAGE_VGA);
	if((size.w[1]==352)&&(size.w[0]==288)) return(IMAGE_CIF);
	if((size.w[1]==176)&&(size.w[0]==144)) return(IMAGE_QCIF);
	return(0);
}

/**************************************************/
#define ERR_IMG_SIZE	-3
int top_set_img_size(WORD w,WORD h);
int top_set_img_size(WORD w,WORD h)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
	}W2DW;
	W2DW	size;
	size.w[1]=w;
	size.w[0]=h;
	hsw_top_reg.IMG_SIZE=size.dw;
	if(is_valid_img_size()==0) return ERR_IMG_SIZE;
	ram_write_dword((void *)&(hhw_top_reg->IMG_SIZE),hsw_top_reg.IMG_SIZE);
	return(0);
}

/**************************************************/
#define ERR_BLK_SIZE	-4
int top_set_blk_size(WORD w,WORD h);
int top_set_blk_size(WORD w,WORD h)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
	}W2DW;
	W2DW	size;
	if((w&&0x7)!=0) return ERR_BLK_SIZE;
	if((h&&0x7)!=0) return ERR_BLK_SIZE;
	size.w[1]=w;
	size.w[0]=h;
	hsw_top_reg.BLK_SIZE=size.dw;
	ram_write_dword((void *)&(hhw_top_reg->BLK_SIZE),hsw_top_reg.BLK_SIZE);
	return 0;
}

/**************************************************/
#define ERR_BLK_POS	-5
int top_set_blk1_pos(WORD x,WORD y);
int top_set_blk1_pos(WORD x,WORD y)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
	}W2DW;
	W2DW	size;
	if((x&&0x7)!=0) return ERR_BLK_POS;
	if((y&&0x7)!=0) return ERR_BLK_POS;
	size.w[1]=y;
	size.w[0]=x;
	hsw_top_reg.BLK1_ADDR=size.dw;
	ram_write_dword((void *)&(hhw_top_reg->BLK1_ADDR),hsw_top_reg.BLK1_ADDR);
	return 0;
}

/**************************************************/
int top_set_blk2_pos(WORD x,WORD y);
int top_set_blk2_pos(WORD x,WORD y)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
	}W2DW;
	W2DW	size;
	if((x&&0x7)!=0) return ERR_BLK_POS;
	if((y&&0x7)!=0) return ERR_BLK_POS;
	size.w[1]=y;
	size.w[0]=x;
	hsw_top_reg.BLK1_ADDR=size.dw;
	ram_write_dword((void *)&(hhw_top_reg->BLK2_ADDR),hsw_top_reg.BLK2_ADDR);
	return 0;
}


/**************************************************/
void top_get_irq_state(DWORD *state);
void top_get_irq_state(DWORD *state)
{
	hsw_top_reg.IRQ_STATE=ram_read_dword((void *)&(hhw_top_reg->IRQ_STATE));
	*state=hsw_top_reg.IRQ_STATE;
}

/**************************************************/
void top_set_clr_irq_state(DWORD bit);
void top_set_clr_irq_state(DWORD bit)
{
	DWORD	old;
	old=hsw_top_reg.CLR_INT;
	old |= bit;
	hsw_top_reg.CLR_INT = old;
	ram_write_dword((void *)&(hhw_top_reg->CLR_INT),hsw_top_reg.CLR_INT);
}

/**************************************************/
void top_set_writeback_id(BYTE id);
void top_set_writeback_id(BYTE id)
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	B2DW	b2dw;
	hsw_top_reg.AXI_ID=ram_read_dword((void *)&(hhw_top_reg->AXI_ID));
	b2dw.dw=hsw_top_reg.AXI_ID;
	id &= 0x0F;
	b2dw.b[2] |= id;
	hsw_top_reg.AXI_ID=b2dw.dw;
	ram_write_dword((void *)&(hhw_top_reg->AXI_ID),hsw_top_reg.AXI_ID);
}
/**************************************************/
void top_set_frame_id(BYTE id);
void top_set_frame_id(BYTE id)
{
	typedef union{
		DWORD  dw;
		BYTE   b[4];
	}B2DW;
	B2DW	b2dw;
	hsw_top_reg.AXI_ID=ram_read_dword((void *)&(hhw_top_reg->AXI_ID));
	b2dw.dw=hsw_top_reg.AXI_ID;
	id &= 0x0F;
	b2dw.b[0] |= id;
	hsw_top_reg.AXI_ID=b2dw.dw;
	ram_write_dword((void *)&(hhw_top_reg->AXI_ID),hsw_top_reg.AXI_ID);
}

/**************************************************/
void top_set_lowband_parameter(WORD para);
void top_set_lowband_parameter(WORD para)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
	}W2DW;
	W2DW	w2dw;
	hsw_top_reg.AXILW_CNT=ram_read_dword((void *)&(hhw_top_reg->AXILW_CNT));
	w2dw.dw=hsw_top_reg.AXILW_CNT;
	w2dw.w[0]=para;
	hsw_top_reg.AXILW_CNT=w2dw.dw;
	ram_write_dword((void *)&(hhw_top_reg->AXILW_CNT),hsw_top_reg.AXILW_CNT);
}

/**************************************************/
void top_get_lowband_counter(WORD *cnt);
void top_get_lowband_counter(WORD *cnt)
{
	typedef union{
		DWORD  dw;
		WORD   w[2];
	}W2DW;
	W2DW	w2dw;
	hsw_top_reg.AXILW_CNT=ram_read_dword((void *)&(hhw_top_reg->AXILW_CNT));
	w2dw.dw=hsw_top_reg.AXILW_CNT;
	*cnt=w2dw.w[0];
}

/**************************************************/
void top_get_read_error_addr(void **addr);
void top_get_read_error_addr(void **addr)
{
	void *ptr;
	hsw_top_reg.RD_ERRADDR=ram_read_addr((void *)&(hhw_top_reg->RD_ERRADDR));
	ptr=(void *)hsw_top_reg.RD_ERRADDR;
	*addr=ptr;
}

/**************************************************/
void top_get_write_error_addr(void **addr);
void top_get_write_error_addr(void **addr)
{
	void *ptr;
	hsw_top_reg.WR_ERRADDR=ram_read_addr((void *)&(hhw_top_reg->WR_ERRADDR));
	ptr=(void *)hsw_top_reg.WR_ERRADDR;
	*addr=ptr;
}
/* end of hw_reg_top.c */
