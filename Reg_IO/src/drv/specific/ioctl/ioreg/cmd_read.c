
/*---------------------------
 * cmd_read.c
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

#include "01import.h"
/**************************************************/
#include <linux/uaccess.h>
#include <linux/compiler.h>
#include "./io/00export.h"

/**************************************************/
long ioctl_cmd_func1(struct file *p, unsigned long d);
long ioctl_cmd_func1(struct file *p, unsigned long d)
{
//	os_print("CVE Driver is going to read 32bits data to user space %lx \n",d);
	long ret;
	IO_REG_CMD_T io_cmd;
	ret=copy_from_user((void *)&io_cmd,(void __user *)d,sizeof(IO_REG_CMD_T));
	if(ret)
	{
//		os_print("CVE Driver fail to copy 32bits from user space %lx \n",d);
		return(ret);
	}
	io_cmd.val.reg32=map_read32(io_cmd.phy_add);
    copy_to_user((void __user *)d,(void *)&io_cmd,sizeof(IO_REG_CMD_T));
//	os_print("CVE Driver read 32bits data %d from offset %x\n",io_cmd.val.reg32,io_cmd.phy_add);
	return(ret);
}
/**************************************************/
long ioctl_cmd_func3(struct file *p, unsigned long d);
long ioctl_cmd_func3(struct file *p, unsigned long d)
{
//	os_print("CVE Driver is going to read 16bits data to user space %lx \n",d);
	long ret;
	IO_REG_CMD_T io_cmd;
	ret=copy_from_user((void *)&io_cmd,(void __user *)d,sizeof(IO_REG_CMD_T));
	if(ret)
	{
//		os_print("CVE Driver fail to copy 16bits data from user space %lx \n",d);
		return(ret);
	}

	io_cmd.val.reg16[0]=map_read16(io_cmd.phy_add);
    copy_to_user((void __user *)d,(void *)&io_cmd,sizeof(IO_REG_CMD_T));
//	os_print("CVE Driver read 16bits data %d from offset %x\n",io_cmd.val.reg16[0],io_cmd.phy_add);
	return(ret);
}

/**************************************************/
long ioctl_cmd_func5(struct file *p, unsigned long d);
long ioctl_cmd_func5(struct file *p, unsigned long d)
{
//	os_print("CVE Driver is going to read 16bits data to user space %lx \n",d);
	long ret;
	IO_REG_CMD_T io_cmd;
	ret=copy_from_user((void *)&io_cmd,(void __user *)d,sizeof(IO_REG_CMD_T));
	if(ret)
	{
//		os_print("CVE Driver fail to copy 16bits data from user space %lx \n",d);
		return(ret);
	}

	io_cmd.val.reg8[0]=map_read8(io_cmd.phy_add);
    copy_to_user((void __user *)d,(void *)&io_cmd,sizeof(IO_REG_CMD_T));
//	os_print("CVE Driver read 8bits data %d from offset %x\n",io_cmd.val.reg8[0],io_cmd.phy_add);
	return(ret);
}
/**************************************************/
/* end of cmd_read.c */
