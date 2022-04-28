
/*---------------------------
 * cve_file_ioctl_io.c
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

#include "c_share.h"

#define CVE_IO_CMD_READ			IOCTL_CMD(1)
#define CVE_IO_CMD_WRITE		IOCTL_CMD(2)

#include "../cve_data/cve_io_base.h"

/**************************************************/
#include <linux/uaccess.h>
#include <linux/compiler.h>
long pfm_file_ioctl_func(1)(void *p,unsigned long d);
long pfm_file_ioctl_func(1)(void *p,unsigned long d)
{
	typedef struct{
		int	offset;
		int val;
	}IO_CMD_T;
//	os_print("CVE Driver is going to read data to user space %lx \n",d);
	long ret;
	IO_CMD_T io_cmd;
	ret=copy_from_user((void *)&io_cmd,(void __user *)d,sizeof(IO_CMD_T));
	if(ret)
	{
		os_print("CVE Driver fail to copy data from user space %lx \n",d);
		return(ret);
	}
//	os_print("CVE Driver IO_CMD is val: %d,offset: %x\n",io_cmd.val,io_cmd.offset);
	io_cmd.val=cve_io_read_dword(io_cmd.offset);
    copy_to_user((void __user *)d,(void *)&io_cmd,sizeof(IO_CMD_T));
//	os_print("CVE Driver read data %d from offset %x\n",io_cmd.val,io_cmd.offset);
	return(ret);
}

/**************************************************/
long pfm_file_ioctl_func(2)(void *p,unsigned long d);
long pfm_file_ioctl_func(2)(void *p,unsigned long d)
{
	typedef struct{
		int	offset;
		int val;
	}IO_CMD_T;
	os_print("CVE Driver is going to write data from user space %lx\n",d);
	long ret;
	IO_CMD_T io_cmd;
	ret=copy_from_user((void *)&io_cmd,(void __user *)d,sizeof(IO_CMD_T));
	if(ret)
	{
		os_print("CVE Driver fail to copy data from user space %lx\n",d);
		return(ret);
	}
//	os_print("CVE Driver IO_CMD is val: %d,offset: %x\n",io_cmd.val,io_cmd.offset);
	cve_io_write_dword(io_cmd.offset,io_cmd.val);
//	os_print("CVE Driver write data %d to offset %x",io_cmd.val,io_cmd.offset);
	return(ret);
}


/* end of cve_file_ioctl_io.c */
