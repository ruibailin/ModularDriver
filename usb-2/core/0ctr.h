
/*------------------------------------
 * 0ctr.h
 * Create:  2021-10-23
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 * To control the feature of USB
 *
 *
 *
 *------------------------------------
 */


#include "../0ctr.h"
#ifndef DRV_USB_0CTR_H_
#define DRV_USB_0CTR_H_
/*================================================================*/
#define	IPOD_COLOR		1
#define	IPOD_4G			1
#define	IPOD_MINI		1
#define	IPOD_MINI2G		0
#if defined(IPOD_COLOR) || defined(IPOD_4G) \
 || defined(IPOD_MINI)  || defined(IPOD_MINI2G)
#define USB_FIREWIRE_HANDLING  0
#endif

#define	USB_HAVE_POWER		0
#define	USB_HAVE_STACK		1

#define	USB_ENABLE_STORAGE		1
#define	USB_ENABLE_SERIAL		0
#define	USB_ENABLE_CHARGING_ONLY	0
#define	USB_ENABLE_HID			0

#define USB_MAX_CURRENT 500
/*================================================================*/
#endif
/* end of 0ctr.h */
