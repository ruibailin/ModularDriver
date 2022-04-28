
/*------------------------------------
 * verdor.c
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
/** PHY Vendor Control Register */
#define GPVNDCTL    GLOBAL_REG(0x034)

/** User ID Register */
#define GUID        GLOBAL_REG(0x03C)

/** Synopsys ID Register */
#define GSNPSID     GLOBAL_REG(0x040)

/*================================================================*/
long g_id_get_vendor(void);
long g_id_get_vendor()
{
	long id;
	id = GSNPSID;
	return id;
}

/*================================================================*/

/* end of verdor.c */
