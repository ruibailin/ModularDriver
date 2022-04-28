
/*---------------------------
 * file.c
 *  Created on: Apr 16, 2019
 *      Author: Steve Rui
 *---------------------------
 *
 *
 *
 *
 *
 *---------------------------
 */

#include "01import.h"
/**************************************************/
#include <linux/fs.h>
#include "./ops/00export.h"
static struct file_operations drv_file_ops =
{
    .owner          = THIS_MODULE,
    .open           = file_ops_open,
    .release        = file_ops_release,
    .unlocked_ioctl = file_ops_ioctl,
    .compat_ioctl   = NULL,
    .fasync         = NULL
};

/**************************************************/
#include <linux/cdev.h>
void drv_set_file_ops(void *cdev);
void drv_set_file_ops(void *cdev)
{
	((struct cdev *)cdev)->ops=&drv_file_ops;
}
/**************************************************/
void *drv_get_file_ops(void);
void *drv_get_file_ops(void)
{
	return(&drv_file_ops);
}


/**************************************************/
/* end of file.c */
