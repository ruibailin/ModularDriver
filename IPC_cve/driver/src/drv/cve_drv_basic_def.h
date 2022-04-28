/*---------------------------
 * cve_drv_basic.h
 *  Created on: Jul 8, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#ifndef DRV_CVE_DRV_BASIC_DEF_H_
#define DRV_CVE_DRV_BASIC_DEF_H_

#define	DEV_MODULE_NAME			"zx_cve"
#define dev_module_func(x)		zx_ipc_cve_dev_##x
#define	DEV_START_MEM			0x00524000

#define	DRV_MODULE_NAME			DEV_MODULE_NAME
#define	DRV_COMPATIBLE_NAME		"zte, zx296805-cve"
#define	DRV_DEVICE_MINOR		0x00

#define drv_module_func(x)		zx_ipc_cve_drv_##x
#define	pfm_drv_func(x)			zx_ipc_cve_##x
#define	pfm_drv_file_func(x)	zx_ipc_cve_file_##x
#define	pfm_drv_int_func(x)		zx_ipc_cve_int_##x
#define	pfm_drv_pm_func(x)		zx_ipc_cve_pm_##x
#define pfm_drv_clk_func(x)		zx_ipc_cve_##x##_clk

#define IOCTL_MAGIC_NUM			's'
#define IOCTL_MAX_COM_NUM		24
#include <asm-generic/ioctl.h>
#define IOCTL_CMD(x)			_IO(IOCTL_MAGIC_NUM,x)
#define pfm_file_ioctl_func(x)	zx_ipc_cve_ioctl_cmd##x

#define CVE_INT_DONE			51
#define CVE_INT_ERR				52


#endif 
/* end of cve_drv_basic.h */
