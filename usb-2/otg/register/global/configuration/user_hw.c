
/*------------------------------------
 * user_hw.c
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
/** User HW Config1 Register */
#define GHWCFG1                 GLOBAL_REG(0x044)
#define GHWCFG1_epdir_bitp(ep)  (2 * (ep))
#define GHWCFG1_epdir_bits      0x3
#define GHWCFG1_EPDIR_BIDIR     0
#define GHWCFG1_EPDIR_IN        1
#define GHWCFG1_EPDIR_OUT       2

/*================================================================*/
void g_hwcfg1_check_inep_dir(int ep);
void g_hwcfg1_check_inep_dir(int ep)
{
    int type;
    type = (GHWCFG1 >> GHWCFG1_epdir_bitp(ep)) & GHWCFG1_epdir_bits;

    if (type != GHWCFG1_EPDIR_BIDIR && type != GHWCFG1_EPDIR_IN)
        panicf("usb-drv: EP%d is no IN or BIDIR", ep);
}

void g_hwcfg1_check_outep_dir(int ep);
void g_hwcfg1_check_outep_dir(int ep)
{
    int type;
    type = (GHWCFG1 >> GHWCFG1_epdir_bitp(ep)) & GHWCFG1_epdir_bits;
    if (type != GHWCFG1_EPDIR_BIDIR && type != GHWCFG1_EPDIR_OUT)
        panicf("usb-drv: EP%d is no OUT or BIDIR", ep);
}

/*================================================================*/
/** User HW Config2 Register */
#define GHWCFG2                     GLOBAL_REG(0x048)
#define GHWCFG2_arch_bitp           3 /** Architecture */
#define GHWCFG2_arch_bits           0x3
#define GHWCFG2_hs_phy_type_bitp    6 /** High speed PHY type */
#define GHWCFG2_hs_phy_type_bits    0x3
#define GHWCFG2_fs_phy_type_bitp    8 /** Full speed PHY type */
#define GHWCFG2_fs_phy_type_bits    0x3
#define GHWCFG2_num_ep_bitp         10 /** Number of endpoints */
#define GHWCFG2_num_ep_bits         0xf
#define GHWCFG2_dyn_fifo            (1 << 19) /** Dynamic FIFO */
/* For GHWCFG2_HS_PHY_TYPE and GHWCFG2_FS_PHY_TYPE */
#define GHWCFG2_PHY_TYPE_UNSUPPORTED        0
#define GHWCFG2_PHY_TYPE_UTMI               1
#define GHWCFG2_ARCH_INTERNAL_DMA           2
/*================================================================*/
void g_hwcfg2_check_phy(void);
void g_hwcfg2_check_phy()
{
    if (extract(GHWCFG2, arch) != GHWCFG2_ARCH_INTERNAL_DMA)
        panicf("usb-drv: wrong architecture (%ld)", extract(GHWCFG2, arch));
    if (extract(GHWCFG2, hs_phy_type) != GHWCFG2_PHY_TYPE_UTMI)
        panicf("usb-drv: wrong HS phy type (%ld)", extract(GHWCFG2, hs_phy_type));
    if (extract(GHWCFG2, fs_phy_type) != GHWCFG2_PHY_TYPE_UNSUPPORTED)
        panicf("usb-drv: wrong FS phy type (%ld)", extract(GHWCFG2, fs_phy_type));
}

void g_hwcfg2_check_dyn_fifo(void);
void g_hwcfg2_check_dyn_fifo()
{
    if(!(GHWCFG2 & GHWCFG2_dyn_fifo))
    panicf("usb-drv: no dynamic fifo %x\r\n", GHWCFG2);
}

void g_hwcfg2_check_ep_num(void);
void g_hwcfg2_check_ep_num()
{
    if (USB_NUM_ENDPOINTS != extract(GHWCFG2, num_ep))
        panicf("usb-drv: wrong endpoint number, %x", (GHWCFG2 >> 10) & (0XF));
}

/*================================================================*/
/** User HW Config3 Register */
#define GHWCFG3                 GLOBAL_REG(0x04C)
#define GHWCFG3_dfifo_len_bitp  16 /** Total fifo size */
#define GHWCFG3_dfifo_len_bits  0xffff

/*================================================================*/
/** User HW Config4 Register */
#define GHWCFG4                             GLOBAL_REG(0x050)
#define GHWCFG4_utmi_phy_data_width_bitp    14 /** UTMI+ data bus width */
#define GHWCFG4_utmi_phy_data_width_bits    0x3
#define GHWCFG4_ded_fifo_en                 (1 << 25) /** Dedicated Tx FIFOs */
#define GHWCFG4_num_in_ep_bitp              26 /** Number of IN endpoints */
#define GHWCFG4_num_in_ep_bits              0xf
/*================================================================*/
void g_hwcfg4_check_fifo(void);
void g_hwcfg4_check_fifo()
{
    if (extract(GHWCFG4, utmi_phy_data_width) != 0x2)
        panicf("usb-drv: wrong utmi data width (0x%x)", (GHWCFG4 >> 14) & (3)/*extract(GHWCFG4, utmi_phy_data_width)*/);
    if (!(GHWCFG4 & GHWCFG4_ded_fifo_en)) /* it seems to be multiple tx fifo support */
        panicf("usb-drv: no multiple tx fifo");
}
/*================================================================*/
/* end of user_hw.c */
