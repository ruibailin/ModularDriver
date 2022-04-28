
/*------------------------------------
 * sense.h
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



#ifndef USB_STO_DATA_SENSE_H_
#define USB_STO_DATA_SENSE_H_
/*================================================================*/
extern int data_sense_request(void *data);

extern void data_sense_cur_init(void);
extern void data_sense_cur_error(void);
extern void data_sense_cur_not_ready(void);
extern void data_sense_cur_illegal(void);
/*================================================================*/
#endif
/* end of sense.h */
