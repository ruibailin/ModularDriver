/*---------------------------
 * os_cdev.c
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
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
/**************************************************/
void *os_create_chrdev_cdev(void);
void *os_create_chrdev_cdev(void)
{
	struct cdev *p;
	p=cdev_alloc();
	return(p);
}
/**************************************************/
/*if you already have a cdev, use this fun to initialize it.*/
void os_init_chrdev_cdev(void *dev,void *fops);
void os_init_chrdev_cdev(void *dev,void *fops)
{
	cdev_init((struct cdev *)dev, (const struct file_operations *)fops);
}
/**************************************************/
void os_distroy_chrdev_cdev(void *cd);
void os_distroy_chrdev_cdev(void *cd)
{
	struct cdev *p;
	p=(struct cedv *)cd;
	cdev_del(p);
}
/**************************************************/
void os_add_chrdev_cdev(void *cd,void *num);
void os_add_chrdev_cdev(void *cd,void *num)
{
	struct cdev *p;
	dev_t d;
	p=(struct cedv *)cd;
	d=*((dev_t *)num);
	cdev_add(p,d,1);
}
/**************************************************/
void *os_get_dev_t_cdev(void *cd);
void *os_get_dev_t_cdev(void *cd)
{
	struct cdev *p;
	p=(struct cedv *)cd;
	return(&p->dev);
}

/* end of os_cdev.c */
