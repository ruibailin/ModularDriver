/*---------------------------
 * os_spin_lock.c
 *  Created on: Jul 4, 2017
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

#include <linux/spinlock.h>
#include <linux/spinlock_types.h>
#include <linux/gfp.h>
#include <linux/slab.h>
/**************************************************/
void *os_ini_spin_lock(void);
void *os_ini_spin_lock(void)
{
	struct spinlock_t *lock;
	lock=kmalloc(sizeof(spinlock_t),GFP_ATOMIC);
	spin_lock_init((spinlock_t *)lock);
	return(lock);
}

/**************************************************/
void os_get_spin_lock(void *lock,long flags);
void os_get_spin_lock(void *lock,long flags)
{
	 spin_lock_irqsave((spinlock_t *)lock, flags);
}
/**************************************************/
void os_free_spin_lock(void *lock,long flags);
void os_free_spin_lock(void *lock,long flags)
{
	spin_unlock_irqrestore((spinlock_t *)lock, flags);
}

/**************************************************/
void os_del_spin_lock(void *lock);
void os_del_spin_lock(void *lock)
{
	kfree((spinlock_t *)lock);
}
/* end of os_spin_lock.c */
