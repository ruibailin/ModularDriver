/*---------------------------
 * file_ops.c
 *  Created on: Jul 8, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Universal driver's file operations
 *Don't change it except you want to add member functions
 *
 *
 *
 *---------------------------
 */

#include "c_share.h"
/**************************************************/
extern int pfm_drv_file_func(open)(void *pinode,void *pfile);
extern int pfm_drv_file_func(release)(void *pinode,void *pfile);
extern long pfm_drv_file_func(ioctl)(void *pfile,unsigned int cmd,unsigned long data);
#include <linux/fs.h>
static struct file_operations pfm_drv_file_ops =
{
    .owner          = THIS_MODULE,
    .open           = pfm_drv_file_func(open),
    .release        = pfm_drv_file_func(release),
    .unlocked_ioctl = pfm_drv_file_func(ioctl),
    .compat_ioctl   = NULL,
    .fasync         = NULL
};

/**************************************************/
#include <linux/cdev.h>
void pfm_cdev_set_file_ops(void *cdev);
void pfm_cdev_set_file_ops(void *cdev)
{
	((struct cdev *)cdev)->ops=&pfm_drv_file_ops;
}
/**************************************************/
void *pfm_cdev_get_file_ops(void);
void *pfm_cdev_get_file_ops(void)
{
	return(&pfm_drv_file_ops);
}
/* end of file_ops.c */
