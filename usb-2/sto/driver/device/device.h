
/*------------------------------------
 * device.h
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



#ifndef USB_STO_DRIVER_DEVICE_DEVICE_H_
#define USB_STO_DRIVER_DEVICE_DEVICE_H_
/*================================================================*/
extern void sto_drv_dev_set_eject(int lun,bool eject);
extern bool sto_drv_dev_get_eject(int lun);
extern bool sto_drv_dev_is_present(int lun);
extern void sto_drv_dev_notify_hotswap(int volume);

/*================================================================*/
#endif
/* end of device.h */
