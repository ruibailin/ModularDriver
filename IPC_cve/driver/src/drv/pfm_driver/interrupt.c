/*---------------------------
 * interrupt.c
 *  Created on: Jul 8, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Interrupt server:isr
 *Universal driver interrupt server
 *Don't change it
 *
 *
 *---------------------------
 */

#include "c_share.h"

/**************************************************/
#include <linux/irqreturn.h>
extern int pfm_drv_int_func(server)(int irq, void *data);
static irqreturn_t pfm_dvr_isr(int irq, void *data);
static irqreturn_t pfm_dvr_isr(int irq, void *data)
{
	int i;
	irqreturn_t	ret;
	i=pfm_drv_int_func(server)(irq,data);
	if(i==0)
		ret=IRQ_NONE;
	else if(i==1)
		ret=IRQ_HANDLED;
	else
		ret=2;					/*IRQ_WAKE_THREAD;*/
	return(ret);
}

/**************************************************/
#include <linux/interrupt.h>
#include <asm-generic/errno-base.h>
int pfm_drv_set_isr(int irq,void *data);
int pfm_drv_set_isr(int irq,void *data)
{
	int ret;
	ret=request_irq(irq, pfm_dvr_isr, IRQF_SHARED, DRV_MODULE_NAME, data);
	if (ret != 0)
	{
	   if (ret == -EINVAL)
		   os_print("Bad irq number or handler for %s\n",DRV_MODULE_NAME);
	   if (ret == -EBUSY)
	    	os_print("irq %d for %s is busy!\n", irq, DRV_MODULE_NAME);
	}
	else
    	os_print("irq %d for %s is installed!\n", irq, DRV_MODULE_NAME);
	return(ret);
}
/* end of interrupt.c */
