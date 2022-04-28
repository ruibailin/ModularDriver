
/*------------------------------------
 * ahb.c
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
/** Core AHB Configuration Register */
#define GAHBCFG                         GLOBAL_REG(0x008)
#define GAHBCFG_glblintrmsk             (1 << 0) /** Global interrupt mask */
#define GAHBCFG_hburstlen_bitp          1
#define GAHBCFG_hburstlen_bits          0xf
#define GAHBCFG_INT_DMA_BURST_SINGLE    0
#define GAHBCFG_INT_DMA_BURST_INCR      1 /** note: the linux patch has several other value, this is one picked for internal dma */
#define GAHBCFG_INT_DMA_BURST_INCR4     3
#define GAHBCFG_INT_DMA_BURST_INCR8     5
#define GAHBCFG_INT_DMA_BURST_INCR16    7
#define GAHBCFG_dma_enable              (1 << 5) /** Enable DMA */

/*================================================================*/
void g_ahb_init(void);
void g_ahb_init()
{
    /* Select UTMI+ 16 */
    //GUSBCFG |= GUSBCFG_phy_if;
    //GUSBCFG = (GUSBCFG & ~bitm(GUSBCFG, toutcal)) | 7 << GUSBCFG_toutcal_bitp;
    /* fixme: the current code is for internal DMA only, the clip+ architecture
     *        define the internal DMA model */
    /* Set burstlen and enable DMA*/
    GAHBCFG = (GAHBCFG_INT_DMA_BURST_INCR8 << GAHBCFG_hburstlen_bitp) | (GAHBCFG_dma_enable) | (GAHBCFG_glblintrmsk);

}

void g_ahb_enable_global(void);
void g_ahb_enable_global()
{
    //   VIC_INT_ENABLE = INTERRUPT_USB;
    GAHBCFG |= GAHBCFG_glblintrmsk;
}


void g_ahb_disable_global(void);
void g_ahb_disable_global()
{
    GAHBCFG &= ~GAHBCFG_glblintrmsk;
    // VIC_INT_EN_CLEAR = INTERRUPT_USB;
}

/*================================================================*/

/* end of ahb.c */
