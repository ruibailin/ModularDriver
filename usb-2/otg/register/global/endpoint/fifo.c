
/*------------------------------------
 * fifo.c
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

#include "../0ctr.h"
#include "../1imp.h"
/*================================================================*/
/* 1<=ep<=15, don't use ep=0 !!! */
/** Device IN Endpoint Transmit FIFO (ep) Size Register */
#define DIEPTXFSIZ(ep)  GLOBAL_REG(0x100 + 4 * (ep))

/** Build the content of a FIFO size register like DIEPTXFSIZ(i) and GNPTXFSIZ*/
#define TXF_MAKE_FIFOSIZE_DATA(adr, depth)   (((adr) & 0xffff) | ((depth) << 16))
/** Retrieve fifo size for such registers */
#define TXF_GET_FIFOSIZE_DEPTH(data)    ((data) >> 16)
/** Retrieve fifo start address for such registers */
#define TXF_GET_FIFOSIZE_START_ADR(data)    ((data) & 0xffff)
/*================================================================*/

/*================================================================*/

/* end of fifo.c */
