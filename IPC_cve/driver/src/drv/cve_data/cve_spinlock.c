
/*---------------------------
 * cve_spinlock.c
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

#include <linux/spinlock.h>
#include <linux/spinlock_types.h>
static spinlock_t int_lock;

/**************************************************/
void cve_spl_init_lock(void);
void cve_spl_init_lock(void)
{
	spin_lock_init(&int_lock);
}

/**************************************************/
void cve_spl_lock_lock(long flags);
void cve_spl_lock_lock(long flags)
{
	 spin_lock_irqsave(&int_lock, flags);
}
/**************************************************/
void cve_spl_unlock_lock(long flags);
void cve_spl_unlock_lock(long flags)
{
	spin_unlock_irqrestore(&int_lock, flags);
}
/* end of cve_spinlock.c */
