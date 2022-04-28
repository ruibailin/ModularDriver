
/*------------------------------------
 * control.c
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
#define GCGCTL         	GLOBAL_REG(0xE00) /** Clock Gating Control Register */

void g_cg_init(void);
void g_cg_init()
{
    /* Restart the phy clock */
//    PCGCCTL = 0;
	GCGCTL = 0;
}

void g_cg_clear_stop_pclk()
{
//	 PCGCCTL &= ~0x1;
	GCGCTL &= ~0x1;
}
/*================================================================*/

/* end of control.c */
