
/*------------------------------------
 * string.h
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



#ifndef DRV_USB_STRING_H_
#define DRV_USB_STRING_H_
/*================================================================*/
#include "1imp.h"
/**
 * struct usb_string - wraps a C string and its USB id
 * @id:the (nonzero) ID for this string
 * @s:the string, in UTF-8 encoding
 *
 * If you're using usb_gadget_get_string(), use this to wrap a string
 * together with its ID.
 */
struct usb_string {
    u8_t id;
    const char* s;
};

/*================================================================*/
#endif
/* end of string.h */
