
/*------------------------------------
 * endpoint.c
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

#define USB_ENDPOINT_HALT       		0   	/* IN/OUT will STALL */

#define USB_ENDPOINT_NUMBER_MASK        0x0f    /* in bEndpointAddress */
#define USB_ENDPOINT_DIR_MASK           0x80

#define USB_ENDPOINT_XFERTYPE_MASK      0x03    /* in bmAttributes */
#define USB_ENDPOINT_XFER_CONTROL       0
#define USB_ENDPOINT_XFER_ISOC          1
#define USB_ENDPOINT_XFER_BULK          2
#define USB_ENDPOINT_XFER_INT           3
#define USB_ENDPOINT_MAX_ADJUSTABLE     0x80

/* USB_DT_ENDPOINT: Endpoint descriptor */
struct usb_endpoint_descriptor {
    u8_t bLength;
    u8_t bDescriptorType;

    u8_t bEndpointAddress;
    u8_t bmAttributes;
    u16_t wMaxPacketSize;
    u8_t bInterval;
}__attribute__ ((packed));


static struct usb_endpoint_descriptor __attribute__((aligned(2)))
endpoint_descriptor =
{
		.bLength = sizeof(struct usb_endpoint_descriptor),
		.bDescriptorType = USB_DT_ENDPOINT,
        .bEndpointAddress = 0,
		.bmAttributes = USB_ENDPOINT_XFER_BULK,
		.wMaxPacketSize = 0,
		.bInterval = 0
};

/*================================================================*/
u8_t *sto_desc_ep_get_config(u8_t *dest,int mps, int ep_in,int ep_out);
u8_t *sto_desc_ep_get_config(u8_t *dest,int mps, int ep_in,int ep_out)
{
    endpoint_descriptor.wMaxPacketSize = mps;

    endpoint_descriptor.bEndpointAddress = ep_in;
    PACK_DATA(dest, endpoint_descriptor);

    endpoint_descriptor.bEndpointAddress = ep_out;
    PACK_DATA(dest, endpoint_descriptor);
	return dest;
}
/*================================================================*/

/* end of endpoint.c */
