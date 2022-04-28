
/*---------------------------
 * ioctl_io.c
 *  Created on: 2017年8月3日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *Please refer to cve_file_ioctl_io.c in driver
 *
 *
 *
 *
 *---------------------------
 */

#include "c_share.h"

/**************************************************/
#define CVE_IO_CMD_READ			IOCTL_CMD(1)
#define CVE_IO_CMD_WRITE		IOCTL_CMD(2)
/**************************************************/
void cmd_write_32(int off,int val);
void cmd_write_32(int off,int val)
{
	int fd;
	typedef struct{
		int offset;
		int value;
	}IO_CMD_T;
	IO_CMD_T io_cmd;

	io_cmd.offset=off;
	io_cmd.value=val;
	fd=io_get_fd();
    ioctl(fd, CVE_IO_CMD_WRITE, &io_cmd);
}
/**************************************************/
int cmd_read_32(int off);
int cmd_read_32(int off)
{
	int fd;
	typedef struct{
		int offset;
		int value;
	}IO_CMD_T;
	IO_CMD_T io_cmd;

	io_cmd.offset=off;
	fd=io_get_fd();
    ioctl(fd, CVE_IO_CMD_READ, &io_cmd);
    return(io_cmd.value);
}
/* end of ioctl_io.c */
