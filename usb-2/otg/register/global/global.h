
/*------------------------------------
 * global.h
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


#ifndef GLOBAL_GLOBAL_H_
#define GLOBAL_GLOBAL_H_
/*================================================================*/
//global clock gate register
extern void g_cg_init(void);
extern void g_cg_clear_stop_pclk(void);
//global Core AHB Configuration Register
extern void g_ahb_init(void);
extern void g_ahb_enable_global(void);
extern void g_ahb_disable_global(void);
//global Core USB Configuration Register
extern void g_usb_init(void);
extern void g_usb_force_into_device_mode(void);
//User HW Config1 Register
extern void g_hwcfg1_check_inep_dir(int ep);
extern void g_hwcfg1_check_outep_dir(int ep);
extern void g_hwcfg2_check_phy(void);
extern void g_hwcfg2_check_dyn_fifo(void);
extern void g_hwcfg2_check_ep_num(void);
extern void g_hwcfg4_check_fifo(void);
//Global power register
extern void g_p_clear_clamp(void);
extern void g_p_clear_reset(void);
//Global interrupt register
extern int g_int_get_type(void);
extern void g_int_enable_all(void);
extern void g_int_clear_all(void);
/**Global OTG Interrupt Register */
extern void g_otg_int_clear(void);
//Global Receive status, FIFO Size etc Register
extern void g_rx_set_fifo_size(int size);
extern void g_rx_check_fifo_size(void);
//Global Core Reset Register
extern void g_rst_soft_reset_core(void);
extern void g_rst_soft_reset_hclk(void);
extern void g_rst_flush_and_reset(void);
extern void g_rst_flush_learning_queue(void);
extern void g_rst_flush_tx_fifos(int nums);
//Global Transmit FIFO Size Register
extern void g_npt_set_fifo_size(int addr,int depth);
//Global Vendor ID Register
extern long g_id_get_vendor(void);
/*================================================================*/
#endif
/* end of global.h */
