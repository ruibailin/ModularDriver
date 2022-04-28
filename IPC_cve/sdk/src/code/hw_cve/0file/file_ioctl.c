
/*---------------------------
 * file_ioctl.c
 *  Created on: 2017年8月3日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *Please refer to cve_file_ops.c in driver
 *
 *
 *
 *
 *---------------------------
 */

#include "c_share.h"

static  int   cve_fd;
/**************************************************/
int io_get_fd(void);
int io_get_fd(void)
{
	return(cve_fd);
}
/**************************************************/
#include <fcntl.h>
#include <errno.h>
#define	DEV_MODULE_NAME			"/dev/zx_cve"
int io_open_file(void);
int io_open_file(void)
{
	cve_fd=0;
	cve_fd = open(DEV_MODULE_NAME, O_RDONLY, 0666);
	if (cve_fd == -1)
	{
	printf("ERROR! Failed to open %s\n", DEV_MODULE_NAME);
	printf("ERROR is %s\n", strerror(errno));
	}
	return(cve_fd);
}
/**************************************************/
void io_close_file(void);
void io_close_file(void)
{
	if(cve_fd >0 )
		close(cve_fd);
	cve_fd=0;
}



/* end of file_ioctl.c */
