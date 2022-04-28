
/*------------------------------------
 * in_interrupt.c
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
/** Device IN Endpoint Common Interrupt Mask Register */
#define DIEPMSK                 DEVICE_REG(0x10)
/* the following apply to DIEPMSK and DIEPINT */
#define DIEPINT_xfercompl       (1 << 0) /** Transfer complete */
#define DIEPINT_epdisabled      (1 << 1) /** Endpoint disabled */
#define DIEPINT_ahberr          (1 << 2) /** AHB error */
#define DIEPINT_timeout         (1 << 3) /** Timeout handshake (non-iso TX) */
#define DIEPINT_intktxfemp      (1 << 4) /** IN token received with tx fifo empty */
#define DIEPINT_intknepmis      (1 << 5) /** IN token received with ep mismatch */
#define DIEPINT_inepnakeff      (1 << 6) /** IN endpoint NAK effective */
#define DIEPINT_emptyintr       (1 << 7) /** linux doc broken on this, empty fifo ? */
#define DIEPINT_txfifoundrn     (1 << 8) /** linux doc void on this, tx fifo underrun ? */

/** Device IN Endpoint (ep) Interrupt Register */
#define DIEPINT(ep)     DEVICE_REG(0x100 + (ep) * 0x20 + 0x8)
/*================================================================*/
void d_ep_in_ini_int_mask(void);
void d_ep_in_ini_int_mask()
{
	DIEPMSK = DIEPINT_xfercompl | DIEPINT_timeout | DIEPINT_ahberr;
}

int d_ep_in_get_int_type(int ep);
int d_ep_in_get_int_type(int ep)
{
	unsigned long sts;
	int ret;
	ret = 0;
	sts = DIEPINT(ep);
    if (sts & DIEPINT_ahberr)
    	ret = 1;
    if (sts & DIEPINT_xfercompl)
    	ret = 2;
    if (sts & DIEPINT_timeout)
    	ret = 3;

    /* clear interrupts */
    DIEPINT(ep) = sts;
    return ret;
}

/*================================================================*/

/* end of in_interrupt.c */
