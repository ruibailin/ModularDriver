
/*------------------------------------
 * request.c
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

#include "../0ctr.h"
#include "../1imp.h"

#include "../request.h"
#include "../state.h"
#include "../dt_type.h"
#include "../desc/desc.h"
#include "../../usb/usb.h"
#include "../../otg/otg.h"
#include "../../core/core.h"
/*================================================================*/

#define intptr_t    long
//#define SYS_USB_CONNECTED_ACK     MAKE_SYS_EVENT(SYS_EVENT_CLS_USB, 1)

struct queue_event {
    long id;
    intptr_t data;
};

int 	core_drv_num_interfaces;
extern unsigned char *response_data;
/*================================================================*/
static void request_handler_interface_drivers(void *ctrl);
static void request_handler_device_get_descriptor(void *ctrl);
static void request_handler_device_get_descriptor(void *ctrl) {
    int size,length,index;
    // bool handled = true;
    const void* ptr;
    ptr = NULL;
    length = usb_get_ctrlrequest_length(ctrl);
    index = usb_get_ctrlrequest_value(ctrl);

    switch (index >> 8) { /* type */
    case USB_DT_DEVICE:
        ptr = core_desc_dev_get_add();
        size = core_desc_dev_get_len();
        break;

    case USB_DT_OTHER_SPEED_CONFIG:
    case USB_DT_CONFIG: {
        int i, max_packet_size;
        max_packet_size = core_desc_cfg_set_type(index >> 8);
        size = core_desc_cfg_get_len();

        size = core_drv_set_dt_config(size,max_packet_size);

        core_desc_cfg_set_dt_config(core_drv_num_interfaces,size);
        ptr = response_data;
        break;
    }

    case USB_DT_STRING:
        BTR_USB_PRINTF("STRING %d", index);
        size = core_desc_usb_str_get_len(index);
        ptr = core_desc_usb_str_get_add(index);

        if (ptr == NULL)
        {
            BTR_USB_PRINTF("bad string id %d", index);
            otg_stall(EP_CONTROL, true, true);
        }
        break;

    case USB_DT_DEVICE_QUALIFIER:
        ptr = core_desc_qual_get_add();
        size = core_desc_qual_get_len();
        break;

    default:
        BTR_USB_PRINTF("ctrl desc.");
//            handled = false;
//        control_request_handler_drivers(ctrl);
        request_handler_interface_drivers(ctrl);
        break;
    }

    if (ptr) {
        BTR_USB_PRINTF("request_handler_device_get_descriptor data %d (%d)\n\r", size, length);
        length = MIN(size, length);

        if (ptr != response_data)
            BTR_USB_MEMCPY(response_data, ptr, length);

        otg_recv(EP_CONTROL, NULL, 0);
        otg_send(EP_CONTROL, response_data, length);
    }
}
/*================================================================*/
static void request_handler_interface_drivers(void *ctrl) {

    int interface;
    bool handled;
    u8_t req;
    u16_t val;

    interface = usb_get_ctrlrequest_index(ctrl) & 0xff;
    handled = core_drv_handle_request(ctrl,interface);

    if (!handled) {
        /* nope. flag error */
    	req = usb_get_ctrlrequest_request(ctrl);
    	val = usb_get_ctrlrequest_value(ctrl);
        BTR_USB_PRINTF("bad req:desc %d:%d", req, val >> 8);
        otg_stall(EP_CONTROL, true, true);
    }
}

