/*---------------------------
 * os_misc.c
 *  Created on: Jul 5, 2017
 *      Author: Bailin Rui
 *          ×÷Õß£ºÜÇ°ØÁÖ
 *---------------------------
 *printk
 *kmalloc
 *kfree
 *
 *
 *
 *---------------------------
 */


#include "c_share.h"

#include <linux/gfp.h>
#include <linux/slab.h>
/**************************************************/
void *os_malloc(int size);
void *os_malloc(int size)
{
	void *ptr;
	ptr=kmalloc(size,GFP_ATOMIC);
	return(ptr);
}
/**************************************************/
void *os_zalloc(int size);
void *os_zalloc(int size)
{
	void *ptr;
	ptr=kzalloc(size,GFP_ATOMIC);
	return(ptr);
}
/**************************************************/
void os_free(void *buf);
void os_free(void *buf)
{
	kfree(buf);
}


/* end of os_misc.c */
