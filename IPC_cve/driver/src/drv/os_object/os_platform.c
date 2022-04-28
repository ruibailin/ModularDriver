/*---------------------------
 * os_platform.c
 *  Created on: Jul 9, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *platform:pfm
 *register:reg
 *unregister:urg
 *alloc:alc
 *
 *
 *---------------------------
 */


#include "c_share.h"

#include <linux/platform_device.h>
/**************************************************/
int os_pfm_reg_device(void *pdev);
int os_pfm_reg_device(void *pdev)
{
	int ret;
	ret=platform_device_register((struct platform_device *)pdev);
	if(ret!=0)
		os_print("Platform fails to register device:name=%s\n",((struct platform_device *)pdev)->name);
	return(ret);
}
/**************************************************/
void os_pfm_urg_device(void *pdev);
void os_pfm_urg_device(void *pdev)
{
	platform_device_unregister((struct platform_device *)pdev);
}

/**************************************************/
void *os_pfm_alc_device(const char *pdev_name,int pdev_id);
void *os_pfm_alc_device(const char *pdev_name,int pdev_id)
{
	struct platform_device * pdev;
	pdev=platform_device_alloc(pdev_name,pdev_id);
	if(pdev == NULL)
		os_print("Platform fails to allocate device:id=%d name=%s !\n",pdev_id,pdev_name);
	return(pdev);
}
/**************************************************/
int os_pfm_add_device(void *pdev);
int os_pfm_add_device(void *pdev)
{
	int ret;
	ret=platform_device_add((struct platform_device *)pdev);
	if(ret!=0)
		os_print("Platform fails to add device:name=%s\n",((struct platform_device *)pdev)->name);
	return(ret);
}
/**************************************************/
void os_pfm_del_device(void *pdev);
void os_pfm_del_device(void *pdev)
{

	platform_device_del((struct platform_device *)pdev);
}

/**************************************************/
int os_pfm_reg_driver(void *pdrv);
int os_pfm_reg_driver(void *pdrv)
{
	int ret;
	ret=platform_driver_register((struct platform_driver *)pdrv);
	if(ret!=0)
		os_print("Platform fails to register driver!\n");
	return(ret);
}
/**************************************************/
void os_pfm_urg_driver(void *pdrv);
void os_pfm_urg_driver(void *pdrv)
{
	platform_driver_unregister((struct platform_driver *)pdrv);
}

/* end of os_platform.c */
