
/*------------------------------------
 * core.c
 * Create:  2021-10-29
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#include "../0ctr.h"
#include "../1imp.h"
/*================================================================*/
#include "../device/device.h"
void otg_drv_core_init(void);
void otg_drv_core_init()
{
    /* Disconnect */
	d_ctl_disconnect();
	g_ahb_init();
	g_usb_init();
	d_ctl_reconnect();
    /* perform device model specific init */
    otg_drv_dev_init();
}

void otg_drv_core_enable_global_interrupts(void);
void otg_drv_core_enable_global_interrupts()
{
	g_ahb_enable_global();
}

void otg_drv_core_disable_global_interrupts(void);
void otg_drv_core_disable_global_interrupts()
{
	g_ahb_disable_global();
}
/*================================================================*/

/* end of core.c */
