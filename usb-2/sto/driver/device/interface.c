
/*------------------------------------
 * interface.c
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

#include "0ctr.h"
#include "1imp.h"

#include "../../desc/desc.h"
/*================================================================*/
static int usb_interface;

void sto_drv_if_set_interface(int uif);
void sto_drv_if_set_interface(int uif)
{
	usb_interface = uif;
}

int sto_drv_if_get_interface(void);
int sto_drv_if_get_interface()
{
	return usb_interface;
}

u8_t *sto_drv_if_get_interface_desc(u8_t *dest);
u8_t *sto_drv_if_get_interface_desc(u8_t *dest)
{
	dest = sto_desc_if_get_config(dest,usb_interface);
	return dest;
}

/*================================================================*/

/* end of interface.c */
