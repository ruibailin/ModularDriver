
/*---------------------------
 * power_mgt.c
 *  Created on: 2017年7月26日
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
#include <linux/device.h>
#include <linux/pm.h>
/**************************************************/
extern int pfm_drv_clk_func(shut)(void);
extern int pfm_drv_pm_func(suspend)(void *dev);
int pfm_drv_pm_suspend(struct device *dev);
int pfm_drv_pm_suspend(struct device *dev)
{
	int ret;
	pfm_drv_pm_func(suspend)(dev);
	ret=pfm_drv_clk_func(shut)();
	return(ret);
}
/**************************************************/
extern int pfm_drv_pm_func(resume)(void *dev);
extern int pfm_drv_clk_func(open)(void);
int pfm_drv_pm_resume(struct device *dev);
int pfm_drv_pm_resume(struct device *dev)
{
	int ret;
	ret=pfm_drv_clk_func(open)();
	pfm_drv_pm_func(resume)(dev);
	return(ret);
}
/**************************************************/
extern int pfm_drv_pm_func(runtime_suspend)(void *dev);
int pfm_drv_pm_runtime_suspend(struct device *dev);
int pfm_drv_pm_runtime_suspend(struct device *dev)
{
	int ret;
	pfm_drv_pm_func(runtime_suspend)(dev);
	ret=pfm_drv_clk_func(shut)();
	return(ret);
}
/**************************************************/
extern int pfm_drv_pm_func(runtime_resume)(void *dev);
int pfm_drv_pm_runtime_resume(struct device *dev);
int pfm_drv_pm_runtime_resume(struct device *dev)
{
	int ret;
	ret=pfm_drv_clk_func(open)();
	pfm_drv_pm_func(runtime_resume)(dev);
	return(ret);
}

/* end of power_mgt.c */
