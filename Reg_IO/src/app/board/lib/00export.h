
/*---------------------------
 * 00export.h
 *  Created on: Apr 18, 2019
 *      Author: Steve Rui
 *---------------------------
 *
 *
 *
 *
 *
 *---------------------------
 */

#ifndef APP_BOARD_LIB_00EXPORT_H_
#define APP_BOARD_LIB_00EXPORT_H_


/**************************************************/
extern int	reg_open_regio(void);
extern int	reg_close_regio(void);

extern int reg_read32_regio(int phy_add);
extern short int reg_read16_regio(int phy_add);
extern char reg_read8_regio(int phy_add);
extern void reg_write32_regio(int phy_add,int val);
extern void reg_write16_regio(int phy_add,short int val);
extern void reg_write8_regio(int phy_add,char val);

/**************************************************/
#endif 
/* end of 00export.h */
