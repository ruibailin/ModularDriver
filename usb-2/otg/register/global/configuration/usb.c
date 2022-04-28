
/*------------------------------------
 * usb.c
 * Create:  2021-10-26
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#include "0ctr.h"
#include "1imp.h"
/*================================================================*/
/** Core USB Configuration Register */
#define GUSBCFG                         GLOBAL_REG(0x00C)
#define GUSBCFG_toutcal_bitp            0
#define GUSBCFG_toutcal_bits            0x7
#define GUSBCFG_phy_if                  (1 << 3) /** select utmi bus width ? */
#define GUSBCFG_ulpi_utmi_sel           (1 << 4) /** select ulpi:1 or utmi:0 */
#define GUSBCFG_fsintf                  (1 << 5)
#define GUSBCFG_physel                  (1 << 6)
#define GUSBCFG_ddrsel                  (1 << 7)
#define GUSBCFG_srpcap                  (1 << 8)
#define GUSBCFG_hnpcapp                 (1 << 9)
#define GUSBCFG_usbtrdtim_bitp          10
#define GUSBCFG_usbtrdtim_bits          0xf
#define GUSBCFG_nptxfrwnden             (1 << 14)
#define GUSBCFG_phylpwrclksel           (1 << 15)
#define GUSBCFG_otgutmifssel            (1 << 16)
#define GUSBCFG_ulpi_fsls               (1 << 17)
#define GUSBCFG_ulpi_auto_res           (1 << 18)
#define GUSBCFG_ulpi_clk_sus_m          (1 << 19)
#define GUSBCFG_ulpi_ext_vbus_drv       (1 << 20)
#define GUSBCFG_ulpi_int_vbus_indicator (1 << 21)
#define GUSBCFG_term_sel_dl_pulse       (1 << 22)
#define GUSBCFG_force_host_mode         (1 << 29)
#define GUSBCFG_force_device_mode       (1 << 30)
#define GUSBCFG_corrupt_tx_packet       (1 << 31)

/*================================================================*/
void g_usb_init(void);
void g_usb_init()
{
    /* Disable HNP and SRP, not sure it's useful because we already forced dev mode */
    GUSBCFG &= ~(GUSBCFG_srpcap | GUSBCFG_hnpcapp);
}

void g_usb_force_into_device_mode(void);
void g_usb_force_into_device_mode()
{
    GUSBCFG &= ~GUSBCFG_force_host_mode;
    GUSBCFG |= GUSBCFG_force_device_mode;
}
/*================================================================*/
/* end of usb.c */
