
/*---------------------------
 * cve_wait_queue.c
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

#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <uapi/linux/wait.h>

static wait_queue_head_t cve_wq;
static int cve_con;
/**************************************************/
void cve_wq_init_head(void);
void cve_wq_init_head(void)
{
	init_waitqueue_head(&cve_wq);
}

/**************************************************/
void cve_wq_hung_proc(int con);
void cve_wq_hung_proc(int con)
{
	int ret;
	cve_con=con;
	ret=wait_event_interruptible(cve_wq,cve_con);
	if(ret!=0)
		os_print("CVE wait interrupt\n");
}

/**************************************************/
void cve_wq_wake_proc(int con);
void cve_wq_wake_proc(int con)
{
	cve_con=con;
	wake_up_all(&cve_wq);
}
/* end of cve_wait_queue.c */
