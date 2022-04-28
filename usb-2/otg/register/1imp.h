
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



#ifndef OTG_REG_1IMP_H_
#define OTG_REG_1IMP_H_

/*================================================================*/
#define  USB_BASE_ADDR       	0

#define  USB_GLOBAL_ADDR  		(USB_BASE_ADDR + 0x0000)
#define  USB_DEVICE_ADDR       	(USB_BASE_ADDR + 0x0800)   /** USB Device base address */

#define extract(r, f)   ((r >> r##_##f##_bitp) & r##_##f##_bits)

#define bitm(r, f)     	(r##_##f##_bits << r##_##f##_bitp)

#include "../1imp.h"
/*================================================================*/
#endif
/* end of 1imp.h */
