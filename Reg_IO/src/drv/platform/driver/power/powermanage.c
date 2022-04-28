
/*---------------------------
 * powermanage.c
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
#include <linux/device.h>
/**************************************************/
int drv_pm_suspend(struct device *dev);
int drv_pm_suspend(struct device *dev)
{
	return 0;
}
/**************************************************/
int drv_pm_resume(struct device *dev);
int drv_pm_resume(struct device *dev)
{
	return 0;
}
/**************************************************/
int drv_pm_runtime_suspend(struct device *dev);
int drv_pm_runtime_suspend(struct device *dev)
{
	return 0;
}
/**************************************************/
int drv_pm_runtime_resume(struct device *dev);
int drv_pm_runtime_resume(struct device *dev)
{
	return 0;
}

/**************************************************/
/* end of powermanage.c */
