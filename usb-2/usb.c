
/*------------------------------------
 * usb.c
 * Create:  2021-11-11
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

#include "./core/core.h"
#include "./otg/otg.h"
#include "./sto/storage.h"
/*================================================================*/
i32_t 	usb_data_left;
bool 	usb_file_section_ok;

enum {
    DEFAULT, ADDRESS, CONFIGURED
} usb_state;

/*================================================================*/
static void usb_get_packet(void);
static void usb_get_packet(void) {
    while (!usb_file_section_ok)
    	otg_interrupt();
    usb_file_section_ok = false;
    usb_data_left = PACKET_SIZE_ONE_SECTION;
}


int usb_seek(void *args, u32_t whence, i32_t offset);
int usb_seek(void *args, u32_t whence, i32_t offset) {
    //btr_printf(0,"seek offset:%d, where:%d\n\r", offset, where);
    return 0;
}


void usb_init(void *args);
void usb_init(void *args) {
    usb_file_section_ok = false;
    usb_data_left = 0;
    core_data_reset();
    core_drv_init();
    usb_state = DEFAULT;
    core_drv_enable_driver(0, true);
}

static void usb_enable(bool on)
{
    if (on)
        otg_init();
    else
        otg_exit();
}

//#define usb_otg_attach usb_attach
void usb_attach(void);
void usb_attach(void) {
    panicf("usb-drv: attach");
    usb_enable(true);
}

extern char 	*usb_core_databuf;
int usb_read(void *args, void *buf, const u32_t size);
int usb_read(void *args, void *buf, const u32_t size) {
    i32_t len;
    i32_t cpy_len = 0;

    //  btr_printf(0,"\n\rusb read size=%d \n\r", size);
    // btr_asm_memset(buf, 0xEF, size);
    while (cpy_len < size) {
        if (usb_data_left != 0) {
            len = ((size - cpy_len) > usb_data_left) ? usb_data_left : (size - cpy_len);
            BTR_USB_MEMCPY((char *) buf + cpy_len, usb_core_databuf + (PACKET_SIZE_ONE_SECTION - usb_data_left), len);
            //btr_printf(0,"####usb_data_left[%d] cpy_len[%d] len[%d]\n\r", usb_data_left, cpy_len, len);

            usb_data_left -= len;
            cpy_len += len;

            continue;
        }

        usb_get_packet();
    }
    return cpy_len;
}

void usb_destroy(void *args);
void usb_destroy(void *args) {
    core_data_reset();
    usb_state = DEFAULT;
    otg_reset_endpoints();
    otg_disconnection();
}

bool usb_allowed_current();
bool usb_allowed_current()
{
    return (usb_state == CONFIGURED) ? MAX(USB_MAX_CURRENT, 100) : 100;
}

void usb_reconnection(void);
void usb_reconnection()
{
	otg_reconnection();
}

void usb_disconnection(void);
void usb_disconnection()
{
	otg_disconnection();
}

void usb_reset_endpoints(void);
void usb_reset_endpoints()
{
	otg_reset_endpoints();
}
/*================================================================*/

/* end of usb.c */
