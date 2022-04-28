
/*------------------------------------
 * wakeup.c
 * Create:  2021-10-30
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


#include "../1imp.h"
/*================================================================*/
void usb_wakeup_init(u32_t *complete);
void usb_wakeup_init(u32_t *complete)
{
    *complete = 0;
}

void usb_wakeup_signal(u32_t *complete);
void usb_wakeup_signal(u32_t *complete)
{
    if (complete)
        *complete = true;
}

/*================================================================*/

/* end of wakeup.c */
