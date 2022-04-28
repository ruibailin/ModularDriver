/*---------------------------
 * os_device_inode.c
 *  Created on: Jul 9, 2017
 *      Author: Bailin Rui
 *          ×÷Õß£ºÜÇ°ØÁÖ
 *---------------------------
 *inode:ind
 *
 *
 *
 *---------------------------
 */


#include "c_share.h"

/**************************************************/
#include <linux/fs.h>
#include <linux/cdev.h>
void *os_ind_get_cdev(void *pinode);
void *os_ind_get_cdev(void *pinode)
{
	struct cdev *pcdev;
	pcdev=((struct inode *)pinode)->i_cdev;
	return(pcdev);
}
/* end of os_device_inode.c */
