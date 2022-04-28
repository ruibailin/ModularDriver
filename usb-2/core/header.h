
/*------------------------------------
 * header.h
 * Create:  2021-10-23
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 * Not be used now
 *
 *
 *
 *------------------------------------
 */



#ifndef USB_DESC_HEADER_H_
#define USB_DESC_HEADER_H_
/*================================================================*/
#include "1imp.h"
/* All standard descriptors have these 2 fields at the beginning */
struct usb_descriptor_header {
    u8_t bLength;
    u8_t bDescriptorType;
}__attribute__ ((packed));

/* USB_DT_DEBUG:  for special highspeed devices, replacing serial console */
struct usb_debug_descriptor {
    u8_t bLength;
    u8_t bDescriptorType;

    /* bulk endpoints with 8 byte maxpacket */
    u8_t bDebugInEndpoint;
    u8_t bDebugOutEndpoint;
}__attribute__((packed));

/* USB_DT_OTG (from OTG 1.0a supplement) */
struct usb_otg_descriptor {
    u8_t bLength;
    u8_t bDescriptorType;

    u8_t bmAttributes; /* support for HNP, SRP, etc */
}__attribute__ ((packed));

/* from usb_otg_descriptor.bmAttributes */
#define USB_OTG_SRP             (1 << 0)
#define USB_OTG_HNP             (1 << 1)        /* swap host/device roles */
/*================================================================*/
#endif
/* end of header.h */
