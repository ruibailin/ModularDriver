
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

#ifndef OPS_IOCTL_00EXPORT_H_
#define OPS_IOCTL_00EXPORT_H_


/**************************************************/
#define extern_cmd_func(x)		extern	long ioctl_cmd_func(x)(struct file *p,unsigned long d)
extern_cmd_func(1);
extern_cmd_func(2);
extern_cmd_func(3);
extern_cmd_func(4);
extern_cmd_func(5);
extern_cmd_func(6);
extern_cmd_func(7);
extern_cmd_func(8);
extern_cmd_func(9);
extern_cmd_func(10);
extern_cmd_func(11);
extern_cmd_func(12);
extern_cmd_func(13);
extern_cmd_func(14);
extern_cmd_func(15);
extern_cmd_func(16);
extern_cmd_func(17);
extern_cmd_func(18);
extern_cmd_func(19);
extern_cmd_func(20);
extern_cmd_func(21);
extern_cmd_func(22);
extern_cmd_func(23);
extern_cmd_func(24);

/**************************************************/
#endif 
/* end of 00export.h */
