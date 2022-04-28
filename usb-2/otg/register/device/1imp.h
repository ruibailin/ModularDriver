
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



#ifndef REG_DEVICE_1IMP_H_
#define REG_DEVICE_1IMP_H_
/*================================================================*/
#include "../1imp.h"
/**
 * Device Registers Base Addresses
 */
#define DEVICE_REG(offset) (*(volatile unsigned int *)(USB_DEVICE_ADDR + offset))
/*================================================================*/
#endif
/* end of 1imp.h */
