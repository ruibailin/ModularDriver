/*---------------------------
 * os_platform_device.c
 *  Created on: Jul 7, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *platform:pfm
 *platform_device:pdev
 *platform_driver:pdrv
 *platform_device_resource:pdrs
 *alloc:alc
 *put:
 *add:
 *
 *---------------------------
 */


#include "c_share.h"

#include <linux/platform_device.h>
/**************************************************/
void *os_pdev_get_resource(void *pdev);
void *os_pdev_get_resource(void *pdev)
{
	struct resource *pdrs;
/*	pdrs=platform_get_rsource((struct platform_device *)pdev,IORESOURCE_MEM,0);*/
	if(pdrs == NULL)
		os_print("Platform fails to get resource:name=%s\n",((struct platform_device *)pdev)->name);
	return(pdrs);
}

/**************************************************/
void os_pdev_set_drvdata(void *pdev,void *pddt);
void os_pdev_set_drvdata(void *pdev,void *pddt)
{
	platform_set_drvdata((struct platform_device *)pdev,pddt);
}

/**************************************************/
void *os_pdev_get_drvdata(void *pdev);
void *os_pdev_get_drvdata(void *pdev)
{
	void *pddt;
	pddt=platform_get_drvdata((struct platform_device *)pdev);
	if(pddt == NULL)
		os_print("Platform fails to get device data\n");
	return(pddt);
}

/* end of os_platform_device.c */
