
/*---------------------------
 * hw_cve_err.c
 *  Created on: 2017年7月13日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *
 *
 *
 *
 *
 *---------------------------
 */

#include "c_share.h"

/**************************************************/
int hw_check_cve_err(void);
int hw_check_cve_err(void)
{
	DWORD	state;

	top_get_irq_state(&state);
	state &= 0x00000FFF;

	return(state);
}
/**************************************************/
void hw_clear_cve_err(void);
void hw_clear_cve_err(void)
{
	 top_set_clr_irq_state(0x00000002);
}


/* end of hw_cve_err.c */
