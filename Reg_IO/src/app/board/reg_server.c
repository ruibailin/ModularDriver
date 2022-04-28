
/*---------------------------
 * reg_server.c
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
#include "./lib/00export.h"
#include "./skt/00export.h"
/**************************************************/
#include <stdio.h>
#include <stdlib.h>

#define IOMUX_BASE	0x021D0000
static void check_mipi_csi(void);
static void check_mipi_csi()
{
	int val;
	val=reg_read32_regio(IOMUX_BASE+0xC000);
	os_print("MIPI_CSI_VERSION= %8x \n",val);
	val=reg_read32_regio(IOMUX_BASE+0xC004);
	os_print("MIPI_CSI_N_LANES= %8x \n",val);
	val=reg_read32_regio(IOMUX_BASE+0xC008);
	os_print("MIPI_CSI_PHY_SHUTDOWNZ= %8x \n",val);
	val=reg_read32_regio(IOMUX_BASE+0xC00C);
	os_print("MIPI_CSI_DPHY_RSTZ= %8x \n",val);
	val=reg_read32_regio(IOMUX_BASE+0xC010);
	os_print("MIPI_CSI_CSI2_RESETN= %8x \n",val);
	val=reg_read32_regio(IOMUX_BASE+0xC014);
	os_print("MIPI_CSI_PHY_STATE= %8x \n",val);
	val=reg_read32_regio(IOMUX_BASE+0xC018);
	os_print("MIPI_CSI_DATA_IDS_1= %8x \n",val);
	val=reg_read32_regio(IOMUX_BASE+0xC01C);
	os_print("MIPI_CSI_DATA_IDS_2= %8x \n",val);
	val=reg_read32_regio(IOMUX_BASE+0xC020);
	os_print("MIPI_CSI_ERR1= %8x \n",val);
	val=reg_read32_regio(IOMUX_BASE+0xC024);
	os_print("MIPI_CSI_ERR2= %8x \n",val);
	val=reg_read32_regio(IOMUX_BASE+0xC028);
	os_print("MIPI_CSI_MASK1= %8x \n",val);
	val=reg_read32_regio(IOMUX_BASE+0xC02C);
	os_print("MIPI_CSI_MASK2= %8x \n",val);
	val=reg_read32_regio(IOMUX_BASE+0xC030);
	os_print("MIPI_CSI_PHY_TST_CRTL0= %8x \n",val);
	val=reg_read32_regio(IOMUX_BASE+0xC034);
	os_print("MIPI_CSI_PHY_TST_CRTL1= %8x \n",val);
}

/**************************************************/
static void check_i2c_val(void);
static void check_i2c_val()
{
	int val;
	val=reg_read16_regio(0x021A0000+0x0000);
	os_print("I2C1_IADR= %8x \n",val);
	val=reg_read16_regio(0x021A0000+0x0004);
	os_print("I2C1_IFDR= %8x \n",val);
	val=reg_read16_regio(0x021A0000+0x0008);
	os_print("I2C1_I2CR= %8x \n",val);
	val=reg_read16_regio(0x021A0000+0x000C);
	os_print("I2C1_I2SR= %8x \n",val);
	val=reg_read16_regio(0x021A0000+0x0010);
	os_print("I2C1_I2DR= %8x \n",val);

	val=reg_read16_regio(0x021A4000+0x0000);
	os_print("I2C2_IADR= %8x \n",val);
	val=reg_read16_regio(0x021A4000+0x0004);
	os_print("I2C2_IFDR= %8x \n",val);
	val=reg_read16_regio(0x021A4000+0x0008);
	os_print("I2C2_I2CR= %8x \n",val);
	val=reg_read16_regio(0x021A4000+0x000C);
	os_print("I2C2_I2SR= %8x \n",val);
	val=reg_read16_regio(0x021A4000+0x0010);
	os_print("I2C2_I2DR= %8x \n",val);

	val=reg_read16_regio(0x021A8000+0x0000);
	os_print("I2C3_IADR= %8x \n",val);
	val=reg_read16_regio(0x021A8000+0x0004);
	os_print("I2C3_IFDR= %8x \n",val);
	val=reg_read16_regio(0x021A8000+0x0008);
	os_print("I2C3_I2CR= %8x \n",val);
	val=reg_read16_regio(0x021A8000+0x000C);
	os_print("I2C3_I2SR= %8x \n",val);
	val=reg_read16_regio(0x021A8000+0x0010);
	os_print("I2C3_I2DR= %8x \n",val);

}



/**************************************************/
static void check_muxc_gpio(void);
static void check_muxc_gpio()
{
	int i, val;
	for(i=0;i<13;i++)
	{
		val=reg_read32_regio(0x020E0000+(i<<2));
		os_print("GPIO%2d,val=%8x\n",i,val);
	}
}

/**************************************************/
static void check_muxc_ctl_pad(void);
static void check_muxc_ctl_pad()
{
	int i, val;
	for(i=0;i<240;i++)
	{
		val=reg_read32_regio(0x020E004C+(i<<2));
		os_print("MUX CTL PAD%3d,val=%8x\n",i,val);
	}
}

static void read_chip_id(void);
static void read_chip_id()
{

}

int board_main(void)
{
	int val;
	reg_open_regio();
	check_mipi_csi();
	check_i2c_val();
	check_muxc_gpio();
	check_muxc_ctl_pad();
	reg_close_regio();
	return EXIT_SUCCESS;
}

/**************************************************/
/* end of reg_server.c */
