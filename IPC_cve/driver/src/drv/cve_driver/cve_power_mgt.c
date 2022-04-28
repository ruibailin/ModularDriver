
/*---------------------------
 * cve_power_mgt.c
 *  Created on: 2017年7月29日
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

/**************************************************/
int pfm_drv_pm_func(suspend)(void *dev);
int pfm_drv_pm_func(suspend)(void *dev)
{
	int ret;
	ret=0;
	os_print("%s to run pm suspend!\n",DRV_MODULE_NAME);
	return(ret);
}

/**************************************************/
int pfm_drv_pm_func(resume)(void *dev);
int pfm_drv_pm_func(resume)(void *dev)
{
	int ret;
	ret=0;
	os_print("%s to run pm resume!\n",DRV_MODULE_NAME);
	return(ret);
}

/**************************************************/
int pfm_drv_pm_func(runtime_suspend)(void *dev);
int pfm_drv_pm_func(runtime_suspend)(void *dev)
{
	int ret;
	ret=0;
	os_print("%s to run pm runtime_suspend!\n",DRV_MODULE_NAME);
	return(ret);
}

/**************************************************/
int pfm_drv_pm_func(runtime_resume)(void *dev);
int pfm_drv_pm_func(runtime_resume)(void *dev)
{
	int ret;
	ret=0;
	os_print("%s to run pm runtime_resume!\n",DRV_MODULE_NAME);
	return(ret);
}

/* end of cve_power_mgt.c */
