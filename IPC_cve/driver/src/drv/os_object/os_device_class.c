/*---------------------------
 * os_class.c
 *  Created on: Jul 5, 2017
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

#include <linux/device.h>
/**************************************************/
void *os_create_class(const char *name);
void *os_create_class(const char *name)
{
	struct class *cls;
	cls=class_create(THIS_MODULE,name);
	return(cls);
}
/**************************************************/
void os_destroy_class(void *cls);
void os_destroy_class(void *cls)
{
	class_destroy((struct class *)cls);
}

/* end of os_class.c */
