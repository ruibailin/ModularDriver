
/*------------------------------------
 * token.c
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
/** Device IN Token Sequence Learning Queue Read Register 1 */
#define DTKNQR1     DEVICE_REG(0x20)

/** Device IN Token Sequence Learning Queue Register 2 */
#define DTKNQR2     DEVICE_REG(0x24)

/** Device IN Token Queue Pop register */
#define DTKNQP      DEVICE_REG(0x28)

/** Device IN Token Queue Read Register 3 (RO) */
#define DTKNQR3     DEVICE_REG(0x30)

/** Device IN Token Queue Read Register 4 (RO) */
#define DTKNQR4     DEVICE_REG(0x34)
/*================================================================*/
/* end of token.c */
