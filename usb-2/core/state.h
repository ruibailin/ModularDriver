
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


#ifndef DRV_USB_STATE_H_
#define DRV_USB_STATE_H_
/*================================================================*/
enum USB_STATE {
    USB_EXTRACTED = 0, /* Event+State */
    USB_INSERTED, /* Event+State */
    USB_POWERED, /* Event+State */
    USB_SCREENED, /* State */
};

/*================================================================*/
#endif
/* end of state.h */
