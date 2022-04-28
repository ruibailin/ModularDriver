
/*---------------------------
 * cve_io_reset.c
 *  Created on: 2017年8月3日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *Reset Address
 *
 *
 *
 *
 *---------------------------
 */

#include "c_share.h"

#include <linux/ioport.h>
#include <linux/platform_device.h>
static  void __iomem *io_reset;

/**************************************************/
void cve_io_set_reset(void *base);
void cve_io_set_reset(void *base)
{
	io_reset=base;
}
/**************************************************/
void *cve_io_get_reset(void);
void *cve_io_get_reset(void)
{
	return(io_reset);
}
/**************************************************/
#include <linux/io.h>
void cve_io_reset_hw(void);
void cve_io_reset_hw(void)
{
    unsigned int val;

    /* reset cve module */
    val = ioread32(io_reset);
    val &= ~(0xc0);   // bit6,7
    iowrite32(val, io_reset);
    //mdelay(5);
    val |=  0xc0;
    iowrite32(val, io_reset);
}
/* end of cve_io_reset.c */
