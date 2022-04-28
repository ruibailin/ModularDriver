/*---------------------------
 * platform.c
 *  Created on: Jul 10, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Universal driver platform
 *But need to change resource
 *
 *
 *---------------------------
 */


#include "c_share.h"


#include <linux/device.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>
/**************************************************/
static struct resource pfm_dev_res[]= {
		[0] = {
				.start	= DEV_START_MEM,
				.end	= DEV_START_MEM+0x50,
				.flags	= IORESOURCE_MEM,
		},
		[1] = {
				.start	= DEV_START_MEM+0x400,
				.end	= DEV_START_MEM+0x400+0x94,
				.flags	= IORESOURCE_MEM,
		},
		[2] = {
				.start	= DEV_START_MEM+0x0800,
				.end	= DEV_START_MEM+0x0800+0x34,
				.flags	= IORESOURCE_MEM,
		},
		[3] = {
				.start	= DEV_START_MEM+0x0C00,
				.end	= DEV_START_MEM+0x0C00+0x1C,
				.flags	= IORESOURCE_MEM,
		},
		[4] = {
				.start	= 0,                  /*ARM IRQ_EINT(7)*/
				.end	= 7,
				.flags	= IORESOURCE_IRQ,
		},
};

/**************************************************/
static struct platform_device pfm_dev = {
		 	 .name 			= DEV_MODULE_NAME,
			 .id			= 0,
		 	 .num_resources	= ARRAY_SIZE(pfm_dev_res),
			 .resource		= pfm_dev_res,
};

/**************************************************/
static void pfm_dev_release(struct device *dev);
static void pfm_dev_release(struct device *dev)
{
	unsigned long addr;
	addr=(long)dev;
	os_print("Dcvice:Release device address is %lx !\n",addr);
}
/**************************************************/
int dev_module_func(init)(void);
int dev_module_func(init)()
{
	int ret;
	unsigned long addr;
	os_print("Dcvice:%s go to register device!\n",DEV_MODULE_NAME);
	addr=(long)&pfm_dev;
	os_print("Dcvice:Platform device address is %lx !\n",addr);
	ret=platform_device_register(&pfm_dev);
    if (ret)
        os_print("Dcvice:%s fail to register device,error is %d!\n",DEV_MODULE_NAME,ret);
    else
    	pfm_dev.dev.release=pfm_dev_release;
	return(ret);
}
/**************************************************/
void dev_module_func(exit)(void);
void dev_module_func(exit)()
{
    os_print("Dcvice:%s go to unregister device!\n",DEV_MODULE_NAME);
	platform_device_unregister(&pfm_dev);
}
/* end of platform.c */
