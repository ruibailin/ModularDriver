
/*------------------------------------
 * endpoint0.c
 * Create:  2021-10-27
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
#include "../../../usb/usb.h"
/*================================================================*/
/* state of EP0 (to correctly schedule setup packet enqueing) */
enum EP0STATE {
    /* Setup packet is enqueud, waiting for actual data */
    EP0_WAIT_SETUP = 0,
    /* Waiting for ack (either IN or OUT) */
    EP0_WAIT_ACK = 1,
    /* Ack complete, waiting for data (either IN or OUT)
     * This state is necessary because if both ack and data complete in the
     * same interrupt, we might process data completion before ack completion
     * so we need this bizarre state */
    EP0_WAIT_DATA = 2,
    /* Setup packet complete, waiting for ack and data */
    EP0_WAIT_DATA_ACK = 3,
};

/* state of EP0 */
static enum EP0STATE ep0_state;
/*================================================================*/
void otg_drv_ep0_prepare_setup_ep0(void);
void otg_drv_ep0_prepare_setup_ep0()
{
    panicf("usb-drv: prepare EP0\n\r");
    /* setup DMA */

    d_ep_set_dma_addr_out((u32_t)ep0_setup_pkt);
    d_ep_set_dma_ep0_out();

    /* Enable endpoint, clear nak */
    ep0_state = EP0_WAIT_SETUP;
    d_ep_ctl_enable_ep0_out();
}


/*================================================================*/
void otg_drv_ep0_handle_ep0_setup(void);
void otg_drv_ep0_handle_ep0_setup(void)
{
	u16_t len;
    if (ep0_state != EP0_WAIT_SETUP) {
        panicf("usb-drv: EP0 SETUP while in state %d", ep0_state);
        return;
    }
    /* determine is there is a data phase */
    len = usb_get_ctrlrequest_length(ep0_setup_pkt);
    if (len == 0)
        /* no: wait for ack */
        ep0_state = EP0_WAIT_ACK;
    else
        /* yes: wait ack and data */
        ep0_state = EP0_WAIT_DATA_ACK;
    panicf("usb-drv: EP0 state updated to %d\n\r", ep0_state);
}
/*================================================================*/
void otg_drv_ep0_handle_ep0_complete(bool is_ack);
void otg_drv_ep0_handle_ep0_complete(bool is_ack)
{
    switch (ep0_state)
    {
    case EP0_WAIT_SETUP:
        panicf("usb-drv: EP0 completion while waiting for SETUP");
        otg_drv_ep0_prepare_setup_ep0();
        break;
    case EP0_WAIT_ACK:
        if (is_ack)
            /* everything is done, prepare next setup */
        	otg_drv_ep0_prepare_setup_ep0();
        else
            panicf("usb-drv: EP0 data completion while waiting for ACK");
        break;
    case EP0_WAIT_DATA:
        if (is_ack)
            panicf("usb-drv: EP0 ACK while waiting for data completion");
        else
            /* everything is done, prepare next setup */
        	otg_drv_ep0_prepare_setup_ep0();
        break;
    case EP0_WAIT_DATA_ACK:
        /* update state */
        if (is_ack)
            ep0_state = EP0_WAIT_DATA;
        else
            ep0_state = EP0_WAIT_ACK;
        break;
    default:
        panicf("usb-drv: invalid EP0 state");
    }
    panicf("usb-drv: EP0 state updated to %d\n\r", ep0_state);
}

/*================================================================*/

/* end of endpoint0.c */
