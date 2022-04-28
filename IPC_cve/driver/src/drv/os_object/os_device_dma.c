/*---------------------------
 * os_device_dma.c
 *  Created on: Jul 9, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *vmem: virtual memory, mapped address
 *pmem: physical memory, unmapped address
 *wb:write bufferable
 *
 *---------------------------
 */


#include "c_share.h"

#include <linux/dma-mapping.h>
#include <linux/device.h>
/**************************************************/
void *os_dma_alloc_vmem(void *dev,int size,void *pmem);
void *os_dma_alloc_vmem(void *dev,int size,void *pmem)
{
	void *ret;
	ret=dma_alloc_coherent((struct device*)dev, size, (dma_addr_t *)pmem, GFP_KERNEL);
	return(ret);
}
/**************************************************/
void os_dma_free_vmem(void *dev,int size,void *vaddr,void *pmem);
void os_dma_free_vmem(void *dev,int size,void *vaddr,void *pmem)
{
	dma_addr_t *handle;
	handle=(dma_addr_t *)pmem;
	dma_alloc_coherent((struct device*)dev, size, vaddr, *handle);
}
/**************************************************/
void *os_dma_alloc_wb_vmem(void *dev,int size,void *pmem);
void *os_dma_alloc_wb_vmem(void *dev,int size,void *pmem)
{
	void *ret;
	ret=dma_alloc_writecombine((struct device*)dev, size, (dma_addr_t *)pmem, GFP_KERNEL);
	return(ret);
}
/**************************************************/
void os_dma_free_wb_vmem(void *dev,int size,void *vaddr,void *pmem);
void os_dma_free_wb_vmem(void *dev,int size,void *vaddr,void *pmem)
{
	dma_addr_t *handle;
	handle=(dma_addr_t *)pmem;
	dma_free_writecombine((struct device*)dev, size, vaddr, *handle);
}
/* end of os_device_dma.c */
