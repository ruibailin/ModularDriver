/*---------------------------
 * os_chrdev_region.c
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
#include <linux/fs.h>
#include <linux/device.h>
/**************************************************/
int os_alloc_chrdev_region(void *dev_no,int minor,const char *name);
int os_alloc_chrdev_region(void *dev_no,int minor,const char *name)
{
	return(alloc_chrdev_region((dev_t *)dev_no,minor,1,name));
}
/**************************************************/
int os_register_chrdev_region(void *dev_no,const char *name);
int os_register_chrdev_region(void *dev_no,const char *name)
{
	return(register_chrdev_region(*(dev_t *)dev_no,1,name));
}
/**************************************************/
void os_unregister_chrdev_region(void *dev_no);
void os_unregister_chrdev_region(void *dev_no)
{
	unregister_chrdev_region(*(dev_t *)dev_no,1);
}

/* end of os_chrdev_region.c */
