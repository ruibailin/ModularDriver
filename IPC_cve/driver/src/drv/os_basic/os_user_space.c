/*---------------------------
 * os_user_base.c
 *  Created on: Jul 4, 2017
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
#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include <linux/compiler.h>
/**************************************************/
void os_copy_dword_to_user(int knl32,unsigned long user_var);
void os_copy_dword_to_user(int knl32,unsigned long user_var)
{
	put_user(knl32, (unsigned int __user *)user_var);
}

/**************************************************/
void os_copy_dword_from_user(int knl32,unsigned long user_var);
void os_copy_dword_from_user(int knl32,unsigned long user_var)
{
	get_user(knl32, (unsigned int __user *)user_var);
}
/* end of os_user_base.c */
