
/*------------------------------------
 * event.h
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


#ifndef DRV_USB_EVENT_H_
#define DRV_USB_EVENT_H_
/*================================================================*/
/* Messages from usb_tick and thread states */
enum USB_EVENT{
    USB_EXTRACT = 0, /* Event */
    USB_INSERT, /* Event */
    USB_POWER, /* Event */
    USB_SCREENDUMP, /* State */
    USB_UNPOWERED, /* Event */
    USB_REENABLE, /* Event */
    USB_TRANSFER_COMPLETION, /* Event */
    USB_REQUEST_REBOOT, /* Event */
    USB_QUIT, /* Event */
};

/*================================================================*/
#endif
/* end of event.h */
