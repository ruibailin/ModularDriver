
/*------------------------------------
 * configuration.c
 * Create:  2021-10-26
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#include "0ctr.h"
#include "1imp.h"
/*================================================================*/
/** Device Configuration Register */
#define DCFG                    DEVICE_REG(0x00)
#define DCFG_devspd_bitp        0 /** Device Speed */
#define DCFG_devspd_bits        0x3
#define DCFG_devspd_hs_phy_hs   0 /** High speed PHY running at high speed */
#define DCFG_devspd_hs_phy_fs   1 /** High speed PHY running at full speed */
#define DCFG_nzstsouthshk       (1 << 2) /** Non Zero Length Status OUT Handshake */
#define DCFG_devadr_bitp        4 /** Device Address */
#define DCFG_devadr_bits        0x7f
#define DCFG_perfrint_bitp      11 /** Periodic Frame Interval */
#define DCFG_perfrint_bits      0x3
#define DCFG_FRAME_INTERVAL_80  0
#define DCFG_FRAME_INTERVAL_85  1
#define DCFG_FRAME_INTERVAL_90  2
#define DCFG_FRAME_INTERVAL_95  3
/*================================================================*/
void d_cfg_reset_device(void);
void d_cfg_reset_device()
{
	//reset usb core parameters (dev addr, speed, ...)
	DCFG = 0;
}

void d_cfg_ini_phy_speed(void);
void d_cfg_ini_phy_speed()
{
	/* Set phy speed : high speed */
	DCFG = (DCFG & ~bitm(DCFG, devspd)) | DCFG_devspd_hs_phy_fs;
}

void d_cfg_set_phy_speed(void);
void d_cfg_set_phy_speed()
{
    /* Set phy speed : high speed */
    DCFG = (DCFG & ~bitm(DCFG, devspd)) | DCFG_devspd_hs_phy_fs;
}

/*================================================================*/
void d_cfg_reset_device_addr(void);
void d_cfg_reset_device_addr()
{
    /* Reset Device Address */
    DCFG &= ~bitm(DCFG, devadr);
}

void d_cfg_set_device_addr(int value);
void d_cfg_set_device_addr(int value)
{
	 DCFG = (DCFG & ~bitm(DCFG, devadr)) | (value << DCFG_devadr_bitp);
}
/*================================================================*/

/* end of configuration.c */