static void request_handler_interface_standard(void *ctrl);
static void request_handler_interface_standard(void *ctrl) {
    u8_t req;
//    u16_t val;

    req = usb_get_ctrlrequest_request(ctrl);
//    val = usb_get_ctrlrequest_value(ctrl);

    switch (req) {
    case USB_REQ_SET_INTERFACE:
        BTR_USB_PRINTF("usb_core: SET_INTERFACE");
        otg_send(EP_CONTROL, NULL, 0);
        break;

    case USB_REQ_GET_INTERFACE:
        BTR_USB_PRINTF("usb_core: GET_INTERFACE");
        response_data[0] = 0;
        otg_recv(EP_CONTROL, NULL, 0);
        otg_send(EP_CONTROL, response_data, 1);
        break;
    case USB_REQ_CLEAR_FEATURE:
        break;
    case USB_REQ_SET_FEATURE:
        break;
    case USB_REQ_GET_STATUS:
        response_data[0] = 0;
        response_data[1] = 0;
        otg_recv(EP_CONTROL, NULL, 0);
        otg_send(EP_CONTROL, response_data, 2);
        break;
    default:
    	request_handler_interface_drivers(ctrl);
        break;
    }
}

/*================================================================*/
static void request_handler_endpoint_drivers(void *ctrl);
static void request_handler_endpoint_drivers(void *ctrl) {
	bool handled;
    u16_t index;
    u8_t req;

    req = usb_get_ctrlrequest_request(ctrl);
    index = usb_get_ctrlrequest_index(ctrl);

	handled = core_drv_ep_handle_req(index,ctrl);

    if (!handled) {
        /* nope. flag error */
        BTR_USB_PRINTF("usb bad req %d", req);
        otg_stall(EP_CONTROL, true, true);
    }
}

#include "../../otg/otg.h"
static void request_handler_endpoint_standard(void *ctrl);
static void request_handler_endpoint_standard(void *ctrl) {
    u8_t req;
    u16_t val,ind;

    req = usb_get_ctrlrequest_request(ctrl);
    val = usb_get_ctrlrequest_value(ctrl);
    ind = usb_get_ctrlrequest_index(ctrl);

    switch (req) {
    case USB_REQ_CLEAR_FEATURE:
        if (val == USB_ENDPOINT_HALT)
            otg_stall(EP_NUM(ind), false, EP_DIR(ind));

        otg_send(EP_CONTROL, NULL, 0);
        break;
    case USB_REQ_SET_FEATURE:
        if (val == USB_ENDPOINT_HALT)
            otg_stall(EP_NUM(ind), true, EP_DIR(ind));

        otg_send(EP_CONTROL, NULL, 0);
        break;
    case USB_REQ_GET_STATUS:
        response_data[0] = 0;
        response_data[1] = 0;
        BTR_USB_PRINTF("usb_core: GET_STATUS");
        if (ind > 0)
            response_data[0] = otg_is_stalled(EP_NUM(ind), EP_DIR(ind));

        otg_recv(EP_CONTROL, NULL, 0);
        otg_send(EP_CONTROL, response_data, 2);
        break;
    default:
        request_handler_endpoint_drivers(ctrl);
        break;
    }
}

/*================================================================*/
#include "../../core/core.h"
static void allocate_interfaces_and_endpoints(void);
static void allocate_interfaces_and_endpoints(void) {
    int i;
    int interface;

    core_drv_ep_ini_data();

    for (i = 0; i < USB_NUM_ENDPOINTS; i++) {
        otg_release_endpoint(i | USB_DIR_OUT);
        otg_release_endpoint(i | USB_DIR_IN);
    }

    interface = core_drv_find_if();
    core_drv_num_interfaces = interface;
}

