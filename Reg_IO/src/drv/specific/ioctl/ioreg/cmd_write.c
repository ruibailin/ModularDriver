
/*---------------------------
 * cmd_write.c
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
long ioctl_cmd_func2(struct file *p, unsigned long d);
long ioctl_cmd_func2(struct file *p, unsigned long d)
{
	long ret;
	IO_REG_CMD_T io_cmd;
//	os_print("CVE Driver is going to write 32bits data from user space %lx\n",d);
	ret=copy_from_user((void *)&io_cmd,(void __user *)d,sizeof(IO_REG_CMD_T));
	if(ret)
	{
//		os_print("CVE Driver fail to copy 32bits data from user space %lx\n",d);
		return(ret);
	}
	map_write32(io_cmd.phy_add,io_cmd.val.reg32);
//	os_print("CVE Driver write 32bits data %d to offset %x\n",io_cmd.val.reg32,io_cmd.phy_add);
	return(ret);
}
/**************************************************/
long ioctl_cmd_func4(struct file *p, unsigned long d);
long ioctl_cmd_func4(struct file *p, unsigned long d)
{
	long ret;
	IO_REG_CMD_T io_cmd;
//	os_print("CVE Driver is going to write 16bits data from user space %lx\n",d);
	ret=copy_from_user((void *)&io_cmd,(void __user *)d,sizeof(IO_REG_CMD_T));
	if(ret)
	{
//		os_print("CVE Driver fail to copy 16bits data from user space %lx\n",d);
		return(ret);
	}
	map_write16(io_cmd.phy_add,io_cmd.val.reg16[0]);
//	os_print("CVE Driver write 16bits data %d to offset %x\n",io_cmd.val.reg16[0],io_cmd.phy_add);
	return(ret);
}

/**************************************************/
long ioctl_cmd_func6(struct file *p, unsigned long d);
long ioctl_cmd_func6(struct file *p, unsigned long d)
{
	long ret;
	IO_REG_CMD_T io_cmd;
//	os_print("CVE Driver is going to write 16bits data from user space %lx\n",d);
	ret=copy_from_user((void *)&io_cmd,(void __user *)d,sizeof(IO_REG_CMD_T));
	if(ret)
	{
//		os_print("CVE Driver fail to copy 16bits data from user space %lx\n",d);
		return(ret);
	}
	map_write8(io_cmd.phy_add,io_cmd.val.reg8[0]);
//	os_print("CVE Driver write 8bits data %d to offset %x\n",io_cmd.val.reg8[0],io_cmd.phy_add);
	return(ret);
}
/**************************************************/
/* end of cmd_write.c */
