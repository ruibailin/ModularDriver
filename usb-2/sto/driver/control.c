
/*------------------------------------
 * control.c
 * Create:  2021-11-05
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
#include "tb.h"
#include "state.h"
#include "./device/device.h"

extern enum STO_STATE_E sto_state ;
/*================================================================*/
void sto_drv_ctrl_get_max_lun();
void sto_drv_ctrl_get_max_lun()
{
	//*tb.max_lun = storage_num_drives() - 1;
#ifdef USB_HIDE_FIRST_DRIVE
	sto_tb.max_lun --;
#endif
	logf("ums: getmaxlun");
	sto_drv_ep0_recv_0(); /* ack */

	response_data[0] = 0;
	sto_drv_ep0_send_1();
}

void sto_drv_ctrl_reset_request();
void sto_drv_ctrl_reset_request()
{
    logf("ums: bulk reset");
    sto_state = WAITING_FOR_COMMAND;
    /* UMS BOT 3.1 says The device shall preserve the value of its bulk
     data toggle bits and endpoint STALL conditions despite
     the Bulk-Only Mass Storage Reset. */
#if 0
    sto_drv_reset_endpoint(ep_in, false);
    sto_drv_reset_endpoint(ep_out, true);
#endif
	sto_drv_ep0_recv_0(); /* ack */
}

/*================================================================*/

/* end of control.c */
