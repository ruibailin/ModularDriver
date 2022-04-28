
/*------------------------------------
 * shortlba.c
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
struct mode_sense_bdesc_shortlba {
    unsigned char density_code;
    unsigned char num_blocks[3];
    unsigned char reserved;
    unsigned char block_size[3];
}__attribute__ ((packed));

struct mode_sense_data_6 {
    unsigned char mode_data_length;
    unsigned char medium_type;
    unsigned char device_specific;
    unsigned char block_descriptor_length;
    struct mode_sense_bdesc_shortlba block_descriptor;
}__attribute__ ((packed));

int data_mode_sense_6_3f(void *data,int div, int mul);
int data_mode_sense_6_3f(void *data,int div, int mul)
{
	struct mode_sense_data_6 *ms_data_6 = (struct mode_sense_data_6 *)data;
    /* All supported pages. */
    ms_data_6->mode_data_length = sizeof(struct mode_sense_data_6) - 1;
    ms_data_6->medium_type = 0;
    ms_data_6->device_specific = 0;
    ms_data_6->block_descriptor_length = sizeof(struct mode_sense_bdesc_shortlba);
    ms_data_6->block_descriptor.density_code = 0;
    ms_data_6->block_descriptor.reserved = 0;
    if (div > 0xffffff) {
        ms_data_6->block_descriptor.num_blocks[0] = 0xff;
        ms_data_6->block_descriptor.num_blocks[1] = 0xff;
        ms_data_6->block_descriptor.num_blocks[2] = 0xff;
    } else {
        ms_data_6->block_descriptor.num_blocks[0] = (div & 0xff0000) >> 16;
        ms_data_6->block_descriptor.num_blocks[1] = (div & 0x00ff00) >> 8;
        ms_data_6->block_descriptor.num_blocks[2] = (div & 0x0000ff);
    }
    ms_data_6->block_descriptor.block_size[0] = (mul & 0xff0000) >> 16;
    ms_data_6->block_descriptor.block_size[1] = (mul & 0x00ff00) >> 8;
    ms_data_6->block_descriptor.block_size[2] = (mul & 0x0000ff);

    return sizeof(struct mode_sense_data_6);
}
/*================================================================*/

/* end of shortlba.c */
