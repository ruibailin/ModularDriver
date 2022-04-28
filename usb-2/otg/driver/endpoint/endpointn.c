
/*------------------------------------
 * endpointn.c
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
#include "usb.h"
#include "endpoint.h"
/*================================================================*/
static const u8_t in_epn_list[NUM_IN_EP + 1] = { 0, IN_EP_LIST };
static const u8_t out_epn_list[NUM_OUT_EP + 1] = { 0, OUT_EP_LIST };

/* iterate through each in/out ep except EP0
 * 'i' is the counter, 'ep' is the actual value */
#define FOR_EACH_EP(list, start, i, ep) \
    for(ep = list[i = start]; \
        i < (sizeof(list)/sizeof(*list)); \
        i++, ep = list[i])

#define FOR_EACH_IN_EP_EX(include_ep0, i, ep) \
    FOR_EACH_EP(in_epn_list, (include_ep0) ? 0 : 1, i, ep)

#define FOR_EACH_OUT_EP_EX(include_ep0, i, ep) \
    FOR_EACH_EP(out_epn_list, (include_ep0) ? 0 : 1, i, ep)

#define FOR_EACH_IN_EP(i, ep)           FOR_EACH_IN_EP_EX (false, i, ep)
#define FOR_EACH_IN_EP_AND_EP0(i, ep)   FOR_EACH_IN_EP_EX (true,  i, ep)
#define FOR_EACH_OUT_EP(i, ep)          FOR_EACH_OUT_EP_EX(false, i, ep)
#define FOR_EACH_OUT_EP_AND_EP0(i, ep)  FOR_EACH_OUT_EP_EX(true,  i, ep)

/*================================================================*/
/* store per endpoint, per direction, information */
struct usb_endpoint {
    unsigned int len; /* length of the data buffer */
    i8_t status; /* completion status (0 for success) */
    bool active; /* true is endpoint has been requested (true for EP0) */
    bool wait; /* true if usb thread is blocked on completion */
    bool busy; /* true is a transfer is pending */
    u32_t complete;
};

/* endpoints[epn_num][DIR_IN/DIR_OUT] */
static struct usb_endpoint endpoints[USB_NUM_ENDPOINTS][2];

/*================================================================*/
void otg_drv_epn_wakeup_init(void);
void otg_drv_epn_wakeup_init()
{
    unsigned i, ep;

    FOR_EACH_IN_EP_AND_EP0(i, ep)
        usb_wakeup_init(&endpoints[ep][DIR_IN].complete);
    FOR_EACH_OUT_EP_AND_EP0(i, ep)
        usb_wakeup_init(&endpoints[ep][DIR_OUT].complete);
}

void otg_drv_epn_check_dir(void);
void otg_drv_epn_check_dir()
{
    unsigned i, ep;

    FOR_EACH_IN_EP_AND_EP0(i, ep)
    {
    	g_hwcfg1_check_inep_dir(ep);
    }
    FOR_EACH_OUT_EP_AND_EP0(i, ep)
    {
    	g_hwcfg1_check_outep_dir(ep);
    }
}

