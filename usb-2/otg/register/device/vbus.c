
/*------------------------------------
 * vbus.c
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

#include "0ctr.h"
#include "1imp.h"
/*================================================================*/
/* fixme: those registers are not present in registers.h but are in dwc_otgh_regs.h.
 *        the previous registers exists but has a different name :( */
/** Device VBUS discharge register*/
#define DVBUSDIS    DEVICE_REG(0x28)

/** Device VBUS pulse register */
#define DVBUSPULSE  DEVICE_REG(0x2C)

/*================================================================*/
/* end of vbus.c */
