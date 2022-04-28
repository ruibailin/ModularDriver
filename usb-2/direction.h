
/*------------------------------------
 * direction.h
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


#ifndef DRV_USB_DIRECTION_H_
#define DRV_USB_DIRECTION_H_
/*================================================================*/
//Endpoint direction
#define DIR_OUT 	0
#define DIR_IN 		1


/* The USB core is a device, and OUT is RX from that P.O.V */
#define DIR_RX 		DIR_OUT
#define DIR_TX 		DIR_IN

/*
 * USB directions
 *
 * This bit flag is used in endpoint descriptors' bEndpointAddress field.
 * It's also one of three fields in control requests bRequestType.
 */
#define USB_DIR_OUT                     0               /* to device */
#define USB_DIR_IN                      0x80            /* to host */

#define EP_CONTROL 0

#define USB_ENDPOINT_NUMBER_MASK        0x0f    /* in bEndpointAddress */
#define USB_ENDPOINT_DIR_MASK           0x80

#define EP_DIR(ep) (((ep) & USB_ENDPOINT_DIR_MASK) ? DIR_IN : DIR_OUT)
#define EP_NUM(ep) ((ep) & USB_ENDPOINT_NUMBER_MASK)
/*================================================================*/
#endif
/* end of direction.h */
