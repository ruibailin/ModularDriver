
/*------------------------------------
 * interface.h
 * Create:  2021-11-13
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */



#ifndef USB_STO_DRIVER_DEVICE_INTERFACE_H_
#define USB_STO_DRIVER_DEVICE_INTERFACE_H_
/*================================================================*/
extern void sto_drv_if_set_interface(int uif);
extern int sto_drv_if_get_interface(void);
extern u8_t *sto_drv_if_get_interface_desc(u8_t *dest);
/*================================================================*/
#endif
/* end of interface.h */
