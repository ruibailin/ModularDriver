
/*---------------------------
 * client.c
 *  Created on: Apr 16, 2019
 *      Author: Steve Rui
 *---------------------------
 *
 *
 *
 *
 *
 *---------------------------
 */

#include "01import.h"
/**************************************************/
#include <linux/irqreturn.h>
extern int drv_int_server(int irq, void *data);
static irqreturn_t drv_isr(int irq, void *data);
static irqreturn_t drv_isr(int irq, void *data)
{
	int i;
	irqreturn_t	ret;
	i=drv_int_server(irq,data);
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
int drv_int_set_isr(int irq,void *data);
int drv_int_set_isr(int irq,void *data)
{
	int ret;
	ret=request_irq(irq, drv_isr, IRQF_SHARED, DRV_MODULE_NAME, data);
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

/**************************************************/
/* end of client.c */
