
/*---------------------------
 * 01import.h
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

#ifndef DRV_PLATFORM_01IMPORT_H_
#define DRV_PLATFORM_01IMPORT_H_

#include <linux/platform_device.h>
#include <asm-generic/ioctl.h>
#include "../01import.h"
/**************************************************/
#define	DEV_MODULE_NAME		PFMDRV_MODULE_NAME
#define	DRV_MODULE_NAME		DEV_MODULE_NAME
#define	DRV_COMPATIBLE_NAME	DRV_MODULE_NAME

#define	DRV_DEVICE_MINOR		0x00

#define MODULE_LICENSE_NAME		"GPL"
#define MODULE_AUTHOR_NAME		"Steve Rui"
#define MODULE_DESCRIP_NAME		"Driver for read and write register!"
/**************************************************/
#endif 
/* end of 01import.h */
