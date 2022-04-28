
/*---------------------------
 * 00export.h
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

#ifndef DRIVER_POWER_00EXPORT_H_
#define DRIVER_POWER_00EXPORT_H_

/**************************************************/
extern int drv_pm_suspend(struct device *dev);
extern int drv_pm_resume(struct device *dev);
extern int drv_pm_runtime_suspend(struct device *dev);
extern int drv_pm_runtime_resume(struct device *dev);

/**************************************************/
#endif 
/* end of 00export.h */
