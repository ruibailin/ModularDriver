
/*---------------------------
 * map_read.c
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
#include <asm/io.h>
/**************************************************/
int	map_read32(int phy_addr);
int	map_read32(int phy_addr)
{
	int	base;
	int offset;
	int ret;
	volatile void *virt;
	base=phy_addr&SEG_MASK;
	offset=phy_addr&OFF_MASK;
	os_print(" phy add is %8u;", phy_addr);
	virt = ioremap(base,offset+4);
	virt += offset;
	os_print(" vir add is %8u\n", virt);

//	ret=ioread32(virt);
	ret=*((int *)virt);
	return(ret);
}
/**************************************************/
short	map_read16(int phy_addr);
short	map_read16(int phy_addr)
{
	int	base;
	int offset;
	short ret;
	volatile void *virt;
	base=phy_addr&SEG_MASK;
	offset=phy_addr&OFF_MASK;
	os_print(" phy add is %8u;", phy_addr);
	virt = ioremap(base,offset+4);
	virt += offset;
	os_print(" vir add is %8u\n", virt);
//	ret=ioread16(virt);
	ret=*((short *)virt);
	return(ret);
}
/**************************************************/
char	map_read8(int phy_addr);
char	map_read8(int phy_addr)
{
	int	base;
	int offset;
	char ret;
	volatile void *virt;
	base=phy_addr&SEG_MASK;
	offset=phy_addr&OFF_MASK;
	virt = ioremap(base,offset+4);
	virt += offset;
//	ret=ioread8(virt);
	ret=*((char *)virt);
	return(ret);
}
/**************************************************/
/* end of map_read.c */
