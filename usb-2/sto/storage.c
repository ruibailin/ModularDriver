
/*------------------------------------
 * storage.c
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

#include "./driver/2exp.h"
/*================================================================*/
/* called by usb_core_init() */
void usb_storage_init(void) {
    logf("usb_storage_init done");
}

void usb_storage_try_release_storage(void) {
    /* Check if there is a connected drive left. If not,
     release excusive access */
    /*
     bool canrelease=true;
     int i;
     for(i=0;i<storage_num_drives();i++) {
     if(!ejected[i] && locked[i]) {
     canrelease=false;
     break;
     }
     }
     if(canrelease) {
     logf("scsi release ata");
     usb_release_exclusive_storage();
     }
     */
}

void usb_storage_notify_hotswap(int volume,bool inserted)
{
	sto_drv_dev_notify_hotswap(volume);
}


int usb_storage_request_endpoints(void *drv) {

	int ret;
	ret = sto_drv_ep_request_endpoint(drv);
	return ret;
}

int usb_storage_set_first_interface(int interface) {
	sto_drv_if_set_interface(interface);
    return interface + 1;
}

int usb_storage_get_config_descriptor(unsigned char *dest, int max_packet_size) {
    unsigned char *orig_dest = dest;

    dest = sto_drv_if_get_interface_desc(dest);
    dest = sto_drv_ep_get_endpoint_desc(dest, max_packet_size);
    return (dest - orig_dest);
}

void usb_storage_init_connection(void) {
	sto_drv_tran_ini_buffer();
}


void usb_storage_disconnect(void) {
    /* Empty for now */
}


/* called by usb_core_transfer_complete() */
void usb_storage_transfer_complete(int ep, int dir, int status, int length) {
    //logf("usb_storage_transfer_complete #############################################################################\n\r");

	sto_drv_tran_complete(ep, dir, status, length);
}

/* bulk-only class specific requests */
#define USB_BULK_RESET_REQUEST   0xff
#define USB_BULK_GET_MAX_LUN     0xfe
/* called by usb_core_control_request() */
#include "../usb/usb.h"
bool usb_storage_control_request(void *req, unsigned char* dest) {
    bool handled = false;

    //  logf("usb_storage_control_request, req->bRequest=%d #############################################################################\n\r", req->bRequest);
    //return 1;
    (void) dest;
    switch (usb_get_ctrlrequest_request(ep0_setup_pkt)) {
    case USB_BULK_GET_MAX_LUN: {
    	sto_drv_ctrl_get_max_lun();
        handled = true;
        break;
    }
    case USB_BULK_RESET_REQUEST:
    	sto_drv_ctrl_reset_request();
        handled = true;
        break;
    default:
    	break;
    }
    return handled;
}




/*

static void send_block_data(void *data, int size) {
    logf("NB\n\r");
	sto_drv_epn_send_nb(data, size);
    state = SENDING_BLOCKS;
}

static void send_command_result(void *data, int size) {
	sto_drv_epn_send_nb(data, size);
    state = SENDING_RESULT;
}

static void send_command_failed_result(void) {
    sto_drv_epn_send_nb(NULL, 0);
    state = SENDING_FAILED_RESULT;
}

static void receive_time(void) {
	sto_drv_epn_recv(tb.transfer_buffer, 12);
    state = RECEIVING_TIME;
}


static void receive_block_data(void *data, int size) {
	sto_drv_epn_recv(data,size);
    state = RECEIVING_BLOCKS;
}


static void send_csw(int status) {
	int size;
	data_csw_send(tb.csw, status);

    state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
    logf("CSW: %X", status);

	data_wait_next_cbw();

    if (status == UMS_STATUS_GOOD) {
    	data_sense_cur_init();
    }
}


// build SCSI INQUIRY
static void fill_inquiry(IF_MD_NONVOID(int lun)) {
//lun is not used
	data_fill_scsi_inquiry(tb->inquiry);
}
*/

/*================================================================*/

/* end of storage.c */
