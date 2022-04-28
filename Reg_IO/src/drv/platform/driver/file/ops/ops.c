
/*---------------------------
 * ops.c
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
#include <linux/cdev.h>
/**************************************************/
int file_ops_open(struct inode *in, struct file *p);
int file_ops_open(struct inode *in, struct file *p)
{
	return 0;
}
/**************************************************/
int file_ops_release(struct inode *in, struct file *p);
int file_ops_release(struct inode *in, struct file *p)
{
	return 0;
}
/**************************************************/
#define call_cmd_func(x)		ioctl_cmd_func(x)(pfile,data)
#include <asm-generic/ioctl.h>
#include <asm-generic/errno-base.h>
#include "./ioctl/00export.h"
long file_ops_ioctl(struct file *pfile, unsigned int cmd, unsigned long data);
long file_ops_ioctl(struct file *pfile, unsigned int cmd, unsigned long data)
{
	long ret;
	ret=0;
    if (_IOC_TYPE(cmd) != IOCTL_MAGIC_NUM)
        return -EINVAL;
    if (_IOC_NR(cmd) > IOCTL_MAX_COM_NUM)
        return -EINVAL;
//    os_print("\nCommand number is %d\n",_IOC_NR(cmd));
    switch(cmd){
	case	IOCTL_CMD(1):
		ret=call_cmd_func(1);
		break;
	case	IOCTL_CMD(2):
		ret=call_cmd_func(2);
		break;
	case	IOCTL_CMD(3):
		ret=call_cmd_func(3);
		break;
	case	IOCTL_CMD(4):
		ret=call_cmd_func(4);
		break;
	case	IOCTL_CMD(5):
		ret=call_cmd_func(5);
		break;
	case	IOCTL_CMD(6):
		ret=call_cmd_func(6);
		break;
	case	IOCTL_CMD(7):
		ret=call_cmd_func(7);
		break;
	case	IOCTL_CMD(8):
		ret=call_cmd_func(8);
		break;
	case	IOCTL_CMD(9):
		ret=call_cmd_func(9);
		break;
	case	IOCTL_CMD(10):
		ret=call_cmd_func(10);
		break;
	case	IOCTL_CMD(11):
		ret=call_cmd_func(11);
		break;
	case	IOCTL_CMD(12):
		ret=call_cmd_func(12);
		break;
	case	IOCTL_CMD(13):
		ret=call_cmd_func(13);
		break;
	case	IOCTL_CMD(14):
		ret=call_cmd_func(14);
		break;
	case	IOCTL_CMD(15):
		ret=call_cmd_func(15);
		break;
	case	IOCTL_CMD(16):
		ret=call_cmd_func(16);
		break;
	case	IOCTL_CMD(17):
		ret=call_cmd_func(17);
		break;
	case	IOCTL_CMD(18):
		ret=call_cmd_func(18);
		break;
	case	IOCTL_CMD(19):
		ret=call_cmd_func(19);
		break;
	case	IOCTL_CMD(20):
		ret=call_cmd_func(20);
		break;
	case	IOCTL_CMD(21):
		ret=call_cmd_func(21);
		break;
	case	IOCTL_CMD(22):
		ret=call_cmd_func(22);
		break;
	case	IOCTL_CMD(23):
		ret=call_cmd_func(23);
		break;
	case	IOCTL_CMD(24):
		ret=call_cmd_func(24);
		break;
	default:
    	break;
    }
    return(ret);
}
/**************************************************/
/* end of ops.c */
