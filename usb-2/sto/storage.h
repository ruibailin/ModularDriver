
/*------------------------------------
 * storage.h
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



#ifndef USB_STORAGE_STORAGE_H_
#define USB_STORAGE_STORAGE_H_
/*================================================================*/
extern int usb_storage_request_endpoints(void *drv);
extern int usb_storage_set_first_interface(int interface);
extern int usb_storage_get_config_descriptor(u8_t *dest, int max_packet_size);
extern void usb_storage_init_connection(void);
extern void usb_storage_disconnect(void);
extern void usb_storage_init(void);
extern void usb_storage_transfer_complete(int ep, int dir, int state, int length);
extern bool usb_storage_control_request(void* req, u8_t* dest);
extern void usb_storage_notify_hotswap(int volume,bool inserted);

/*================================================================*/
#endif
/* end of storage.h */
