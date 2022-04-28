
/*---------------------------
 * 00export.h
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

#ifndef FILE_OPS_00EXPORT_H_
#define FILE_OPS_00EXPORT_H_

/**************************************************/
extern int file_ops_open(struct inode *, struct file *);
extern int file_ops_release(struct inode *, struct file *);
extern long file_ops_ioctl(struct file *, unsigned int, unsigned long);

/**************************************************/
#endif 
/* end of 00export.h */
