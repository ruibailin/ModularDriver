/*---------------------------
 * os_mutex_lock.c
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

#include <linux/mutex.h>
#include <linux/gfp.h>
#include <linux/slab.h>
/**************************************************/
void os_ini_mutex_lock(void *lock);
void os_ini_mutex_lock(void *lock)
{
	lock=kmalloc(sizeof(struct mutex),GFP_KERNEL);
	mutex_init((struct mutex *)lock);
}

/**************************************************/
void os_get_mutex_lock(void *lock);
void os_get_mutex_lock(void *lock)
{
	mutex_lock((struct mutex *)lock);
}
/**************************************************/
void os_free_mutex_lock(void *lock);
void os_free_mutex_lock(void *lock)
{
	mutex_unlock((struct mutex *)lock);
}
/**************************************************/
void os_del_mutex_lock(void *lock);
void os_del_mutex_lock(void *lock)
{
	kfree((struct mutex *)lock);
}

/**************************************************/
/* end of os_mutex_lock.c */
