
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

#include "0ctr.h"
#include "1imp.h"
/*================================================================*/
/** Device Control Register */
#define DCTL                DEVICE_REG(0x04)
#define DCTL_rmtwkupsig     (1 << 0) /** Remote Wakeup */
#define DCTL_sftdiscon      (1 << 1) /** Soft Disconnect */
#define DCTL_gnpinnaksts    (1 << 2) /** Global Non-Periodic IN NAK Status */
#define DCTL_goutnaksts     (1 << 3) /** Global OUT NAK Status */
#define DCTL_tstctl_bitp    4 /** Test Control */
#define DCTL_tstctl_bits    0x7
#define DCTL_sgnpinnak      (1 << 7) /** Set Global Non-Periodic IN NAK */
#define DCTL_cgnpinnak      (1 << 8) /** Clear Global Non-Periodic IN NAK */
#define DCTL_sgoutnak       (1 << 9) /** Set Global OUT NAK */
#define DCTL_cgoutnak       (1 << 10) /** Clear Global OUT NAK */
#define DCTL_pwronprgdone   (1 << 11) /** Power on Program Done ? */
/*================================================================*/
void d_ctl_set_power_on(void);
void d_ctl_set_power_on()
{
	//set "power on program done"
	DCTL |= DCTL_pwronprgdone;
}

void d_ctl_reconnect(void);
void d_ctl_reconnect()
{
    /* Reconnect */
    DCTL &= ~DCTL_sftdiscon;
}

void d_ctl_disconnect(void);
void d_ctl_disconnect()
{
    DCTL |= DCTL_sftdiscon;
}

void d_ctl_set_test_mode(int mode);
void d_ctl_set_test_mode(int mode)
{
    /* there is a perfect matching between usb test mode code
     * and the register field value */
    DCTL = (DCTL & ~bitm(DCTL, tstctl)) | (mode << DCTL_tstctl_bitp);
}

void d_ctl_clear_remote_wakeup(void);
void d_ctl_clear_remote_wakeup()
{
    //CON_PRINTF("T\n\r");
    /* Clear the Remote Wakeup Signalling */
    DCTL &= ~DCTL_rmtwkupsig;
}

/*================================================================*/

/* end of control.c */
