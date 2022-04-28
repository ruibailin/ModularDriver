
/*---------------------------
 * libregio.c
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

#include "01import.h"
/**************************************************/
static int regio_fd = 0;
/**************************************************/
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#define DRV_MODULE_NAME		"/dev/rbl_reg"
int	reg_open_regio(void);
int	reg_open_regio(void)
{
    regio_fd = open(DRV_MODULE_NAME, O_RDWR, 00);
    if (regio_fd != -1)
    	return 1;
   	os_print("ERROR! Failed to open %s\n", DRV_MODULE_NAME);
   	return 0;
}

/**************************************************/
int	reg_close_regio(void);
int	reg_close_regio(void)
{
    close(regio_fd);

    os_print("Success to close %s\n", DRV_MODULE_NAME);

	return 1;
}

/**************************************************/
int reg_read32_regio(int phy_add);
int reg_read32_regio(int phy_add)
{
	IO_REG_CMD_T	ioreg;
	ioreg.phy_add=phy_add;
    ioctl(regio_fd, FILE_CMD_READ32_REG, &ioreg);
    return(ioreg.val.reg32);
}

/**************************************************/
short int reg_read16_regio(int phy_add);
short int reg_read16_regio(int phy_add)
{
	IO_REG_CMD_T	ioreg;
	ioreg.phy_add=phy_add;
    ioctl(regio_fd, FILE_CMD_READ16_REG, &ioreg);
    return(ioreg.val.reg16[0]);
}

/**************************************************/
char reg_read8_regio(int phy_add);
char reg_read8_regio(int phy_add)
{
	IO_REG_CMD_T	ioreg;
	ioreg.phy_add=phy_add;
    ioctl(regio_fd, FILE_CMD_READ8_REG, &ioreg);
    return(ioreg.val.reg8[0]);
}

/**************************************************/
void reg_write32_regio(int phy_add,int val);
void reg_write32_regio(int phy_add,int val)
{
	IO_REG_CMD_T	ioreg;
	ioreg.phy_add=phy_add;
	ioreg.val.reg32=val;
    ioctl(regio_fd, FILE_CMD_WRITE32_REG, &ioreg);
}

/**************************************************/
void reg_write16_regio(int phy_add,short int val);
void reg_write16_regio(int phy_add,short int val)
{
	IO_REG_CMD_T	ioreg;
	ioreg.phy_add=phy_add;
	ioreg.val.reg16[0]=val;
    ioctl(regio_fd, FILE_CMD_WRITE16_REG, &ioreg);
}

/**************************************************/
void reg_write8_regio(int phy_add,char val);
void reg_write8_regio(int phy_add,char val)
{
	IO_REG_CMD_T	ioreg;
	ioreg.phy_add=phy_add;
	ioreg.val.reg8[0]=val;
    ioctl(regio_fd, FILE_CMD_WRITE8_REG, &ioreg);
}
/**************************************************/
/* end of libregio.c */
