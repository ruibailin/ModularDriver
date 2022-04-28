
/*---------------------------
 * map_write.c
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
void	map_write32(int phy_addr,int val);
void	map_write32(int phy_addr,int val)
{
	int	base;
	int offset;
	volatile void *virt;
	base=phy_addr&SEG_MASK;
	offset=phy_addr&OFF_MASK;
	virt = ioremap(base,offset+4);
	virt += offset;
//	iowrite32(val,virt);
	*((int *)virt)=val;
}
/**************************************************/
void	map_write16(int phy_addr,short val);
void	map_write16(int phy_addr,short val)
{
	int	base;
	int offset;
	volatile void *virt;
	base=phy_addr&SEG_MASK;
	offset=phy_addr&OFF_MASK;
	virt = ioremap(base,offset+4);
	virt += offset;
//	iowrite16(val,virt);
	*((short *)virt)=val;

}
/**************************************************/
void	map_write8(int phy_addr,char val);
void	map_write8(int phy_addr,char val)
{
	int	base;
	int offset;
	volatile void *virt;
	base=phy_addr&SEG_MASK;
	offset=phy_addr&OFF_MASK;
	virt = ioremap(base,offset+4);
	virt += offset;
//	iowrite8(val,virt);
	*((char *)virt)=val;
}

/**************************************************/
/* end of map_write.c */
