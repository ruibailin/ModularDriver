
/*------------------------------------
 * state.h
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


#ifndef USB_GADGET_STATE_H_
#define USB_GADGET_STATE_H_
/*================================================================*/
enum usb_device_state {
    /* NOTATTACHED isn't in the USB spec, and this state acts
     * the same as ATTACHED ... but it's clearer this way.
     */
    USB_STATE_NOTATTACHED = 0,

    /* chapter 9 and authentication (wireless) device states */
    USB_STATE_ATTACHED,
	USB_STATE_POWERED, /* wired */
    USB_STATE_UNAUTHENTICATED, /* auth */
    USB_STATE_RECONNECTING, /* auth */
    USB_STATE_DEFAULT, /* limited function */
    USB_STATE_ADDRESS,
	USB_STATE_CONFIGURED, /* most functions */

    USB_STATE_SUSPENDED

/* NOTE:  there are actually four different SUSPENDED
 * states, returning to POWERED, DEFAULT, ADDRESS, or
 * CONFIGURED respectively when SOF tokens flow again.
 * At this level there's no difference between L1 and L2
 * suspend states.  (L2 being original USB 1.1 suspend.)
 */
};

/*================================================================*/
#endif
/* end of state.h */
