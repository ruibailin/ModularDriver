
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
#define GPCTL         	GLOBAL_REG(0xE00) /** Power control Register */
/*================================================================*/
void g_p_clear_clamp(void);
void g_p_clear_clamp()
{
//clear "power clamp"
//	PCGCCTL &= ~0x4;
	GPCTL &= ~0x4;
}

void g_p_clear_reset(void);
void g_p_clear_reset()
{
//clear "reset power down module"
//	PCGCCTL &= ~0x8;
	GPCTL &= ~0x8;
}
/*================================================================*/

/* end of control.c */