void otg_drv_epn_reset(void);
void otg_drv_epn_reset()
{
    unsigned i;
    int ep;
    /* disable all endpoints except EP0 */
    FOR_EACH_IN_EP_AND_EP0(i, ep)
    {
        endpoints[ep][DIR_IN].active = false;
        endpoints[ep][DIR_IN].busy = false;
        endpoints[ep][DIR_IN].status = (i8_t) -1;
        if (endpoints[ep][DIR_IN].wait) {
            usb_wakeup_signal(&endpoints[ep][DIR_IN].complete);
        }
        endpoints[ep][DIR_IN].wait = false;
        d_ep_ctl_enable_in(ep);
    }

    FOR_EACH_OUT_EP_AND_EP0(i, ep)
    {
        endpoints[ep][DIR_OUT].active = false;
        endpoints[ep][DIR_OUT].busy = false;
        endpoints[ep][DIR_OUT].status = (i8_t) -1;
        if (endpoints[ep][DIR_OUT].wait) {
            usb_wakeup_signal(&endpoints[ep][DIR_OUT].complete);
        }
        endpoints[ep][DIR_OUT].wait = false;
        d_ep_ctl_enable_out(ep);
    }
    /* 64 bytes packet size, active endpoint */
    d_ep_ctl_active_ep0();
    /* Setup next chain for IN eps */
    FOR_EACH_IN_EP_AND_EP0(i, ep)
    {
        int next_ep = in_epn_list[(i + 1) % (NUM_IN_EP + 1)];
        d_ep_ctl_setup_nextep(ep,next_ep);
    }
}
/*================================================================*/
int otg_drv_epn_begin_transfer(int ep, void *ptr, int len, bool dir_in, bool blocking);
int otg_drv_epn_begin_transfer(int ep, void *ptr, int len, bool dir_in, bool blocking)
{
    ep = EP_NUM(ep);
    btr_nsecs_delay(10000);

    struct usb_endpoint *endpoint = &endpoints[ep][dir_in];

    if (endpoint->busy)
        panicf("usb-drv: EP%d %s is already busy\n\r", ep, dir_in ? "IN" : "OUT");

    endpoint->busy = true;
    endpoint->len = len;
    endpoint->wait = blocking;
    endpoint->status = (i8_t) -1;

    d_ep_ctl_set_busy(ep,dir_in);
    d_ep_transfer_packet(ep, ptr, len, dir_in);
    d_ep_ctl_set_idle(ep,dir_in);

    if (blocking) {
        //wakeup_wait(&endpoint->complete, BTR_USB_TIMEOUT_BLOCK);
        return endpoint->status;
    }
    return 0;
}

//void cancel_all_transfers(bool cancel_ep0)
void otg_drv_epn_cancel_transfer(bool cancel_ep0);
void otg_drv_epn_cancel_transfer(bool cancel_ep0)
{
    int ep;
    unsigned i;

    FOR_EACH_IN_EP_EX(cancel_ep0, i, ep)
    {
        endpoints[ep][DIR_IN].status = (i8_t) -1;
        endpoints[ep][DIR_IN].wait = false;
        endpoints[ep][DIR_IN].busy = false;
        usb_wakeup_signal(&endpoints[ep][DIR_IN].complete);
        d_ep_ctl_deactive(ep,DIR_IN);
    }
    FOR_EACH_OUT_EP_EX(cancel_ep0, i, ep)
    {
        endpoints[ep][DIR_OUT].status = (i8_t) -1;
        endpoints[ep][DIR_OUT].wait = false;
        endpoints[ep][DIR_OUT].busy = false;
        usb_wakeup_signal(&endpoints[ep][DIR_OUT].complete);
        d_ep_ctl_deactive(ep,DIR_OUT);
    }

    //restore_irq(flags);
}
/*================================================================*/
int otg_drv_epn_request(int type, int dir);
int otg_drv_epn_request(int type, int dir)
{
    int ep, ret = -1;
    unsigned i;
    panicf("usb-drv: request endpoint (type=%d,dir=%s)\n\r", type, dir == USB_DIR_IN ? "IN" : "OUT");

    if (dir == USB_DIR_IN)
        FOR_EACH_IN_EP(i, ep)
        {
            if (endpoints[ep][DIR_IN].active)
                continue;
            endpoints[ep][DIR_IN].active = true;
            ret = ep | dir;
            break;
        }
    else
        FOR_EACH_OUT_EP(i, ep)
        {
            if (endpoints[ep][DIR_OUT].active)
                continue;
            endpoints[ep][DIR_OUT].active = true;
            ret = ep | dir;
            break;
        }

    if (ret == -1) {
        panicf("usb-drv: request failed");
        return -1;
    }

    d_ep_ctl_request(ep,type,dir);

    return ret;
}

