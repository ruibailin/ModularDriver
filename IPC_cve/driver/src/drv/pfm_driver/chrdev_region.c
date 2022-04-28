/*---------------------------
 * chrdev_region.c
 *  Created on: Jul 8, 2017
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

/**************************************************/

#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/gfp.h>
#include <linux/slab.h>
void *pfm_drv_alloc_dev_t(int major);
void *pfm_drv_alloc_dev_t(int major)
{
	int ret;
	dev_t *dev_no;

	dev_no=kzalloc(sizeof(dev_t),GFP_ATOMIC);
	if(dev_no==NULL)
		return(dev_no);

	if(major)
	{
		*dev_no=MKDEV(major, DRV_DEVICE_MINOR);
        ret = register_chrdev_region(*dev_no, 1, DRV_MODULE_NAME);
	}
	else
        ret = alloc_chrdev_region(dev_no, DRV_DEVICE_MINOR, 1, DRV_MODULE_NAME);
	if(ret != 0)
	{
		kfree(dev_no);
		dev_no=NULL;
	}
	return(dev_no);
}

/* end of chrdev_region.c */
