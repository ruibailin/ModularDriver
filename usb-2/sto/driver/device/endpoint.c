
/*------------------------------------
 * endpoint.c
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

#include "../../desc/desc.h"
/*================================================================*/
#define EP_CONTROL 0

static int ep_in, ep_out;
extern unsigned char *response_data;

#define USB_ENDPOINT_XFER_BULK          2

int sto_drv_ep_request_endpoint(void *drv);
int sto_drv_ep_request_endpoint(void *drv)
{
    ep_in = core_drv_ep_request_endpoint(USB_ENDPOINT_XFER_BULK, USB_DIR_IN, drv);

    if (ep_in < 0)
        return -1;

    ep_out = core_drv_ep_request_endpoint(USB_ENDPOINT_XFER_BULK, USB_DIR_OUT, drv);

    if (ep_out < 0) {
    	core_drv_ep_release_endpoint(ep_in);
        return -1;
    }

    return 0;
}

u8_t *sto_drv_ep_get_endpoint_desc(u8_t *dest, int mps);
u8_t *sto_drv_ep_get_endpoint_desc(u8_t *dest, int mps)
{
	dest = sto_desc_ep_get_config(dest,mps,ep_in,ep_out);
	return dest;
}

void sto_drv_epn_stall();
void sto_drv_epn_stall()
{
    d_ep_ctl_stall(ep_in, true, true);
    d_ep_ctl_stall(ep_out, true, false);
}

void sto_drv_epn_send(void *in,int size);
void sto_drv_epn_send(void *in,int size)
{
	otg_send(ep_in,in,size);
}

void sto_drv_epn_send_nb(void *in,int size);
void sto_drv_epn_send_nb(void *in,int size)
{
	otg_send_nonblocking(ep_in,in,size);
}

void sto_drv_epn_recv(void *in,int size);
void sto_drv_epn_recv(void *in,int size)
{
	otg_recv(ep_out,in,size);
}


/*================================================================*/
void sto_drv_ep0_recv_0(void);
void sto_drv_ep0_recv_0()
{
	otg_recv(EP_CONTROL,NULL,0);
}

void sto_drv_ep0_send_0(void);
void sto_drv_ep0_send_0()
{
	otg_send(EP_CONTROL, NULL, 0);
}

void sto_drv_ep0_send_1(void);
void sto_drv_ep0_send_1()
{
    otg_send(EP_CONTROL, response_data, 1);
}

void sto_drv_ep0_send_2(void);
void sto_drv_ep0_send_2()
{
    otg_send(EP_CONTROL, response_data, 2);
}
/*================================================================*/

/* end of endpoint.c */
