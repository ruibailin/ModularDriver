
/*------------------------------------
 * core.h
 * Create:  2021-11-17
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


#ifndef USB_CORE_CORE_H_
#define USB_CORE_CORE_H_
/*================================================================*/
extern void core_data_reset(void);
extern void core_init(void);
extern void core_exit(void);

#include "./desc/desc.h"
#include "./driver/driver.h"
/*================================================================*/
#endif
/* end of core.h */
