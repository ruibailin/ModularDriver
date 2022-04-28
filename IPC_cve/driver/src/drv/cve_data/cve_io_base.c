
/*---------------------------
 * cve_io_base.c
 *  Created on: 2017年7月27日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *处理数据对象io_base
 *
 *
 *
 *
 *---------------------------
 */

#include "c_share.h"
#include <linux/ioport.h>
#include <linux/platform_device.h>
static  void __iomem *io_base;
 /**************************************************/
#include <linux/gfp.h>
#include <linux/slab.h>
void cve_io_init_base(void);						/*For test in Ubuntu Only*/
void cve_io_init_base(void)
{
	io_base=kmalloc(4096,GFP_KERNEL);
	if(io_base == NULL)
		os_print("Faill to alloc 4096 mem\n");
}

/**************************************************/
void cve_io_set_base(void *base);
void cve_io_set_base(void *base)
{
	io_base=base;
}
/**************************************************/
void *cve_io_get_base(void);
void *cve_io_get_base(void)
{
	return(io_base);
}
/**************************************************/
#include <linux/io.h>
int cve_io_read_dword(int offset);
int cve_io_read_dword(int offset)
{
	int val;
	void __iomem *reg;
	reg=(void *)(io_base+offset);
	val=ioread32(reg);
	return(val);
}
/**************************************************/
void cve_io_write_dword(int offset,int val);
void cve_io_write_dword(int offset,int val)
{
	void __iomem *reg;
	reg=(void *)(io_base+offset);
	iowrite32(val,reg);
}

/* end of cve_io_base.c */
