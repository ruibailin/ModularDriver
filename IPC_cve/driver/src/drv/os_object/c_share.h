/*---------------------------
 * c_share.h
 *  Created on: Jul 4, 2017
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *把驱动所需要的linux资源进行封装，包括spin-lock,atomic,
 *device,file,等
 *
 *
 *---------------------------
 */


#ifndef DRV_OS_OBJECT_C_SHARE_H_
#define DRV_OS_OBJECT_C_SHARE_H_

#ifndef	IVE_UNIT_TEST
#include <linux/kern_levels.h>
#include <linux/printk.h>
#define  os_print(fmt,...)  printk(KERN_ERR fmt,##__VA_ARGS__)
#else
#include <stdio.h>
#include <stdlib.h>
#define  os_print(fmt,...)  printf(fmt,##__VA_ARGS__)
#endif

#endif 
/* end of c_share.h */
