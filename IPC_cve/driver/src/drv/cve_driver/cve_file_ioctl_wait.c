
/*---------------------------
 * cve_file_ioctl_wait.c
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

#define CVE_WAIT_CMD_DONE		IOCTL_CMD(3)
#define CVE_WAIT_CMD_STOP		IOCTL_CMD(4)		/*For test*/
/**************************************************/
long pfm_file_ioctl_func(3)(void *p,unsigned long d);
long pfm_file_ioctl_func(3)(void *p,unsigned long d)
{
	long ret;
	int state;
	state=cve_top_get_irq_done();
	os_print("CVE_check irq state is %x \n", state);
	cve_wq_hung_proc(state);
	ret=0;
	return(ret);
}
/**************************************************/
long pfm_file_ioctl_func(4)(void *p,unsigned long d);
long pfm_file_ioctl_func(4)(void *p,unsigned long d)
{
	long ret;
	cve_wq_wake_proc(1);
	ret=0;
	return(ret);
}

/* end of cve_file_ioctl_wait.c */
