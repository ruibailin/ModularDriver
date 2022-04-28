
/*------------------------------------
 * endpoint.h
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


#ifndef USB_STO_DRIVER_DEVICE_ENDPOINT_H_
#define USB_STO_DRIVER_DEVICE_ENDPOINT_H_
/*================================================================*/
extern int sto_drv_ep_request_endpoint(void *drv);
extern u8_t *sto_drv_ep_get_endpoint_desc(u8_t *dest, int mps);
extern void sto_drv_epn_stall(void);
extern void sto_drv_epn_send(void *in,int size);
extern void sto_drv_epn_send_nb(void *in,int size);
extern void sto_drv_epn_recv(void *in,int size);
extern void sto_drv_ep0_recv_0(void);
extern void sto_drv_ep0_send_0(void);
extern void sto_drv_ep0_send_1(void);
extern void sto_drv_ep0_send_2(void);
/*================================================================*/
#endif
/* end of endpoint.h */
