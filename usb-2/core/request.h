
/*------------------------------------
 * request.h
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


#ifndef DRV_USB_REQUEST_H_
#define DRV_USB_REQUEST_H_
/*================================================================*/
/* CONTROL REQUEST SUPPORT */


/*
 * USB types, the second of three bRequestType fields
 */
#define USB_TYPE_MASK                   (0x03 << 5)
#define USB_TYPE_STANDARD               (0x00 << 5)
#define USB_TYPE_CLASS                  (0x01 << 5)
#define USB_TYPE_VENDOR                 (0x02 << 5)
#define USB_TYPE_RESERVED               (0x03 << 5)

/*
 * USB recipients, the third of three bRequestType fields
 */
#define USB_RECIP_MASK                  0x1f
#define USB_RECIP_DEVICE                0x00
#define USB_RECIP_INTERFACE             0x01
#define USB_RECIP_ENDPOINT              0x02
#define USB_RECIP_OTHER                 0x03

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
/*
 * USB feature flags are written using USB_REQ_{CLEAR,SET}_FEATURE, and
 * are read as a bit array returned by USB_REQ_GET_STATUS.  (So there
 * are at most sixteen features of each type.)  Hubs may also support a
 * new USB_REQ_TEST_AND_SET_FEATURE to put ports into L1 suspend.
 */
#define USB_DEVICE_SELF_POWERED         0   /* (read only) */
#define USB_DEVICE_REMOTE_WAKEUP        1   /* dev may initiate wakeup */
#define USB_DEVICE_TEST_MODE            2   /* (wired high speed only) */
#define USB_DEVICE_BATTERY              2   /* (wireless) */
#define USB_DEVICE_B_HNP_ENABLE         3   /* (otg) dev may initiate HNP */
#define USB_DEVICE_WUSB_DEVICE          3   /* (wireless)*/
#define USB_DEVICE_A_HNP_SUPPORT        4   /* (otg) RH port supports HNP */
#define USB_DEVICE_A_ALT_HNP_SUPPORT    5   /* (otg) other RH port does */
#define USB_DEVICE_DEBUG_MODE           6   /* (special devices only) */

/*================================================================*/
#endif
/* end of request.h */
