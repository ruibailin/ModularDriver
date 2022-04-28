
/*------------------------------------
 * transmit.c
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
/** Periodic Transmit FIFO Size Register */
#define GNPTXFSIZ   GLOBAL_REG(0x028)

/** Non-Periodic Transmit FIFO/Queue Status Register */
#define GNPTXSTS    GLOBAL_REG(0x02C)

#define NPT_MAKE_FIFOSIZE_DATA(adr, depth)   (((adr) & 0xffff) | ((depth) << 16))

/*================================================================*/
void g_npt_set_fifo_size(int addr,int depth);
void g_npt_set_fifo_size(int addr,int depth)
{
    /* Setup FIFOs */
    GNPTXFSIZ = NPT_MAKE_FIFOSIZE_DATA(addr, depth);
}
/*================================================================*/

/* end of transmit.c */
