
/*------------------------------------
 * device.h
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

#ifndef DEVICE_DEVICE_H_
#define DEVICE_DEVICE_H_
/*================================================================*/
//device endpoint control  register
extern void d_ep_ctl_enable_ep0_out(void);
extern void d_ep_ctl_active_ep0(void);
extern void d_ep_ctl_enable_in(int ep);
extern void d_ep_ctl_enable_out(int ep);
extern void d_ep_ctl_setup_nextep(int ep,int next_ep);
extern void d_ep_ctl_set_idle(int ep,bool dir_in);
extern void d_ep_ctl_set_busy(int ep,bool dir_in);
extern void d_ep_ctl_deactive(int ep,bool dir_in);
extern int d_ep_ctl_get_type(int ep,bool dir_in);
extern void d_ep_ctl_stall(int ep, int stall, bool dir_in);
extern bool d_ep_ctl_is_stalled(int ep, bool dir_in);
extern void d_ep_ctl_request(int ep,int type,int dir);
//device endpoint interrupt  register
extern void d_ep_in_ini_int_mask(void);
extern int d_ep_in_get_int_type(int ep);
extern void d_ep_out_ini_int_mask(void);
extern int d_ep_out_get_int_type(int ep);
extern void d_ep_all_ini_int_mask(void);
extern long d_ep_all_get_int(void);
extern void d_ep_all_set_int(long state);
//device endpoint transfer  register
extern void d_ep_set_dma_addr_out(int paddr);
extern void d_ep_set_dma_ep0_out(void);
extern int d_ep_in_get_xfr_len(int ep);
extern int d_ep_out_get_xfr_len(int ep);
extern void d_ep_transfer_packet(int ep, void *ptr, int len, bool dir_in);
//device configuration register
extern void d_cfg_reset_device(void);
extern void d_cfg_ini_phy_speed(void);
extern void d_cfg_set_phy_speed(void);
extern void d_cfg_reset_device_addr(void);
extern void d_cfg_set_device_addr(int value);
//device control register
extern void d_ctl_set_power_on(void);
extern void d_ctl_reconnect(void);
extern void d_ctl_disconnect(void);
extern void d_ctl_set_test_mode(int mode);
extern void d_ctl_clear_remote_wakeup(void);
//device status register
extern int d_sts_get_port_speed_type(void);
extern int d_sts_get_mps_by_type(int type);
/*================================================================*/
#endif
/* end of device.h */
