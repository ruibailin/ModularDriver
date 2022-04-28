
/*------------------------------------
 * 1imp.h
 * Create:  2021-10-29
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */



#ifndef USB_STORAGE_1IMP_H_
#define USB_STORAGE_1IMP_H_
/*================================================================*/
#include "../1imp.h"
#include "../otg/otg.h"
#include "../usb/usb.h"
#define NUM_DRIVES	2

#define RAMDISK_SIZE 0x10000

#ifndef SECTOR_SIZE
#define SECTOR_SIZE 512
#endif

/* These defaults allow the operation */
#ifndef USBSTOR_READ_SECTORS_FILTER
#define USBSTOR_READ_SECTORS_FILTER() ({ 0; })
#endif

#ifndef USBSTOR_WRITE_SECTORS_FILTER
#define USBSTOR_WRITE_SECTORS_FILTER() ({ 0; })
#endif

/* the ARC driver currently supports up to 64k USB transfers. This is
 * enough for efficient mass storage support, as commonly host OSes
 * don't do larger SCSI transfers anyway, so larger USB transfers
 * wouldn't buy us anything.
 * Due to being the double-buffering system used, using a smaller write buffer
 * ends up being more efficient. Measurements have shown that 24k to 28k is
 * optimal, except for sd devices that apparently don't gain anything from
 * double-buffering
 */
#if 0
#ifdef USB_READ_BUFFER_SIZE
#define READ_BUFFER_SIZE USB_READ_BUFFER_SIZE
#else
#if CONFIG_CPU == AS3525
/* We'd need to implement multidescriptor dma for sizes >65535 */
#define READ_BUFFER_SIZE (1024*63)
#else
#define READ_BUFFER_SIZE (1024*64)
#endif /* CONFIG_CPU == AS3525 */
#endif /* USB_READ_BUFFER_SIZE */
#endif //if 0

#define READ_BUFFER_SIZE (512)

#define MAX_CBW_SIZE 64
#define USB_WRITE_BUFFER_SIZE (512)
#ifdef USB_WRITE_BUFFER_SIZE
#define WRITE_BUFFER_SIZE USB_WRITE_BUFFER_SIZE
#else
#if (CONFIG_STORAGE & STORAGE_SD)
#if CONFIG_CPU == AS3525
/* We'd need to implement multidescriptor dma for sizes >65535 */
#define WRITE_BUFFER_SIZE (1024*63)
#else
#define WRITE_BUFFER_SIZE (1024*64)
#endif /* CONFIG_CPU == AS3525 */
#else
#define WRITE_BUFFER_SIZE (1024*24)
#endif /* (CONFIG_STORAGE & STORAGE_SD) */
#endif /* USB_WRITE_BUFFER_SIZE */

#define ALLOCATE_BUFFER_SIZE (2*MAX(READ_BUFFER_SIZE,WRITE_BUFFER_SIZE))

#define IF_MD(x)
#define IF_MD2(x,y)
#define IF_MD_NONVOID(x) void
/*================================================================*/
#endif
/* end of 1imp.h */
