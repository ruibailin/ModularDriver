
/*------------------------------------
 * device.c
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
#include "../class.h"
/*================================================================*/
/* USB_DT_DEVICE: Device descriptor */
struct usb_device_descriptor {
    u8_t bLength;
    u8_t bDescriptorType;

    u16_t bcdUSB;
    u8_t bDeviceClass;
    u8_t bDeviceSubClass;
    u8_t bDeviceProtocol;
    u8_t bMaxPacketSize0;
    u16_t idVendor;
    u16_t idProduct;
    u16_t bcdDevice;
    u8_t iManufacturer;
    u8_t iProduct;
    u8_t iSerialNumber;
    u8_t bNumConfigurations;
}__attribute__ ((packed));

#define	USB_VENDOR_ID	0x1234
#define	USB_PRODUCT_ID	0x4321
static struct usb_device_descriptor __attribute__((aligned(2)))
device_descriptor = {
		.bLength = sizeof(struct usb_device_descriptor),
		.bDescriptorType = USB_DT_DEVICE,
#ifndef USB_NO_HIGH_SPEED
        .bcdUSB = 0x0200,
#else
        .bcdUSB = 0x0110,
#endif
        .bDeviceClass = USB_CLASS_PER_INTERFACE,
		.bDeviceSubClass = 0,
		.bDeviceProtocol = 0,
		.bMaxPacketSize0 = 64,
		.idVendor = USB_VENDOR_ID,
		.idProduct = USB_PRODUCT_ID,
		.bcdDevice = 0x0100,
		.iManufacturer = 1,
        .iProduct = 2,
		.iSerialNumber = 3,
		.bNumConfigurations = 1
};


void core_desc_dev_clr_serial(void);
void core_desc_dev_clr_serial()
{
    device_descriptor.iSerialNumber = 0;
}

void *core_desc_dev_get_add(void);
void *core_desc_dev_get_add()
{
	void *ptr;
	ptr =(void *)&device_descriptor;
	return ptr;
}

int core_desc_dev_get_len(void);
int core_desc_dev_get_len()
{
	int len;
	len = sizeof(struct usb_device_descriptor);
	return len;
}
/*================================================================*/

/* end of device.c */
