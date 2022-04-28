
/*------------------------------------
 * speed.h
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



#ifndef USB_GADGET_SPEED_H_
#define USB_GADGET_SPEED_H_
/*================================================================*/
/* USB 2.0 defines three speeds, here's how Linux identifies them */

enum usb_device_speed {
    USB_SPEED_UNKNOWN = 0, /* enumerating */
    USB_SPEED_LOW,
	USB_SPEED_FULL, /* usb 1.1 */
    USB_SPEED_HIGH, /* usb 2.0 */
    USB_SPEED_VARIABLE, /* wireless (usb 2.5) */
};

/*================================================================*/
#endif
/* end of speed.h */
