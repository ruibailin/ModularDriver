
/*---------------------------
 * cve_top_reg.c
 *  Created on: 2017年7月28日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *
 *
 *
 *
 *
 *---------------------------
 */

#include "c_share.h"

#include <linux/ioport.h>
#include <linux/io.h>
/**************************************************/
typedef struct{
    int VERSION;                 	// 0x0
    void *START_ADDR;          		// 0x4
    void *END_ADDR;            		// 0x8
    int CLR_INT;           			// 0xc

    int IRQ_STATE;               	// 0x10
    int AXI_ID;           			// 0x14
    void *FRM1_ADDR;             	// 0x18
    void *FRM2_ADDR;             	// 0x1c

    void *WB_ADDR;           		// 0x20
    int IMG_SIZE;              		// 0x24
    int Start;                   	// 0x28
    int ENDIAN_MODE;             	// 0x2c

    int BLK1_ADDR;             		// 0x30
    int BLK2_ADDR;             		// 0x34
    int BLK_SIZE;              		// 0x38
    int AXILW_CNT;               	// 0x3c

    void *RD_ERRADDR;              	// 0x40
    void *WR_ERRADDR;              	// 0x44
}T_HW_TOP_REG;

static	T_HW_TOP_REG	*hhw_top_reg;
/**************************************************/
void cve_top_set_base_addr(void *top);
void cve_top_set_base_addr(void *top)
{
	hhw_top_reg=(T_HW_TOP_REG *)top;
}
/**************************************************/
int cve_top_get_irq_state(void);
int cve_top_get_irq_state(void)
{
	void __iomem *reg;
	int state;
	reg=&(hhw_top_reg->IRQ_STATE);
	state=ioread32(reg);
	state &= 0xE0001FFF;
	return(state);
}
/**************************************************/
int cve_top_get_irq_done(void);
int cve_top_get_irq_done(void)
{
	void __iomem *reg;
	int state;
	reg=&(hhw_top_reg->IRQ_STATE);
	state=ioread32(reg);
	state &= 0x80000000;
	if(state!=0)
		state=0x01;
	return(state);
}
/**************************************************/
int cve_top_get_irq_axi(void);
int cve_top_get_irq_axi(void)
{
	void __iomem *reg;
	int state;
	reg=&(hhw_top_reg->IRQ_STATE);
	state=ioread32(reg);
	state &= 0x60000000;
	return(state);
}
/**************************************************/
int cve_top_get_irq_err(void);
int cve_top_get_irq_err(void)
{
	void __iomem *reg;
	int state;
	reg=&(hhw_top_reg->IRQ_STATE);
	state=ioread32(reg);
	state &= 0x00001FFF;
	return(state);
}
/* end of cve_top_reg.c */
