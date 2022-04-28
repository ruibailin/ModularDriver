
/*------------------------------------
 * endpoint.c
 * Create:  2021-10-23
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

#include "../../../otg/driver/endpoint/endpoint.h"
#include "../class.h"

#define USB_ENDPOINT_HALT       		0   	/* IN/OUT will STALL */

#define USB_ENDPOINT_NUMBER_MASK        0x0f    /* in bEndpointAddress */
#define USB_ENDPOINT_DIR_MASK           0x80

#define USB_ENDPOINT_XFERTYPE_MASK      0x03    /* in bmAttributes */
#define USB_ENDPOINT_XFER_CONTROL       0
#define USB_ENDPOINT_XFER_ISOC          1
#define USB_ENDPOINT_XFER_BULK          2
#define USB_ENDPOINT_XFER_INT           3
#define USB_ENDPOINT_MAX_ADJUSTABLE     0x80


#define EP_CONTROL 0
#define EP_DIR(ep) (((ep) & USB_ENDPOINT_DIR_MASK) ? DIR_IN : DIR_OUT)
#define EP_NUM(ep) ((ep) & USB_ENDPOINT_NUMBER_MASK)

/*================================================================*/
typedef void (*completion_handler_t)(int ep, int dir, int status, int length);
typedef BOOL (*control_handler_t)(void* req, unsigned char* dest);


struct usb_transfer_completion_event_data {
    unsigned char endpoint;
    int dir;
    int status;
    int length;
    void* data;
};

static struct {
    completion_handler_t completion_handler[2];
    control_handler_t control_handler[2];
    struct usb_transfer_completion_event_data completion_event[2];
} ep_data[USB_NUM_ENDPOINTS];
/*================================================================*/
enum USB_EVENT{
    USB_EXTRACTED = 0, /* Event */
    USB_INSERTED, /* Event */
    USB_POWER, /* Event */
    USB_SCREENDUMP, /* State */
    USB_UNPOWERED, /* Event */
    USB_REENABLE, /* Event */
    USB_TRANSFER_COMPLETION, /* Event */
    USB_REQUEST_REBOOT, /* Event */
    USB_QUIT, /* Event */
};
#define intptr_t    long
struct queue_event {
    enum USB_EVENT id;
    intptr_t data;
};

/*================================================================*/
static void usb_core_handle_transfer_completion(struct usb_transfer_completion_event_data* event) {
    completion_handler_t handler;
    int ep = (int) (event->endpoint);
    BTR_USB_PRINTF("usb_core_handle_transfer_completion ep=%d\n\r", ep);
    switch (ep) {
    case EP_CONTROL:
        // BTR_USB_PRINTF("ctrl handled %ld" ,current_tick);
        core_drv_control_request_handler((struct usb_ctrlrequest*) event->data);
        break;
    default:
        handler = ep_data[ep].completion_handler[EP_DIR(event->dir)];
        if (handler != NULL)
            handler(ep, event->dir, event->status, event->length);
        break;
    }
}

static void usb_thread(struct queue_event ev);
static void usb_thread(struct queue_event ev) {
    //int num_acks_to_expect = 0;
    //long last_broadcast_tick = current_tick;
    //struct queue_event ev;

    //while(1)
    {
        BTR_USB_PRINTF("usb_thread: ev.id[%d]\n\r", ev.id);
        //queue_wait(&usb_queue, &ev);
        switch (ev.id) {
        /*** Main USB thread duties ***/

#ifdef HAVE_USBSTACK
        case USB_TRANSFER_COMPLETION:
            usb_core_handle_transfer_completion((struct usb_transfer_completion_event_data*) ev.data);
            break;
#endif /* HAVE_USBSTACK */

        case USB_INSERTED:

            break;
            /* USB_INSERTED: */

            //case SYS_USB_CONNECTED_ACK:
            //break;
            /* SYS_USB_CONNECTED_ACK */

#ifdef USB_DELAYED_INSERT
            /* In this case, these events handle cable insertion. USB driver or
             core determines USB_INSERTED. */
            case USB_POWERED:
            break;
            /* USB_POWERED: */

            case USB_UNPOWERED:
            if(usb_state == USB_POWERED)
            usb_enable(false);
            /* Fall-through - other legal states can be USB_INSERTED or
             USB_SCREENDUMP */
#endif /* USB_DELAYED_INSERT */
        case USB_EXTRACTED:
            break;
            /* USB_UNPOWERED: USB_EXTRACTED: */

            /*** Miscellaneous USB thread duties ***/

            /* HOTSWAP */
#if USB_HAVE_HOTSWAP
            case SYS_HOTSWAP_INSERTED:
            case SYS_HOTSWAP_EXTRACTED:
#if (CONFIG_STORAGE & STORAGE_MMC)
            case USB_REENABLE:
#endif
            usb_handle_hotswap(ev.id);
#endif

            /* FIREWIRE */
#if USB_FIREWIRE_HANDLING
            case USB_REQUEST_REBOOT:
            if(usb_reboot_button())
            usb_try_reboot();
            break;
#endif

            /* CHARGING */
#if defined(HAVE_USB_CHARGING_ENABLE) && defined(HAVE_USBSTACK)
            case USB_CHARGER_UPDATE:
            usb_charging_maxcurrent_change(usb_charging_maxcurrent());
            break;
#endif

            /* CLOSE */
#ifdef USB_DRIVER_CLOSE
            case USB_QUIT:
            return;
#endif
        } /* switch */
    } /* while */
}

