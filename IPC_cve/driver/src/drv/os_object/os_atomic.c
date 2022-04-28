/*---------------------------
 * os_atomic.c
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

#include <asm/atomic.h>
#include <linux/gfp.h>
#include <linux/slab.h>
/**************************************************/
void *os_ini_atomic(void);
void *os_ini_atomic(void)
{
	struct atomic_t *atom;
	atom=kmalloc(sizeof(atomic_t),GFP_ATOMIC);
	return(atom);
}
/**************************************************/
void os_inc_atomic(void *atom);
void os_inc_atomic(void *atom)
{
	atomic_inc((atomic_t *)atom);
}
/**************************************************/
void os_dec_atomic(void *atom);
void os_dec_atomic(void *atom)
{
	atomic_dec((atomic_t *)atom);
}
/**************************************************/
void os_read_atomic(void *atom);
void os_read_atomic(void *atom)
{
	atomic_read((atomic_t *)atom);
}
/**************************************************/
void os_add_atomic(int i,void *atom);
void os_add_atomic(int i,void *atom)
{
	atomic_add(i,(atomic_t *)atom);
}
/**************************************************/
void os_sub_atomic(int i,void *atom);
void os_sub_atomic(int i,void *atom)
{
	atomic_sub(i,(atomic_t *)atom);
}

/**************************************************/
void os_del_atomic(void *atom);
void os_del_atomic(void *atom)
{
	kfree((atomic_t *)atom);
}
/* end of os_atomic.c */
