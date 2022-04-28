
/*------------------------------------
 * reset.c
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
/** Core Reset Register */
#define GRSTCTL                 GLOBAL_REG(0x010)
#define GRSTCTL_csftrst         (1 << 0) /** Core soft reset */
#define GRSTCTL_hsftrst         (1 << 1) /** Hclk soft reset */
#define GRSTCTL_intknqflsh      (1 << 3) /** In Token Sequence Learning Queue Flush */
#define GRSTCTL_rxfflsh_flush   (1 << 4) /** RxFIFO Flush */
#define GRSTCTL_txfflsh_flush   (1 << 5) /** TxFIFO Flush */
#define GRSTCTL_txfnum_bitp     6 /** TxFIFO Number */
#define GRSTCTL_txfnum_bits     0x1f
#define GRSTCTL_ahbidle         (1 << 31) /** AHB idle state*/

/*================================================================*/
void g_rst_soft_reset_core(void);
void g_rst_soft_reset_core()
{
	GRSTCTL |= GRSTCTL_csftrst;
}

void g_rst_soft_reset_hclk(void);
void g_rst_soft_reset_hclk()
{
	GRSTCTL |= GRSTCTL_hsftrst;
}

void g_rst_flush_and_reset(void);
void g_rst_flush_and_reset()
{
	GRSTCTL |= 0x3f;
}

void g_rst_flush_learning_queue(void);
void g_rst_flush_learning_queue()
{
    /* Flush the Learning Queue */
    GRSTCTL = GRSTCTL_intknqflsh;
}

void g_rst_flush_tx_fifos(int nums);
void g_rst_flush_tx_fifos(int nums)
{
    unsigned int i = 0;

    GRSTCTL = (nums << GRSTCTL_txfnum_bitp) | GRSTCTL_txfflsh_flush;
    while ((GRSTCTL & GRSTCTL_txfflsh_flush) && (i < 0x300))
        i++;
    if (GRSTCTL & GRSTCTL_txfflsh_flush)
        panicf("usb-drv: hang of flush tx fifos (%x)", nums);
}
/*================================================================*/

/* end of reset.c */
