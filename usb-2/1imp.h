
/*------------------------------------
 * 1imp.h
 * Create:  2021-10-26
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */



#ifndef USB_1IMP_H_
#define USB_1IMP_H_
/*================================================================*/
#include "../btr_types.h"
#include "../btr_cfg.h"
#include "../btr_stdio.h"
#include "../btr_string.h"
#include "../btr_tmr.h"
#include "direction.h"


#define PACKET_SIZE_ONE_SECTION (512)
#define USB_MAX_CURRENT 500
#define USB_NUM_DRIVERS	1
extern unsigned char *response_data;
#define USB_ENDPOINT_HALT       0   /* IN/OUT will STALL */

#define BTR_USB_MEMCPY btr_asm_memcpy
#define BTR_USB_MEMSET btr_asm_memset

#define panicf(fmt,...)   do{}while(0)
#define BTR_USB_CACHE_WRITE() do{}while(0)
#define BTR_USB_CACHE_READ() do{}while(0)
#define BTR_USB_PRINTF(fmt,...) do{}while(0)

#define USB_BASE		0x0000
#define USB_DEVICE      (USB_BASE + 0x0800)   /** USB Device base address */
#define DEV_REG(offset) (*(volatile unsigned long *)(USB_DEVICE + offset))

#define PACK_DATA(dest, data) \
    do { \
        btr_asm_memcpy(dest, &(data), sizeof(data)); \
        dest += sizeof(data); \
    } while (0)

/*================================================================*/
#endif
/* end of 1imp.h */
