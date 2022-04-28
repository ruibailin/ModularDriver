
/*---------------------------
 * module.c
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
#include <linux/init.h>
#include <linux/compiler.h>
/**************************************************/
extern int pfm_dev_init(void);
static int __init dev_module_init(void)
{
    int ret;
    ret=pfm_dev_init();
    return ret;
}
/**************************************************/
extern void pfm_dev_exit(void);
static  void  __exit dev_module_exit(void)
{
	pfm_dev_exit();
}

/**************************************************/
#include <linux/module.h>
module_init(dev_module_init);
module_exit(dev_module_exit);
/**************************************************/
MODULE_LICENSE(MODULE_LICENSE_NAME);
MODULE_AUTHOR(MODULE_AUTHOR_NAME);
MODULE_DESCRIPTION(MODULE_DESCRIP_NAME);


/**************************************************/
/* end of module.c */
