
/*------------------------------------
 * capacity.c
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

struct capacity {
    unsigned int block_count;
    unsigned int block_size;
}__attribute__ ((packed));

struct format_capacity {
    unsigned int following_length;
    unsigned int block_count;
    unsigned int block_size;
}__attribute__ ((packed));


/*================================================================*/
#define htole32(x) (x)
#define htobe32(x) (x)

#define SCSI_FORMAT_CAPACITY_FORMATTED_MEDIA 0x02000000

int    data_read_format_capacity_data(void *data,int div,int mul);
int    data_read_format_capacity_data(void *data,int div,int mul)
{
	struct format_capacity  *format_capacity_data = (struct format_capacity *)data;
    format_capacity_data->following_length = htobe32(8);
    /* "block count" actually means "number of last block" */
    format_capacity_data->block_count = htobe32(div);
    format_capacity_data->block_size = htobe32(mul);
    format_capacity_data->block_size |= htobe32(SCSI_FORMAT_CAPACITY_FORMATTED_MEDIA);

    return sizeof(struct format_capacity);
}

int    data_read_capacity_data(void *data,int div,int mul);
int    data_read_capacity_data(void *data,int div,int mul)
{
	struct format_capacity  *format_capacity_data = (struct format_capacity *)data;

    format_capacity_data->block_count = htobe32(div);
    format_capacity_data->block_size = htobe32(mul);

    return sizeof(struct format_capacity);
}
/*================================================================*/

/* end of capacity.c */
