
/*------------------------------------
 * interrupt.c
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
/** Device All Endpoints Interrupt Register */
#define DAINT               DEVICE_REG(0x18)
/* valid for DAINT and DAINTMSK, for 0<=ep<=15 */
#define DAINT_IN_EP(i)      (1 << (i))
#define DAINT_OUT_EP(i)     (1 << ((i) + 16))

/** Device Endpoints Interrupt Mask Register */
#define DAINTMSK    DEVICE_REG(0x1C)
/*================================================================*/
void d_ep_all_ini_int_mask(void);
void d_ep_all_ini_int_mask()
{
	DAINTMSK = 0xffffffff;
}

long d_ep_all_get_int(void);
long d_ep_all_get_int()
{
	long state;

	state = DAINT;
	return state;
}

void d_ep_all_set_int(long state);
void d_ep_all_set_int(long state)
{
	DAINT = state;
}
/*================================================================*/

/* end of interrupt.c */
