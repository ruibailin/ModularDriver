
/*------------------------------------
 * strings.h
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


#include "../strings.h"
#ifndef USB_GADGET_STRING_H_
#define USB_GADGET_STRING_H_
/*================================================================*/
/**
 * struct usb_gadget_strings - a set of USB strings in a given language
 * @language:identifies the strings' language (0x0409 for en-us)
 * @strings:array of strings with their ids
 *
 * If you're using usb_gadget_get_string(), use this to wrap all the
 * strings for a given language.
 */
struct usb_gadget_strings {
    u16_t language; /* 0x0409 for en-us */
    struct usb_string* strings;
};

/*================================================================*/
#endif
/* end of strings.h */
