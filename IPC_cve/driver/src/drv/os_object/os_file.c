/*---------------------------
 * os_chrdev_file.c
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

#include <linux/fs.h>
/**************************************************/
void os_file_set_data(void *flip,void *dev);
void os_file_set_data(void *flip,void *dev)
{
	((struct file *)flip)->private_data=dev;
}
/**************************************************/
void *os_file_get_data(void *flip);
void *os_file_get_data(void *flip)
{
	return(((struct file *)flip)->private_data);
}
/**************************************************/
void *os_file_get_inode(void *flip);
void *os_file_get_inode(void *flip)
{
	return(((struct file *)flip)->f_inode);
}

/* end of os_chrdev_file.c */
