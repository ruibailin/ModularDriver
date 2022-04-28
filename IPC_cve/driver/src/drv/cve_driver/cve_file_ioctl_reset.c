
/*---------------------------
 * cve_file_ioctl_reset.c
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

#include "c_share.h"

#define CVE_RESET_CMD_ASIC		IOCTL_CMD(5)

/**************************************************/
long pfm_file_ioctl_func(5)(void *p,unsigned long d);
long pfm_file_ioctl_func(5)(void *p,unsigned long d)
{
	long ret;
	cve_io_reset_hw();
	os_print("CVE_reset hardware ASIC \n");
	ret=0;
	return(ret);
}
/* end of cve_file_ioctl_reset.c */