static void usb_signal_transfer_completion(struct usb_transfer_completion_event_data* event_data);
static void usb_signal_transfer_completion(struct usb_transfer_completion_event_data* event_data)
{
    //queue_post(&usb_queue, USB_TRANSFER_COMPLETION, (intptr_t)event_data);

    struct queue_event ev;
    ev.id = USB_TRANSFER_COMPLETION;
    ev.data = (intptr_t) event_data;
    usb_thread(ev);
}


/*================================================================*/
void core_drv_ep_ini_data(void);
void core_drv_ep_ini_data()
{
	   BTR_USB_MEMSET(ep_data, 0, sizeof(ep_data));
}
/* called by otg_transfer_completed() */
void core_drv_ep_transfer_complete(int endpoint, int dir, int status, int length);
void core_drv_ep_transfer_complete(int endpoint, int dir, int status, int length) {
    struct usb_transfer_completion_event_data *completion_event;

    switch (endpoint) {
    case EP_CONTROL:
        /* already handled */
        break;

    default:
        completion_event = &ep_data[endpoint].completion_event[EP_DIR(dir)];

        completion_event->endpoint = endpoint;
        completion_event->dir = dir;
        completion_event->data = 0;
        completion_event->status = status;
        completion_event->length = length;

        usb_signal_transfer_completion(completion_event);

        break;
    }
}

/* called by otg_drv_int() */
void core_drv_ep_ini_ctrlrequest(void* req);
void core_drv_ep_ini_ctrlrequest(void* req) {

    struct usb_transfer_completion_event_data* completion_event = &ep_data[EP_CONTROL].completion_event[EP_DIR(USB_DIR_IN)];

    completion_event->endpoint = EP_CONTROL;
    completion_event->dir = 0;
    completion_event->data = (void*) req;
    completion_event->status = 0;
    completion_event->length = 0;
    //BTR_USB_PRINTF("ctrl received %ld", current_tick);
    usb_signal_transfer_completion(completion_event);

}

void core_drv_ep_release_endpoint(int ep);
void core_drv_ep_release_endpoint(int ep) {
    int dir;

    otg_drv_epn_release(ep);

    dir = EP_DIR(ep);
    ep = EP_NUM(ep);

    ep_data[ep].completion_handler[dir] = NULL;
    ep_data[ep].control_handler[dir] = NULL;
}


int core_drv_ep_request_endpoint(int type, int dir, void *driver);
int core_drv_ep_request_endpoint(int type, int dir, void *driver)
{
    int ret, ep;
    struct usb_class_driver* drv;
    drv = (struct usb_class_driver* )driver;
    ret = otg_request_endpoint(type, dir);

    if (ret == -1)
        return -1;

    dir = EP_DIR(ret);
    ep = EP_NUM(ret);

    ep_data[ep].completion_handler[dir] = drv->transfer_complete;
    ep_data[ep].control_handler[dir] = drv->control_request;

    return ret;
}

bool core_drv_ep_handle_req(u16_t index,void *req);
bool core_drv_ep_handle_req(u16_t index,void *req)
{
	bool handled;
    control_handler_t control_handler = NULL;

    handled = false;

    if (EP_NUM(index) < USB_NUM_ENDPOINTS)
        control_handler = ep_data[EP_NUM(index)].control_handler[EP_DIR(index)];

    if (control_handler)
        handled = control_handler(req, response_data);

    return handled;
}
/*================================================================*/

/* end of endpoint.c */
