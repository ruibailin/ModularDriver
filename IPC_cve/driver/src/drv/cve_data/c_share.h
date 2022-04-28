
/*---------------------------
 * c_share.h
 *  Created on: 2017年7月28日
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

#ifndef SRC_DRV_CVE_DATA_C_SHARE_H_
#define SRC_DRV_CVE_DATA_C_SHARE_H_

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
