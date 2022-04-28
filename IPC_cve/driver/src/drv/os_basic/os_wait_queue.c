/*---------------------------
 * os_wait_queue.c
 *  Created on: Jul 5, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#include "c_share.h"
#include <linux/wait.h>
#include <linux/gfp.h>
#include <linux/slab.h>
typedef int (*os_wait_queue_func_t)(void *wait, unsigned mode, int flags, void *key);
/**************************************************/
void *os_ini_wait_queue_head(void);
void *os_ini_wait_queue_head(void)
{
	struct wait_queue_head_t *node;
	node=kmalloc(sizeof(wait_queue_head_t),GFP_ATOMIC);
	init_waitqueue_head(node);
	return(node);
}

/**************************************************/
void *os_ini_wait_queue_node(void);
void *os_ini_wait_queue_node(void)
{
	struct wait_queue_t *node;
	node=kmalloc(sizeof(wait_queue_t),GFP_ATOMIC);
	return(node);
}

/**************************************************/
#include <linux/jiffies.h>
#include <linux/sched.h>
#include <linux/wait.h>
void os_sleep_wait_queue(int mode,void *wq,int con,int time);
void os_sleep_wait_queue(int mode,void *wq,int con,int time)
{
	int ret;
	switch(mode)
	{
	case	0:
		ret=wait_event_interruptible(wq,con);
		break;
	case	1:
		wait_event(wq,con);
		break;
	case	2:
		ret=wait_event_interruptible_timeout(wq,con,msecs_to_jiffies(time));
		break;
	case	3:
		ret=wait_event_timeout(wq,con,msecs_to_jiffies(time));
		break;
	default:
		break;
	}
}

/**************************************************/
void os_wakeup_wait_queue(int mode,void *wq);
void os_wakeup_wait_queue(int mode,void *wq)
{
	switch(mode)
	{
	case	0:
		wake_up_interruptible(wq);
		break;
	case	1:
		wake_up(wq);
		break;
	default:
		break;
	}
}
/* end of os_wait_queue.c */
