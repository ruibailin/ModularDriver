
/*---------------------------
 * device.c
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

#include <linux/device.h>
#include <linux/ioport.h>
#include "01import.h"
/**************************************************/
static struct resource pfm_dev_res[]= {
		[0] = {
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
/**************************************************/
static void pfm_dev_release(struct device *dev);
static void pfm_dev_release(struct device *dev)
{

}
/**************************************************/
int pfm_dev_init(void);
int pfm_dev_init()
{
	int ret;
	unsigned long addr;
	addr=(long)&pfm_dev;
	ret=platform_device_register(&pfm_dev);
    if (ret)
        os_print("Dcvice:%s fail to register device,error is %d!\n",DEV_MODULE_NAME,ret);
    else
    	pfm_dev.dev.release=pfm_dev_release;
	return(ret);
}
/**************************************************/
void pfm_dev_exit(void);
void pfm_dev_exit()
{
    os_print("Dcvice:%s go to unregister device!\n",DEV_MODULE_NAME);
	platform_device_unregister(&pfm_dev);
}

/**************************************************/
/* end of device.c */
