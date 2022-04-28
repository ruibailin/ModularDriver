/*---------------------------
 * file_ioctl.c
 *  Created on: Jul 9, 2017
 *      Author: Bailin Rui
 *          ×÷Õß£ºÜÇ°ØÁÖ
 *---------------------------
 *Universal driver's file ioctl function
 *Don't change it except you need more ioctl commands.
 *
 *
 *
 *---------------------------
 */


#include "c_share.h"

/**************************************************/
#include <asm-generic/ioctl.h>
#include <asm-generic/errno-base.h>
#define extern_cmd_func(x)		extern	long pfm_file_ioctl_func(x)(void *p,unsigned long d)
extern_cmd_func(1);
extern_cmd_func(2);
extern_cmd_func(3);
extern_cmd_func(4);
extern_cmd_func(5);
extern_cmd_func(6);
extern_cmd_func(7);
extern_cmd_func(8);
extern_cmd_func(9);
extern_cmd_func(10);
extern_cmd_func(11);
extern_cmd_func(12);
extern_cmd_func(13);
extern_cmd_func(14);
extern_cmd_func(15);
extern_cmd_func(16);
extern_cmd_func(17);
extern_cmd_func(18);
extern_cmd_func(19);
extern_cmd_func(20);
extern_cmd_func(21);
extern_cmd_func(22);
extern_cmd_func(23);
extern_cmd_func(24);

#define call_cmd_func(x)		pfm_file_ioctl_func(x)(pfile,data)
/**************************************************/
long pfm_drv_file_func(ioctl)(void *pfile,unsigned int cmd,unsigned long data);
long pfm_drv_file_func(ioctl)(void *pfile,unsigned int cmd,unsigned long data)
{
	long ret;
    if (_IOC_TYPE(cmd) != IOCTL_MAGIC_NUM)
        return -EINVAL;
    if (_IOC_NR(cmd) > IOCTL_MAX_COM_NUM)
        return -EINVAL;
//    os_print("Command number is %d\n",_IOC_NR(cmd));
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

#undef extern_cmd_func
#undef call_cmd_func
#undef deal_case_cmd

/* end of file_ioctl.c */
