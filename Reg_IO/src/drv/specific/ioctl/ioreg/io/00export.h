
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

#ifndef IOREG_IO_00EXPORT_H_
#define IOREG_IO_00EXPORT_H_


/**************************************************/
extern void	map_write32(int phy_addr,int val);
extern int	map_read32(int phy_addr);
extern void	map_write16(int phy_addr,int val);
extern int	map_read16(int phy_addr);
extern void	map_write8(int phy_addr,int val);
extern int	map_read8(int phy_addr);
/**************************************************/
#endif 
/* end of 00export.h */
