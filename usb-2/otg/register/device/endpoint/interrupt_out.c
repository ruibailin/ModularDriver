
/*------------------------------------
 * out_interrupt.c
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
/** Device OUT Endpoint Common Interrupt Mask Register */
#define DOEPMSK                 DEVICE_REG(0x14)
/* the following apply to DOEPMSK and DOEPINT */
#define DOEPINT_xfercompl       (1 << 0) /** Transfer complete */
#define DOEPINT_epdisabled      (1 << 1) /** Endpoint disabled */
#define DOEPINT_ahberr          (1 << 2) /** AHB error */
#define DOEPINT_setup           (1 << 3) /** Setup Phase Done (control EPs)*/

/** Device OUT Endpoint (ep) Frame number Register */
#define DOEPFN(ep)      DEVICE_REG(0x300 + (ep) * 0x20 + 0x4)
/** Device Endpoint (ep) Interrupt Register */
#define DOEPINT(ep)     DEVICE_REG(0x300 + (ep) * 0x20 + 0x8)

/*================================================================*/
void d_ep_out_ini_int_mask(void);
void d_ep_out_ini_int_mask()
{
    /* Setup interrupt masks for endpoints */
    /* Setup interrupt masks */
    DOEPMSK = DOEPINT_setup | DOEPINT_xfercompl | DOEPINT_ahberr;
}

int d_ep_out_get_int_type(int ep);
int d_ep_out_get_int_type(int ep)
{
	unsigned long sts;
	int ret;
	ret = 0;
	sts = DOEPINT(ep);
    if (sts & DOEPINT_ahberr)
    	ret = 1;
    if (sts & DOEPINT_xfercompl)
    	ret = 2;
    if (sts &  DOEPINT_setup)
    	ret = 3;

    /* clear interrupts */
    DOEPINT(ep) = sts;
    return ret;
}
/*================================================================*/

/* end of out_interrupt.c */
