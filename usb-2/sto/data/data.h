
/*------------------------------------
 * data.h
 * Create:  2021-11-14
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


#ifndef USB_STO_DATA_DATA_H_
#define USB_STO_DATA_DATA_H_
/*================================================================*/
extern int data_read_format_capacity_data(void *data,int div,int mul);
extern int data_read_capacity_data(void *data,int div,int mul);

#include "command.h"

extern void data_fill_scsi_inquiry(void *in);
extern void data_inquiry(void *in,int length);

extern int data_mode_sense_10_3f(void *data,int div, int mul);
extern int data_mode_sense_6_3f(void *data,int div, int mul);

#include "sense.h"
/*================================================================*/
#endif
/* end of data.h */
