
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
/*================================================================*/
#include "class.h"
#include "dt_type.h"

struct usb_interface_descriptor {
    u8_t bLength;
    u8_t bDescriptorType;

    u8_t bInterfaceNumber;
    u8_t bAlternateSetting;
    u8_t bNumEndpoints;
    u8_t bInterfaceClass;
    u8_t bInterfaceSubClass;
    u8_t bInterfaceProtocol;
    u8_t iInterface;
}__attribute__ ((packed));

/* storage interface */

#define USB_SC_SCSI      0x06            /* Transparent */
#define USB_PROT_BULK    0x50            /* bulk only */

static struct usb_interface_descriptor __attribute__((aligned(2)))
interface_descriptor = {
		.bLength = sizeof(struct usb_interface_descriptor),
		.bDescriptorType = USB_DT_INTERFACE,
        .bInterfaceNumber = 0,
		.bAlternateSetting = 0,
		.bNumEndpoints = 2,
		.bInterfaceClass = USB_CLASS_MASS_STORAGE,
        .bInterfaceSubClass = USB_SC_SCSI,
		.bInterfaceProtocol = USB_PROT_BULK,
		.iInterface = 0
};

/*================================================================*/
u8_t *sto_desc_if_get_config(u8_t *dest,int interface);
u8_t *sto_desc_if_get_config(u8_t *dest,int interface)
{
	interface_descriptor.bInterfaceNumber = interface;
	PACK_DATA(dest, interface_descriptor);

	return dest;
}
/*================================================================*/

/* end of interface.c */
