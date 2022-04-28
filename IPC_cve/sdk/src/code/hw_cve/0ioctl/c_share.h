
/*---------------------------
 * c_share.h
 *  Created on: 2017年8月3日
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

#ifndef SRC_CODE_HW_CVE_0IOCTL_C_SHARE_H_
#define SRC_CODE_HW_CVE_0IOCTL_C_SHARE_H_
#include "../../ive_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <string.h>
#include <asm-generic/ioctl.h>
#define IOCTL_MAGIC_NUM			's'
#define IOCTL_MAX_COM_NUM		24
#define IOCTL_CMD(x)			_IO(IOCTL_MAGIC_NUM,x)

#include "../0file/file_ioctl.h"
#endif 
/* end of c_share.h */
