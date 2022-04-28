/*---------------------------
 * c_share.h
 *  Created on: Jul 8, 2017
 *      Author: Bailin Rui
 *          ×÷Õß£ºÜÇ°ØÁÖ
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#ifndef DRV_PFM_DRIVER_C_SHARE_H_
#define DRV_PFM_DRIVER_C_SHARE_H_

#include "../cve_drv_basic_def.h"

#ifndef	IVE_UNIT_TEST
#include <linux/init.h>
#include <linux/module.h>
#define  os_print(fmt,...)  printk(KERN_ERR fmt,##__VA_ARGS__)
#else
#include <stdio.h>
#include <stdlib.h>
#define  os_print(fmt,...)  printf(fmt,##__VA_ARGS__)
#endif

#endif 
/* end of c_share.h */
