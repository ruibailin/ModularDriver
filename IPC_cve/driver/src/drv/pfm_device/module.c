/*---------------------------
 * module.c
 *  Created on: Jul 10, 2017
 *      Author: Bailin Rui
 *          ×÷Õß£ºÜÇ°ØÁÖ
 *---------------------------
 *Universal device module
 *Don't change it *
 *
 *
 *
 *---------------------------
 */


#include "c_share.h"
/**************************************************/
extern int dev_module_func(init)(void);
#include <linux/init.h>
#include <linux/compiler.h>

static int __init dev_module_init(void)
{
    int ret;
    ret=dev_module_func(init)();
    return ret;
}

/**************************************************/
extern void dev_module_func(exit)(void);
static  void  __exit dev_module_exit(void)
{
	dev_module_func(exit)();
}

/**************************************************/
#include <linux/module.h>
module_init(dev_module_init);
module_exit(dev_module_exit);
/**************************************************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZXIC Multimedia BU");
MODULE_DESCRIPTION("Driver Module for ZX_IPC_CVE");
/**************************************************/

/* end of module.c */
