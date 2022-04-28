
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



#ifndef REG_GLOBAL_1IMP_H_
#define REG_GLOBAL_1IMP_H_
/*================================================================*/
#include "../1imp.h"
#define GLOBAL_REG(offset) (*(volatile unsigned int *)(USB_GLOBAL_ADDR + offset))

#define DATA_FIFO_DEPTH	512

#include "../device/device.h"
#include "../global/global.h"
/*================================================================*/
#endif
/* end of 1imp.h */
