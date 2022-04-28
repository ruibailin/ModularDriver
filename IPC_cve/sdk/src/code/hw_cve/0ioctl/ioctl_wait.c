
/*---------------------------
 * ioctl_wait.c
 *  Created on: 2017年8月3日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *Refer to cve_file_ioctl_wait.c in driver
 *
 *
 *
 *
 *---------------------------
 */

#include "c_share.h"

#define CVE_WAIT_CMD_DONE		IOCTL_CMD(3)
#define CVE_WAIT_CMD_STOP		IOCTL_CMD(4)
/**************************************************/
void cmd_wait_done(void);			/*hung up current process if CVE is busy*/
void cmd_wait_done(void)
{
	int fd;
	fd=io_get_fd();
    ioctl(fd, CVE_WAIT_CMD_DONE, NULL);
}
/**************************************************/
void cmd_stop_wait(void);			/*for test,wake up all hung process*/
void cmd_stop_wait(void)
{
	int fd;
	fd=io_get_fd();
    ioctl(fd, CVE_WAIT_CMD_STOP, NULL);
}
/* end of ioctl_wait.c */
