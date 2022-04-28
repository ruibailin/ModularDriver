
/*------------------------------------
 * report.c
 * Create:  2021-10-29
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
struct report_lun_data {
    unsigned int lun_list_length;
    unsigned int reserved1;
    unsigned char luns[NUM_DRIVES][8];
}__attribute__ ((packed));

/*================================================================*/

/* end of report.c */
