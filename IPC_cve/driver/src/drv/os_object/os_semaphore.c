/*---------------------------
 * os_semaphore.c
 *  Created on: Jul 4, 2017
 *      Author: Bailin Rui
 *          ×÷Õß£ºÜÇ°ØÁÖ
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#include "c_share.h"

#include <linux/semaphore.h>
#include <linux/gfp.h>
#include <linux/slab.h>
/**************************************************/
void os_ini_sema(void *sema);
void os_ini_sema(void *sema)
{
	sema=kmalloc(sizeof(struct semaphore),GFP_KERNEL);
	sema_init((struct semaphore *)sema,1);
}

/**************************************************/
int os_get_sema(void *sema);
int os_get_sema(void *sema)
{
	int ret;
	ret=down_interruptible((struct semaphore *)sema);
	return(ret);
}
/**************************************************/
void os_post_sema(void *sema);
void os_post_sema(void *sema)
{
	up((struct semaphore *)sema);
}

/**************************************************/
void os_del_sema(void *sema);
void os_del_sema(void *sema)
{
	kfree((struct semaphore *)sema);
}
/**************************************************/
/* end of os_semaphore.c */
