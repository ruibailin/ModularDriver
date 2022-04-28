/*---------------------------
 * os_device.c
 *  Created on: Jul 8, 2017
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

#include <linux/device.h>
/**************************************************/
void *os_dev_get_drvdata(void *dev);
void *os_dev_get_drvdata(void *dev)
{
    return dev_get_drvdata((struct device *)dev);
}

/**************************************************/
void os_dev_set_drvdata(void *dev,void *data);
void os_dev_set_drvdata(void *dev,void *data)
{
    dev_set_drvdata((struct device *)dev,data);
}

/* end of os_device.c */
