
/*------------------------------------
 * config.c
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

/* USB_DT_CONFIG: Configuration descriptor information.
 *
 * USB_DT_OTHER_SPEED_CONFIG is the same descriptor, except that the
 * descriptor type is different.  Highspeed-capable devices can look
 * different depending on what speed they're currently running.  Only
 * devices with a USB_DT_DEVICE_QUALIFIER have any OTHER_SPEED_CONFIG
 * descriptors.
 */
struct usb_config_descriptor {
    u8_t bLength;
    u8_t bDescriptorType;

    u16_t wTotalLength;
    u8_t bNumInterfaces;
    u8_t bConfigurationValue;
    u8_t iConfiguration;
    u8_t bmAttributes;
    u8_t bMaxPower;
}__attribute__ ((packed));

/* from config descriptor bmAttributes */
#define USB_CONFIG_ATT_ONE              (1 << 7)        /* must be set */
#define USB_CONFIG_ATT_SELFPOWER        (1 << 6)        /* self powered */
#define USB_CONFIG_ATT_WAKEUP           (1 << 5)        /* can wakeup */
#define USB_CONFIG_ATT_BATTERY          (1 << 4)        /* battery powered */

#include "../dt_type.h"
static struct usb_config_descriptor __attribute__((aligned(2)))
config_descriptor = {
		.bLength = sizeof(struct usb_config_descriptor),
		.bDescriptorType = USB_DT_CONFIG,
		.wTotalLength = 0, /* will be filled in later */
		.bNumInterfaces = 1,
		.bConfigurationValue = 1,
		.iConfiguration = 0,
		.bmAttributes = USB_CONFIG_ATT_ONE, /*| USB_CONFIG_ATT_SELFPOWER,*/
		.bMaxPower = 0x31, //(USB_MAX_CURRENT + 1) / 2, /* In 2mA units */
        };
/*================================================================*/
int core_desc_cfg_set_type(char type);
int core_desc_cfg_set_type(char type)
{
	int msp;
    if (type == USB_DT_CONFIG) {
        msp = (otg_port_speed() ? 512 : 64);
        config_descriptor.bDescriptorType = USB_DT_CONFIG;
    } else {
        msp = (otg_port_speed() ? 64 : 512);
        config_descriptor.bDescriptorType = USB_DT_OTHER_SPEED_CONFIG;
    }
    return msp;
}

void *core_desc_cfg_get_add(void);
void *core_desc_cfg_get_add()
{
	return (void *)&config_descriptor;
}

int core_desc_cfg_get_len();
int core_desc_cfg_get_len()
{
	int size;
	size = sizeof(struct usb_config_descriptor);
	return size;
}

extern unsigned char *response_data;
void core_desc_cfg_set_dt_config(int intf,int size);
void core_desc_cfg_set_dt_config(int intf,int size)
{
    config_descriptor.bNumInterfaces = intf;
    config_descriptor.wTotalLength = (u16_t) size;
    BTR_USB_MEMCPY(&response_data[0], &config_descriptor, sizeof(struct usb_config_descriptor));

}
/*================================================================*/

/* end of config.c */
