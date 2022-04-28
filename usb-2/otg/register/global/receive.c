
/*------------------------------------
 * receive.c
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
/** Receive Status Debug Read Register (Read Only) */
#define GRXSTSR     GLOBAL_REG(0x01C)

/** Receive Status Read /Pop Register (Read Only) */
#define GRXSTSP     GLOBAL_REG(0x020)

/** Receive FIFO Size Register */
#define GRXFSIZ     GLOBAL_REG(0x024)

/*================================================================*/
void g_rx_set_fifo_size(int size);
void g_rx_set_fifo_size(int size)
{
    /* Setup FIFOs */
    GRXFSIZ = size;
}

void g_rx_check_fifo_size(void);
void g_rx_check_fifo_size()
{
    if(GRXFSIZ != DATA_FIFO_DEPTH)
    panicf("usb-drv: wrong data fifo size, %x\r\n", GRXFSIZ);
}
/*================================================================*/

/* end of receive.c */
