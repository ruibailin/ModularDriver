
/*------------------------------------
 * ctrlrequest.h
 * Create:  2021-10-28
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */



#ifndef ENDPOINT_CTRLREQUEST_H_
#define ENDPOINT_CTRLREQUEST_H_
/*================================================================*/
extern void *ep0_setup_pkt;
extern u8_t usb_get_ctrlrequest_type(void *pkt);
extern u8_t usb_get_ctrlrequest_request(void *pkt);
extern u16_t usb_get_ctrlrequest_length(void *pkt);
extern u16_t usb_get_ctrlrequest_value(void *pkt);
extern u16_t usb_get_ctrlrequest_index(void *pkt);
extern bool usb_is_ctrlrequest_set_add(void *pkt);

extern int usb_get_ep_mps(int ep_type,int speed_type);

extern void usb_wakeup_init(u32_t *complete);
extern void usb_wakeup_signal(u32_t *complete);

extern bool usb_storage_removable(int lun);
extern bool usb_storage_present(int lun);

#define BTR_USB_PRINTF(fmt,...) do{}while(0)
#define logf(fmt, ...)          do{}while(0)

extern bool usb_reboot_button(void);
extern void usb_try_reboot(void);
/*================================================================*/
#endif
/* end of ctrlrequest.h */
