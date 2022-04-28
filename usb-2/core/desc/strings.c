
/*------------------------------------
 * strings.c
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
/*================================================================*/
/* USB_DT_STRING: String descriptor */
struct usb_string_descriptor {
    u8_t bLength;
    u8_t bDescriptorType;

    u16_t wString[]; /* UTF-16LE encoded */
}__attribute__ ((packed));

/* note that "string" zero is special, it holds language codes that
 * the device supports, not Unicode characters.
 */

static struct usb_string_descriptor __attribute__((aligned(2)))
usb_string_iManufacturer = {
		24,
		USB_DT_STRING,
		{ 'A', 'v', 'a', 'i', 'l', 'i', 'n', 'k', '.', 'C', 'o' }
};

static struct usb_string_descriptor __attribute__((aligned(2)))
usb_string_iProduct = {
		42,
		USB_DT_STRING,
		{ 'A', 'v', 'a', 'i', 'l', 'i', 'n', 'k', 'B', 'O', 'O', 'T', 'R', 'O', 'M', 'U', 'S', 'B', 'L', 'R' }
};

static struct usb_string_descriptor __attribute__((aligned(2)))
usb_string_iSerial = {
		84,
		USB_DT_STRING,
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' }
};

/* Generic for all targets */

/* this is stringid #0: languages supported */
static struct usb_string_descriptor __attribute__((aligned(2)))
lang_descriptor = {
		4,
		USB_DT_STRING,
		{ 0x0409 } /* LANGID US English */
};

static struct usb_string_descriptor* usb_strings[] = {
		&lang_descriptor,
		&usb_string_iManufacturer,
        &usb_string_iProduct,
		&usb_string_iSerial
};

/*================================================================*/
#ifdef IPOD_ARCH
void set_serial_descriptor(void)
{
#ifdef IPOD_VIDEO
    u32_t* serial = (u32_t*)0x20004034;
#else
    u32_t* serial = (u32_t*)0x20002034;
#endif

    /* We need to convert from a little-endian 64-bit int
     into a utf-16 string of hex characters */
    short* p = &usb_string_iSerial.wString[24];
    u32_t x;
    int i, j;

    for(i = 0; i < 2; i++) {
        x = serial[i];
        for(j = 0; j < 8; j++) {
            *p-- = hex[x & 0xf];
            x >>= 4;
        }
    }
    usb_string_iSerial.bLength = 52;
}
#elif defined(HAVE_AS3514)
void set_serial_descriptor(void)
{
    unsigned char serial[16];
    /* Align 32 digits right in the 40-digit serial number */
    short* p = &usb_string_iSerial.wString[1];
    int i;

    ascodec_readbytes(AS3514_UID_0, 0x10, serial);
    for(i = 0; i < 16; i++) {
        *p++ = hex[(serial[i] >> 4) & 0xF];
        *p++ = hex[(serial[i] >> 0) & 0xF];
    }
    usb_string_iSerial.bLength = 68;
}
#elif (CONFIG_STORAGE & STORAGE_ATA)
/* If we don't know the device serial number, use the one
 * from the disk */
void set_serial_descriptor(void)
{
    short* p = &usb_string_iSerial.wString[1];
    unsigned short* identify = ata_get_identify();
    unsigned short x;
    int i;

    for(i = 10; i < 20; i++) {
        x = identify[i];
        *p++ = hex[(x >> 12) & 0xF];
        *p++ = hex[(x >> 8) & 0xF];
        *p++ = hex[(x >> 4) & 0xF];
        *p++ = hex[(x >> 0) & 0xF];
    }
    usb_string_iSerial.bLength = 84;
}
#elif (CONFIG_STORAGE & STORAGE_RAMDISK)
/* This "serial number" isn't unique, but it should never actually
 appear in non-testing use */
void set_serial_descriptor(void)
{
    short* p = &usb_string_iSerial.wString[1];
    int i;
    for(i = 0; i < 16; i++) {
        *p++ = hex[(2 * i) & 0xF];
        *p++ = hex[(2 * i + 1) & 0xF];
    }
    usb_string_iSerial.bLength = 68;
}
#else
void set_serial_descriptor(void) {
//	core_desc_dev_clr_serial();
}
#endif

int core_desc_usb_str_get_len(int index);
int core_desc_usb_str_get_len(int index)
{
	int size;
	size = 0;
    if ((unsigned) index < (sizeof(usb_strings) / sizeof(struct usb_string_descriptor*))) {
        size = usb_strings[index]->bLength;
    }

    return size;
}

void *core_desc_usb_str_get_add(int index);
void *core_desc_usb_str_get_add(int index)
{
	void *ptr;
    if ((unsigned) index < (sizeof(usb_strings) / sizeof(struct usb_string_descriptor*))) {
        ptr = &(usb_strings[index]);
    }
    else
    	ptr = NULL;
    return ptr;
}

static short hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
void core_desc_usb_str_set_str0(int id);
void core_desc_usb_str_set_str0(int id)
{
	usb_string_iSerial.wString[0] = hex[id];
}
/*================================================================*/

/* end of strings.c */
