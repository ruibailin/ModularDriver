
/*------------------------------------
 * otg.h
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



#ifndef USB_OTG_OTG_H_
#define USB_OTG_OTG_H_
/*================================================================*/
extern int otg_init(void);
extern void otg_exit(void);
extern void otg_enable(bool on);
extern int otg_interrupt(void);
extern int otg_port_speed(void);

extern void otg_enable(bool on);
extern void otg_attach(void);
extern void otg_reconnection(void);
extern void otg_disconnection(void);
/*================================================================*/
extern void otg_reset_endpoints(void);
extern int otg_request_endpoint(int type, int dir);
extern void otg_release_endpoint(int ep);
/*================================================================*/
extern int otg_recv(int ep, void *ptr, int len);
extern int otg_send(int ep, void *ptr, int len);
extern int otg_send_nonblocking(int ep, void *ptr, int len);
extern void otg_cancel_all_transfers(void);
/*================================================================*/
extern void otg_set_test_mode(int mode);
extern void otg_set_address(int address);
extern void otg_stall(int ep, bool stall, bool in);
extern bool otg_is_stalled(int ep, bool in);
/*================================================================*/
#endif
/* end of otg.h */
