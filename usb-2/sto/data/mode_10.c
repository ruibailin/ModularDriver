
/*------------------------------------
 * longlba.c
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

#include "../0ctr.h"
#include "../1imp.h"
/*================================================================*/
struct mode_sense_bdesc_longlba {
    unsigned char num_blocks[8];
    unsigned char reserved[4];
    unsigned char block_size[4];
}__attribute__ ((packed));

struct mode_sense_data_10 {
    unsigned short mode_data_length;
    unsigned char medium_type;
    unsigned char device_specific;
    unsigned char longlba;
    unsigned char reserved;
    unsigned short block_descriptor_length;
    struct mode_sense_bdesc_longlba block_descriptor;
}__attribute__ ((packed));

#define htobe16(x)	(x)
int data_mode_sense_10_3f(void *data,int div, int mul);
int data_mode_sense_10_3f(void *data,int div, int mul)
{
	struct mode_sense_data_10 *ms_data_10 = (struct mode_sense_data_10 *)data;

    ms_data_10->mode_data_length = htobe16(sizeof(struct mode_sense_data_10) - 2);
    ms_data_10->medium_type = 0;
    ms_data_10->device_specific = 0;
    ms_data_10->reserved = 0;
    ms_data_10->longlba = 1;
    ms_data_10->block_descriptor_length = htobe16(sizeof(struct mode_sense_bdesc_longlba));

    BTR_USB_MEMSET(ms_data_10->block_descriptor.reserved, 0, 4);
    BTR_USB_MEMSET(ms_data_10->block_descriptor.num_blocks, 0, 8);

    ms_data_10->block_descriptor.num_blocks[4] = (div & 0xff000000) >> 24;
    ms_data_10->block_descriptor.num_blocks[5] = (div & 0x00ff0000) >> 16;
    ms_data_10->block_descriptor.num_blocks[6] = (div & 0x0000ff00) >> 8;
    ms_data_10->block_descriptor.num_blocks[7] = (div & 0x000000ff);

    ms_data_10->block_descriptor.block_size[0] = (mul & 0xff000000) >> 24;
    ms_data_10->block_descriptor.block_size[1] = (mul & 0x00ff0000) >> 16;
    ms_data_10->block_descriptor.block_size[2] = (mul & 0x0000ff00) >> 8;
    ms_data_10->block_descriptor.block_size[3] = (mul & 0x000000ff);


    return sizeof(struct mode_sense_data_10);
}

/*================================================================*/

/* end of longlba.c */