int 	core_drv_address = 0;
extern enum {
    DEFAULT, ADDRESS, CONFIGURED
} usb_state;
static void request_handler_device(void *ctrl);
static void request_handler_device(void *ctrl) {
    u8_t req;
    u16_t val;

    req = usb_get_ctrlrequest_request(ctrl);
    val = usb_get_ctrlrequest_value(ctrl);

    BTR_USB_PRINTF("req->bRequest=%d\n\r", req);
    //CON_PRINTF("r%x\n\r", req->bRequest);
    switch (req) {
    case USB_REQ_GET_CONFIGURATION: {
        BTR_USB_PRINTF("usb_core: GET_CONFIG");
        response_data[0] = (usb_state == ADDRESS ? 0 : 1);
        otg_recv(EP_CONTROL, NULL, 0);
        otg_send(EP_CONTROL, response_data, 1);
        break;
    }
    case USB_REQ_SET_CONFIGURATION: {
        BTR_USB_PRINTF("usb_core: SET_CONFIG");
        otg_cancel_all_transfers();
    	core_drv_req_set_config(val);
        BTR_USB_PRINTF("usb_core: SET_CONFIG[%d]\n\r", val);
        otg_send(EP_CONTROL, NULL, 0);
        break;
    }
    case USB_REQ_SET_ADDRESS: {
        unsigned char address = val;
        BTR_USB_PRINTF("usb_core: SET_ADR %d\n\r", address);
        otg_send(EP_CONTROL, NULL, 0);
        otg_cancel_all_transfers();
        core_drv_address = address;
        otg_set_address(core_drv_address);
        usb_state = ADDRESS;
        break;
    }
    case USB_REQ_GET_DESCRIPTOR:
        BTR_USB_PRINTF("usb_core: GET_DESC %d\n\r", val >> 8);
        request_handler_device_get_descriptor(ctrl);
        BTR_USB_PRINTF("############end\n\r");
        break;
    case USB_REQ_CLEAR_FEATURE:
        break;
    case USB_REQ_SET_FEATURE:
        if (val == USB_DEVICE_TEST_MODE) {
            val = usb_get_ctrlrequest_index(ctrl);
            int mode = val >> 8;
            otg_send(EP_CONTROL, NULL, 0);
            otg_set_test_mode(mode);
        }
        break;
    case USB_REQ_GET_STATUS:
        response_data[0] = 0;
        response_data[1] = 0;
        otg_recv(EP_CONTROL, NULL, 0);
        otg_send(EP_CONTROL, response_data, 2);
        break;
    default:
        break;
    }
}

#include "../../usb/usb.h"
static void request_handler_interface(void *ctrl);
static void request_handler_interface(void *ctrl) {
    u8_t type;
 //   u16_t val;

    type = usb_get_ctrlrequest_type(ctrl);
//    val = usb_get_ctrlrequest_value(ctrl);

    switch (type & USB_TYPE_MASK) {
    case USB_TYPE_STANDARD:
        request_handler_interface_standard(ctrl);
        break;
    case USB_TYPE_CLASS:
    	request_handler_interface_drivers(ctrl);
//        control_request_handler_drivers(ctrl);
        break;
    case USB_TYPE_VENDOR:
        break;
    }
}


static void request_handler_endpoint(void *ctrl);
static void request_handler_endpoint(void *ctrl) {
    u8_t type;

    type = usb_get_ctrlrequest_type(ctrl);

    switch (type & USB_TYPE_MASK) {
    case USB_TYPE_STANDARD:
        request_handler_endpoint_standard(ctrl);
        break;
    case USB_TYPE_CLASS:
        request_handler_endpoint_drivers(ctrl);
        break;
    case USB_TYPE_VENDOR:
    default:
        break;
    }
}

/*================================================================*/
/* Handling USB requests starts here */
void core_drv_control_request_handler(void *ctrl);
void core_drv_control_request_handler(void *ctrl) {
    u8_t type;


    type = usb_get_ctrlrequest_type(ctrl);

	int id;

    if (usb_state == DEFAULT) {
    	core_desc_dev_clr_serial();
        id = core_drv_get_serial_function_id();
        core_desc_usb_str_set_str0(id);

        allocate_interfaces_and_endpoints();
    }

    switch (type & USB_RECIP_MASK) {
    case USB_RECIP_DEVICE:
        request_handler_device(ctrl);
        break;
    case USB_RECIP_INTERFACE:
        request_handler_interface(ctrl);
        break;
    case USB_RECIP_ENDPOINT:
        request_handler_endpoint(ctrl);
        break;
    case USB_RECIP_OTHER:
        BTR_USB_PRINTF("unsupported recipient");
        break;
    }
    //BTR_USB_PRINTF("control handled");
}
/*================================================================*/

/* end of request.c */
