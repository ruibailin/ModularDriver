
/*------------------------------------
 * endpoint.h
 * Create:  2021-11-11
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */



#ifndef USB_CORE_DRIVER_ENDPOINT_H_
#define USB_CORE_DRIVER_ENDPOINT_H_
/*================================================================*/
extern void core_drv_ep_ini_data(void);
extern void core_drv_ep_transfer_complete(int endpoint, int dir, int status, int length);
extern void core_drv_ep_control_request(void* req);
extern void core_drv_ep_release_endpoint(int ep);
extern int core_drv_ep_request_endpoint(int type, int dir, void *driver);
extern bool core_drv_ep_handle_req(u16_t index,void *req);
/*================================================================*/
#endif
/* end of endpoint.h */
