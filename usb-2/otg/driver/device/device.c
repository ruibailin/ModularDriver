
/*------------------------------------
 * device.c
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

#include "../0ctr.h"
#include "../1imp.h"
/*================================================================*/
#include "../endpoint/endpoint.h"
static void device_check_user_hardware(void);
static void device_check_user_hardware()
{
    /* Check hardware capabilities */
    g_hwcfg2_check_phy();
    g_hwcfg4_check_fifo();
#if USE_CUSTOM_FIFO_LAYOUT
    g_hwcfg2_check_dyn_fifo();
    g_rx_check_fifo_size();
#endif /* USE_CUSTOM_FIFO_LAYOUT */
    g_hwcfg2_check_ep_num();
    otg_drv_epn_check_dir();
}

static void device_ini_fifo_size(void);
static void device_ini_fifo_size()
{
    g_rx_set_fifo_size(512);
    g_npt_set_fifo_size(512,512);
}

static void device_ini_int_mask(void);
static void device_ini_int_mask()
{
    d_ep_out_ini_int_mask();
    d_ep_in_ini_int_mask();
    d_ep_all_ini_int_mask();
}

static void device_config_interrupts(void);
static void device_config_interrupts(void)
{
	g_int_clear_all();
    g_otg_int_clear();
    g_int_enable_all();
}
/*================================================================*/
void otg_drv_dev_init(void);
void otg_drv_dev_init(void)
{
    g_cg_init();
    d_cfg_ini_phy_speed();

    device_check_user_hardware();
    device_ini_fifo_size();
    device_ini_int_mask();

    otg_drv_epn_reset();
    otg_drv_ep0_prepare_setup_ep0();
    /* enable USB interrupts */
    device_config_interrupts();
}
/*================================================================*/

/* end of device.c */
