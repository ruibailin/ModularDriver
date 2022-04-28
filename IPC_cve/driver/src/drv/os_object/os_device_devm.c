/*---------------------------
 * os_device_devm.c
 *  Created on: Jul 5, 2017
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
#include <linux/gfp.h>
#include <linux/slab.h>
#include <linux/device.h>
/**************************************************/
void *os_create_mem_devm(void *d,int size);
void *os_create_mem_devm(void *d,int size)
{
	return(devm_kzalloc((struct device *)d,size,GFP_KERNEL));
}
/**************************************************/
void os_destroy_mem_devm(void *d,void *p);
void os_destroy_mem_devm(void *d,void *p)
{
	devm_kfree((struct device *)d, p);
}
/**************************************************/
void *os_get_iomap_devm(void *d,void *res);
void *os_get_iomap_devm(void *d,void *res)
{
	void __iomem *io_base;
	io_base=devm_ioremap_resource((struct device *)d, (struct resource *)res);
	return(io_base);
}

/* end of os_device_devm.c */
