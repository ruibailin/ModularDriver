
/*------------------------------------
 * ctrlrequest.c
 * Create:  2021-10-28
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
/**
 * struct usb_ctrlrequest - SETUP data for a USB device control request
 * @bRequestType: matches the USB bmRequestType field
 * @bRequest: matches the USB bRequest field
 * @wValue: matches the USB wValue field (le16 byte order)
 * @wIndex: matches the USB wIndex field (le16 byte order)
 * @wLength: matches the USB wLength field (le16 byte order)
 *
 * This structure is used to send control requests to a USB device.  It matches
 * the different fields of the USB 2.0 Spec section 9.3, table 9-2.  See the
 * USB spec for a fuller description of the different fields, and what they are
 * used for.
 *
 * Note that the driver for any interface can issue control requests.
 * For most devices, interfaces don't coordinate with each other, so
 * such requests may be made at any time.
 */
struct usb_ctrlrequest {
    u8_t bRequestType;
    u8_t bRequest;
    u16_t wValue;
    u16_t wIndex;
    u16_t wLength;
}__attribute__ ((packed));

void *ep0_setup_pkt = BTR_DMA_ADDR(BTR_NAND_DMA_BASE);
/*================================================================*/
u8_t usb_get_ctrlrequest_type(void *pkt);
u8_t usb_get_ctrlrequest_type(void *pkt)
{
	struct usb_ctrlrequest *req;
	req = (struct usb_ctrlrequest *)pkt;
	return req->bRequestType;
}

u8_t usb_get_ctrlrequest_request(void *pkt);
u8_t usb_get_ctrlrequest_request(void *pkt)
{
	struct usb_ctrlrequest *req;
	req = (struct usb_ctrlrequest *)pkt;
	return req->bRequest;
}

u16_t usb_get_ctrlrequest_length(void *pkt);
u16_t usb_get_ctrlrequest_length(void *pkt)
{
	struct usb_ctrlrequest *req;
	req = (struct usb_ctrlrequest *)pkt;
	return req->wLength;
}

/*================================================================*/
u16_t usb_get_ctrlrequest_value(void *pkt);
u16_t usb_get_ctrlrequest_value(void *pkt)
{
	struct usb_ctrlrequest *req;
	req = (struct usb_ctrlrequest *)pkt;
	return req->wValue;
}

u16_t usb_get_ctrlrequest_index(void *pkt);
u16_t usb_get_ctrlrequest_index(void *pkt)
{
	struct usb_ctrlrequest *req;
	req = (struct usb_ctrlrequest *)pkt;
	return req->wIndex;
}
/*================================================================*/
/*
 * USB types, the second of three bRequestType fields
 */
#define USB_TYPE_MASK                   (0x03 << 5)
#define USB_TYPE_STANDARD               (0x00 << 5)
#define USB_TYPE_CLASS                  (0x01 << 5)
#define USB_TYPE_VENDOR                 (0x02 << 5)
#define USB_TYPE_RESERVED               (0x03 << 5)

/*
 * Standard requests, for the bRequest field of a SETUP packet.
 *
 * These are qualified by the bRequestType field, so that for example
 * TYPE_CLASS or TYPE_VENDOR specific feature flags could be retrieved
 * by a GET_STATUS request.
 */
#define USB_REQ_GET_STATUS              0x00
#define USB_REQ_CLEAR_FEATURE           0x01
#define USB_REQ_SET_FEATURE             0x03
#define USB_REQ_SET_ADDRESS             0x05
#define USB_REQ_GET_DESCRIPTOR          0x06
#define USB_REQ_SET_DESCRIPTOR          0x07
#define USB_REQ_GET_CONFIGURATION       0x08
#define USB_REQ_SET_CONFIGURATION       0x09
#define USB_REQ_GET_INTERFACE           0x0A
#define USB_REQ_SET_INTERFACE           0x0B
#define USB_REQ_SYNCH_FRAME             0x0C

bool usb_is_ctrlrequest_set_add(void *pkt);
bool usb_is_ctrlrequest_set_add(void *pkt)
{
	struct usb_ctrlrequest *req;
	req = (struct usb_ctrlrequest *)pkt;

    panicf("rt=%x r=%x\n\r", req->bRequestType, req->bRequest);

	if (req->bRequestType != USB_TYPE_STANDARD)
    	return false;
    if (req->bRequest != USB_REQ_SET_ADDRESS)
    	return false;
    panicf(" \n\rSet address[%d]\n\r", req->wValue);
    /* Set address now */
    return true;
}

/*================================================================*/

/* end of ctrlrequest.c */
