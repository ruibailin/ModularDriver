
/*---------------------------
 * ioctl_reset.c
 *  Created on: 2017年8月3日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *Refer to cve_file_ioctl_reset.c
 *To reset CVE ASIC hardware.
 *
 *
 *
 *
 *---------------------------
 */

#include "c_share.h"
/**************************************************/
#define CVE_RESET_CMD_ASIC		IOCTL_CMD(5)
void cmd_reset_asic(void);
void cmd_reset_asic(void)
{
	int fd;
	fd=io_get_fd();
    ioctl(fd, CVE_RESET_CMD_ASIC, NULL);
}

/* end of ioctl_reset.c */
