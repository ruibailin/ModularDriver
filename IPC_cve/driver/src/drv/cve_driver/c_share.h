/*---------------------------
 * c_share.h
 *  Created on: Jul 9, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#ifndef DRV_CVE_DRIVER_C_SHARE_H_
#define DRV_CVE_DRIVER_C_SHARE_H_

#include "../cve_drv_basic_def.h"
#include "../pfm_driver/pfm_driver.h"

#ifndef	IVE_UNIT_TEST

#include <linux/init.h>
#include <linux/module.h>

#define  os_print(fmt,...)  printk(KERN_ERR fmt,##__VA_ARGS__)
#else
#include <stdio.h>
#include <stdlib.h>
#define  os_print(fmt,...)  printf(fmt,##__VA_ARGS__)
#endif

#include "../cve_data/cve_data.h"

#define TEST_WITHOUT_CVE_HW		0		/*should be 0 when run CVE hardware in 6805 board*/

#endif 
/* end of c_share.h */
