/*---------------------------
 * os_device_dev_t.c
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
#include <linux/gfp.h>
#include <linux/slab.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
/**************************************************/
void *os_create_dev_t(unsigned int major,const char *name);
void *os_create_dev_t(unsigned int major,const char *name)
{
	dev_t *dev_no;
	dev_no=kmalloc(sizeof(dev_t),GFP_ATOMIC);
	*dev_no=MKDEV(major,0);
	return(dev_no);
}
/**************************************************/
unsigned os_get_major_dev_t(void *dev_no);
unsigned os_get_major_dev_t(void *dev_no)
{
	dev_t *dev;
	dev=(dev_t *)dev_no;
	return(MAJOR(*dev));
}

/* end of os_device_dev_t.c */
