
/*------------------------------------
 * qualiier.c
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
/*================================================================*/

/* USB_DT_DEVICE_QUALIFIER: Device Qualifier descriptor */
struct usb_qualifier_descriptor {
    u8_t bLength;
    u8_t bDescriptorType;

    u16_t bcdUSB;
    u8_t bDeviceClass;
    u8_t bDeviceSubClass;
    u8_t bDeviceProtocol;
    u8_t bMaxPacketSize0;
    u8_t bNumConfigurations;
    u8_t bRESERVED;
}__attribute__ ((packed));

static const struct usb_qualifier_descriptor __attribute__((aligned(2)))
qualifier_descriptor = {
		.bLength = sizeof(struct usb_qualifier_descriptor),
		.bDescriptorType = USB_DT_DEVICE_QUALIFIER,
        .bcdUSB = 0x0200,
		.bDeviceClass = 0,
		.bDeviceSubClass = 0,
		.bDeviceProtocol = 0,
		.bMaxPacketSize0 = 64,
        .bNumConfigurations = 1
};

/*================================================================*/
void *core_desc_qual_get_add(void);
void *core_desc_qual_get_add()
{
	void *ptr;
	ptr =(void *)&qualifier_descriptor;
	return ptr;
}

int core_desc_qual_get_len(void);
int core_desc_qual_get_len()
{
	int len;
	len = sizeof(struct usb_qualifier_descriptor);
	return len;
}

/*================================================================*/

/* end of qualiier.c */
