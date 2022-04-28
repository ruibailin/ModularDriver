/*---------------------------
 * os_device_node.c
 *  Created on: Jul 5, 2017
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
#include <linux/of.h>
#include <linux/device.h>
/**************************************************/
void *os_find_device_node(const char *dev_name);
void *os_find_device_node(const char *dev_name)
{
	struct device_node *d_n;
	d_n=of_find_compatible_node(NULL,NULL,dev_name);
	return(d_n);
}
/**************************************************/
void *os_get_device_node(void *dev);
void *os_get_device_node(void *dev)
{
	struct device_node *d_n;
	d_n=((struct device *)dev)->of_node;
	return(d_n);
}
/**************************************************/
#include <linux/of_address.h>
void *os_get_iomap_device_node(void *dev_n);
void *os_get_iomap_device_node(void *dev_n)
{
	void __iomem *addr;
	addr=of_iomap((struct device_node *)dev_n, 0);
	return(addr);
}
/* end of os_device_node.c */
