
/*------------------------------------
 * core.c
 * Create:  2021-10-23
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

#include "../otg/otg.h"
#include "./driver/driver.h"
/*================================================================*/
bool 	usb_core_initialized = false;

/*================================================================*/
void core_data_reset(void);
void core_data_reset()
{
    usb_core_initialized = false;
}

void core_init(void);
void core_init()
{

    if (usb_core_initialized)
        return;

    otg_init();

    core_drv_init();

    usb_core_initialized = true;
    BTR_USB_PRINTF("core_init() finished\n\r");
}

void core_exit(void);
void core_exit()
{
	core_drv_exit();

    if (usb_core_initialized) {
        otg_exit();
        usb_core_initialized = false;
    }
    BTR_USB_PRINTF("usb_core_exit() finished");
}
/*================================================================*/

/* end of core.c */
