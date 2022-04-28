
/*------------------------------------
 * driver.h
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



#ifndef USB_CORE_DRIVER_DRIVER_H_
#define USB_CORE_DRIVER_DRIVER_H_
/*================================================================*/
extern void core_drv_control_request_handler(void *ctrl);

extern void core_drv_init(void);
extern void core_drv_exit(void);
extern int core_drv_find_if(void);
extern bool core_drv_handle_request(void *ctrl,int interface);
extern void core_drv_enable_driver(int driver, bool enabled);
extern bool core_drv_driver_enabled(int driver);
extern bool core_drv_any_exclusive_storage(void);
extern void core_drv_hotswap_event(int volume, bool inserted);
extern int core_drv_get_serial_function_id(void);
extern int core_drv_set_dt_config(int size,int mps);
extern void core_drv_req_set_config(u16_t value);

#include "./endpoint/endpoint.h"
/*================================================================*/
#endif
/* end of driver.h */