void otg_drv_epn_release(int ep);
void otg_drv_epn_release(int ep)
{
    endpoints[EP_NUM(ep)][EP_DIR(ep)].active = false;
}
/*================================================================*/
void otg_drv_epn_handle_in_int(int ep);
void otg_drv_epn_handle_in_int(int ep)
{
    struct usb_endpoint *endpoint = &endpoints[ep][DIR_IN];
    int itype;
    itype = d_ep_in_get_int_type(ep);
    switch(itype){
    case 1:
    	panicf("usb-drv: ahb error on EP%d IN\n\r", ep);
    	break;
    case 2:
    	panicf(" -compl\n\r");
    	if (!endpoint->busy)
    		break;
        endpoint->busy = false;
        endpoint->status = 0;
        /* works even for EP0 */
        int size = d_ep_in_get_xfr_len(ep);
        int transfered = endpoint->len - size;
        panicf("handle_epn_in_int len=%d reg=%ld xfer=%d\n\r", endpoint->len, size, transfered);
        /* handle EP0 state if necessary,
         * this is a ack if length is 0 */
        if (ep == 0)
            otg_drv_ep0_handle_ep0_complete(endpoint->len == 0);
        endpoint->len = size;
        core_drv_ep_transfer_complete(ep, USB_DIR_IN, 0, transfered);
        usb_wakeup_signal(&endpoint->complete);
    	break;
    case 3:
        panicf(" -timeout\n\r");
        panicf("usb-drv: timeout on EP%d IN\n\r", ep);
        if (!endpoint->busy)
        	break;
        endpoint->busy = false;
        endpoint->status = (i8_t) -1;
        /* for safety, act as if no bytes as been transfered */
        endpoint->len = 0;
        core_drv_ep_transfer_complete(ep, USB_DIR_IN, 1, 0);
        usb_wakeup_signal(&endpoint->complete);
    	break;
    default:
    	break;
    }
}

void otg_drv_epn_handle_out_int(int ep);
void otg_drv_epn_handle_out_int(int ep)
{
	struct usb_endpoint *endpoint = &endpoints[ep][DIR_OUT];
	int itype,size;
	u16_t value;
    itype = d_ep_in_get_int_type(ep);
    switch(itype){
    case 1:
    	panicf("usb-drv: ahb error on EP%d OUT\n\r", ep);
    	BTR_USB_CACHE_READ();
    	break;
    case 2:
        panicf(" -compl\n\r");
        panicf("usb-drv: xfer complete on EP%d OUT\n\r", ep);
        if (!endpoint->busy)
        	break;
        panicf(" -busy\n\r");
        endpoint->busy = false;
        endpoint->status = 0;
        /* works even for EP0 */
        size = d_ep_out_get_xfr_len(ep);
        int transfered = endpoint->len - size;
        panicf("len=%d reg=%ld xfer=%d\n\r", endpoint->len,size, transfered);
        /* handle EP0 state if necessary,
         * this is a ack if length is 0 */
        if (ep == 0)
            otg_drv_ep0_handle_ep0_complete(endpoint->len == 0);
        core_drv_ep_transfer_complete(ep, USB_DIR_OUT, 0, transfered);
        usb_wakeup_signal(&endpoint->complete);
    	break;
    case 3:
        panicf(" -setup\n\r");
        panicf("usb-drv: setup on EP%d OUT\n\r", ep);
        if (ep != 0)
            panicf("usb-drv: setup not on EP0, this is impossible\n\r");
        size = d_ep_out_get_xfr_len(ep);
        if (size != 0) {
            panicf("usb-drv: ignore spurious setup (xfersize=%ld)\n\r", size);
            otg_drv_ep0_prepare_setup_ep0();
        } else {
            /* handle EP0 state */
            otg_drv_ep0_handle_ep0_setup();
            /* handle set address */

            /* Set address now */
            if(usb_is_ctrlrequest_set_add(ep0_setup_pkt))
            {
                value = usb_get_ctrlrequest_value(ep0_setup_pkt);
            	d_cfg_set_device_addr(value);
            }
            core_drv_ep_ini_ctrlrequest(ep0_setup_pkt);
        }
    	break;
    default:
    	break;
    }
}

/* valid for DAINT and DAINTMSK, for 0<=ep<=15 */
#define DAINT_IN_EP(i)      (1 << (i))
#define DAINT_OUT_EP(i)     (1 << ((i) + 16))
void otg_drv_epn_handle_ints(void);
void otg_drv_epn_handle_ints()
{

    /* we must read it */
    unsigned long daint;
    unsigned i, ep;

    daint = d_ep_all_get_int();

    FOR_EACH_IN_EP_AND_EP0(i, ep)
        if (daint & DAINT_IN_EP(ep))
            otg_drv_epn_handle_in_int(ep);

    FOR_EACH_OUT_EP_AND_EP0(i, ep)
        if (daint & DAINT_OUT_EP(ep))
            otg_drv_epn_handle_out_int(ep);

    /* write back to clear status */
    d_ep_all_set_int(daint);
}
/*================================================================*/

/* end of endpointn.c */
