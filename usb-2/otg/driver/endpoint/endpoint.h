
/*------------------------------------
 * endpoint.h
 * Create:  2021-10-29
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


#ifndef OTG_DRIVER_ENDPOINT_ENDPOINT_H_
#define OTG_DRIVER_ENDPOINT_ENDPOINT_H_
/*================================================================*/
extern void otg_drv_ep0_prepare_setup_ep0(void);
extern void otg_drv_ep0_handle_ep0_setup(void);
extern void otg_drv_ep0_handle_ep0_complete(bool is_ack);

extern void otg_drv_epn_wakeup_init(void);
extern void otg_drv_epn_check_dir(void);
extern void otg_drv_epn_reset(void);
extern int otg_drv_epn_begin_transfer(int ep, void *ptr, int len, bool dir_in, bool blocking);
extern void otg_drv_epn_cancel_transfer(bool cancel_ep0);
extern int otg_drv_epn_request(int type, int dir);
extern void otg_drv_epn_release(int ep);
extern void otg_drv_epn_handle_in_int(int ep);
extern void otg_drv_epn_handle_out_int(int ep);
extern void otg_drv_epn_handle_ints(void);

/*================================================================*/
#endif
/* end of endpoint.h */
