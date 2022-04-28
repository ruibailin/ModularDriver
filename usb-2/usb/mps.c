
/*------------------------------------
 * mps.c
 * Create:  2021-11-14
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 * max_packet_size
 *
 *
 *
 *------------------------------------
 */


/*================================================================*/
#include "../1imp.h"

/*================================================================*/
#define USB_ENDPOINT_XFERTYPE_MASK      0x03    /* in bmAttributes */
#define USB_ENDPOINT_XFER_CONTROL       0
#define USB_ENDPOINT_XFER_ISOC          1
#define USB_ENDPOINT_XFER_BULK          2
#define USB_ENDPOINT_XFER_INT           3
#define USB_ENDPOINT_MAX_ADJUSTABLE     0x80

//MPS: MAX Packet Size
static const u16_t mps[4][2] =
{
		/*         type                   fs, hs   */
		[USB_ENDPOINT_XFER_CONTROL] = 	{ 64, 64 },
		[USB_ENDPOINT_XFER_ISOC] = 		{ 1023, 1024 },
		[USB_ENDPOINT_XFER_BULK] = 		{ 64, 512 },
        [USB_ENDPOINT_XFER_INT] = 		{ 64, 1024 },
};

int usb_get_ep_mps(int ep_type,int speed_type);
int usb_get_ep_mps(int ep_type,int speed_type)
{
	speed_type &= 1;
	ep_type &= USB_ENDPOINT_XFERTYPE_MASK;
	return mps[ep_type][speed_type];
}

/*================================================================*/

/* end of mps.c */
