
/*------------------------------------
 * driver.c
 * Create:  2021-10-25
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
#include "class.h"

/*================================================================*/
extern int usb_storage_request_endpoints(void *drv);
extern int usb_storage_set_first_interface(int interface);
extern int usb_storage_get_config_descriptor(unsigned char *dest, int max_packet_size);
extern void usb_storage_init_connection(void);
extern void usb_storage_init(void);
extern void usb_storage_disconnect(void);
extern void usb_storage_transfer_complete(int ep, int dir, int status, int length);
extern int usb_storage_control_request(void* req, unsigned char *dest);
extern void usb_storage_notify_hotswap(int volume, int inserted);
static struct usb_class_driver drivers[] = {
        {
        		.enabled = false,
        		.needs_exclusive_storage = true,
				.first_interface = 0,
				.last_interface = 0,
				.request_endpoints = usb_storage_request_endpoints,
				.set_first_interface = usb_storage_set_first_interface,
				.get_config_descriptor = usb_storage_get_config_descriptor,
				.init_connection = usb_storage_init_connection,
				.init = usb_storage_init,
                .disconnect = usb_storage_disconnect,
				.transfer_complete = usb_storage_transfer_complete,
				.control_request = usb_storage_control_request,
				.notify_hotswap = usb_storage_notify_hotswap,
    },
};
/*================================================================*/
void core_drv_init(void);
void core_drv_init()
{
    int i;
    /* class driver init functions should be safe to call even if the driver
     * won't be used. This simplifies other logic (i.e. we don't need to know
     * yet which drivers will be enabled */
    for (i = 0; i < sizeof(drivers) / sizeof(drivers[0]); i++)
        if (drivers[i].init != NULL)
            drivers[i].init();
}

void core_drv_exit(void);
void core_drv_exit()
{
    int i;
    for (i = 0; i < sizeof(drivers) / sizeof(drivers[0]); i++)
        if (drivers[i].enabled && drivers[i].disconnect != NULL) {
            drivers[i].disconnect();
            drivers[i].enabled = false;
        }
}

int core_drv_find_if(void);
int core_drv_find_if()
{
	int interface,i;
	interface = 0;
    for (i = 0; i < USB_NUM_DRIVERS; i++) {
        if (drivers[i].enabled) {
            drivers[i].first_interface = interface;

            if (drivers[i].request_endpoints(&drivers[i])) {
                drivers[i].enabled = false;
                continue;
            }

            interface = drivers[i].set_first_interface(interface);
            drivers[i].last_interface = interface;
        }
    }
    return interface;
}
/*================================================================*/
unsigned char *response_data = (unsigned char *) (BTR_NAND_DMA_BASE + 64);   //;[256] USB_DEVBSS_ATTR;

bool   core_drv_handle_request(void *ctrl,int interface);
bool   core_drv_handle_request(void *ctrl,int interface)
{
	int i;
	bool handled;
	handled = false;
    for (i = 0; i < USB_NUM_DRIVERS; i++) {
        if (drivers[i].enabled && drivers[i].control_request && drivers[i].first_interface <= interface
                && drivers[i].last_interface > interface) {
            handled = drivers[i].control_request(ctrl, response_data);
            if (handled)
                break;
        }
    }
    return handled;
}

void core_drv_enable_driver(int driver, bool enabled);
void core_drv_enable_driver(int driver, bool enabled) {
    drivers[driver].enabled = enabled;
}

bool core_drv_driver_enabled(int driver);
bool core_drv_driver_enabled(int driver) {
    return drivers[driver].enabled;
}

bool core_drv_any_exclusive_storage(void);
bool core_drv_any_exclusive_storage(void) {
    int i;
    for (i = 0; i < USB_NUM_DRIVERS; i++)
        if (drivers[i].enabled && drivers[i].needs_exclusive_storage)
            return true;

    return false;
}

void core_drv_hotswap_event(int volume, bool inserted);
void core_drv_hotswap_event(int volume, bool inserted)
{
    int i;
    for(i = 0; i < USB_NUM_DRIVERS; i++)
    if(drivers[i].enabled && drivers[i].notify_hotswap != NULL)
    drivers[i].notify_hotswap(volume, inserted);
}

int core_drv_get_serial_function_id(void);
int core_drv_get_serial_function_id(void) {
    int i, id = 0;

    for (i = 0; i < USB_NUM_DRIVERS; i++)
        if (drivers[i].enabled)
            id |= 1 << i;
    //usb_string_iSerial.wString[0] = hex[id];
    return id;
}

int core_drv_set_dt_config(int size,int mps);
int core_drv_set_dt_config(int size,int mps)
{
	int i;
    for (i = 0; i < USB_NUM_DRIVERS; i++)
        if (drivers[i].enabled && drivers[i].get_config_descriptor)
            size += drivers[i].get_config_descriptor(&response_data[size], mps);
    return size;
}

extern enum {
    DEFAULT, ADDRESS, CONFIGURED
} usb_state;
void core_drv_req_set_config(u16_t value);
void core_drv_req_set_config(u16_t value)
{
	int i;
    if (value) {
        usb_state = CONFIGURED;
        for (i = 0; i < USB_NUM_DRIVERS; i++)
            if (drivers[i].enabled && drivers[i].init_connection)
                drivers[i].init_connection();
    } else
        usb_state = ADDRESS;
}
/*================================================================*/
/* end of driver.c */
