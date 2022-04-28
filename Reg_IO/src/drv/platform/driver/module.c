
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
/**************************************************/
#include <linux/init.h>
#include <linux/compiler.h>

extern int pfm_drv_init(void);
static int __init drv_module_init(void)
{
    int ret;
    ret=pfm_drv_init();
    return ret;
}
/**************************************************/
extern void pfm_drv_exit(void);
static  void  __exit drv_module_exit(void)
{
	pfm_drv_exit();
}
/**************************************************/
#include <linux/module.h>
module_init(drv_module_init);
module_exit(drv_module_exit);

/**************************************************/
MODULE_LICENSE(MODULE_LICENSE_NAME);
MODULE_AUTHOR(MODULE_AUTHOR_NAME);
MODULE_DESCRIPTION(MODULE_DESCRIP_NAME);
/**************************************************/
/* end of module.c */
