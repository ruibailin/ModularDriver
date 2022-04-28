
/*------------------------------------
 * inquiry.c
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
/*================================================================*/
struct inquiry_data {
    unsigned char DeviceType;
    unsigned char DeviceTypeModifier;
    unsigned char Versions;
    unsigned char Format;
    unsigned char AdditionalLength;
    unsigned char Reserved[2];
    unsigned char Capability;
    unsigned char VendorId[8];
    unsigned char ProductId[16];
    unsigned char ProductRevisionLevel[4];
}__attribute__ ((packed));

/*================================================================*/
static void copy_padded(char *dest, char *src, int len) {
    int i = 0;
    while (src[i] != 0 && i < len) {
        dest[i] = src[i];
        i++;
    }
    while (i < len) {
        dest[i] = ' ';
        i++;
    }
}

/*================================================================*/
/* bulk-only class specific requests */
#define USB_BULK_RESET_REQUEST   0xff
#define USB_BULK_GET_MAX_LUN     0xfe

#define DIRECT_ACCESS_DEVICE     0x00    /* disks */
#define DEVICE_REMOVABLE         0x80

void data_fill_scsi_inquiry(void *in);
void data_fill_scsi_inquiry(void *in)
{
	struct inquiry_data *inquiry = (struct inquiry_data *)in;
    BTR_USB_MEMSET(inquiry, 0, sizeof(struct inquiry_data));
    copy_padded((char *) inquiry->VendorId, "Libra", sizeof(inquiry->VendorId));
    copy_padded((char *) inquiry->ProductId, "Boot", sizeof(inquiry->ProductId));
    copy_padded((char *) inquiry->ProductRevisionLevel, "0.00", sizeof(inquiry->ProductRevisionLevel));

    inquiry->DeviceType = DIRECT_ACCESS_DEVICE;
    inquiry->AdditionalLength = 0x1f;
    BTR_USB_MEMSET(inquiry->Reserved, 0, 3);
    inquiry->Versions = 4; /* SPC-2 */
    inquiry->Format = 2; /* SPC-2/3 inquiry format */

    inquiry->DeviceTypeModifier = DEVICE_REMOVABLE;

}

void   data_inquiry(void *in,int length);
void   data_inquiry(void *in,int length)
{
	struct inquiry_data *inquiry=(struct inquiry_data *)in;

	sto_drv_epn_send_nb(inquiry, MIN(sizeof(struct inquiry_data), length));
}
/*================================================================*/

/* end of inquiry.c */
