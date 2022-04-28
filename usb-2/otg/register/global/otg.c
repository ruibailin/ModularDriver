
/*------------------------------------
 * otg.c
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
/** OTG Control and Status Register */
#define GOTGCTL     GLOBAL_REG(0x000)

/** OTG Interrupt Register */
#define GOTGINT     GLOBAL_REG(0x004)

void g_otg_int_clear(void);
void g_otg_int_clear()
{
    /* Clear any pending otg interrupt */
    GOTGINT = 0xffffffff;
}
/*================================================================*/

/* end of otg.c */
