
/*------------------------------------
 * command.h
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



#ifndef USB_STO_DATA_COMMAND_H_
#define USB_STO_DATA_COMMAND_H_
/*================================================================*/
extern u8_t data_cbw_get_page_code(void *data);
extern u8_t data_cbw_get_command_block(void *data,int id);
extern bool data_cbw_is_signed(void *data);
extern void data_cbw_wait_next(void);
extern bool data_cbw_is_rec_time(void *cmd);
extern u8_t data_cbw_get_length(void *data);
extern u8_t data_cbw_get_lun(void *data);

extern int data_cmd_send_next_sector(void);
extern void data_cmd_send_and_read_next(void);
extern void data_cmd_save_cbw(void *data);
extern void data_cmd_write_10(void *transfer_buffer,void *cmd,int block_size);
extern u32_t data_cmd_get_count(void);
extern u32_t data_cmd_get_last_result(void);
extern u8_t data_cmd_get_sector(void);
extern int data_cmd_get_length(void);
extern void data_cmd_write_10_read(void);
extern void data_cmd_read_10(void *transfer_buffer,void *cmd,int block_size);
extern void data_cmd_read_sector(void);

extern void data_csw_send(void *data,int status);


/*================================================================*/
#endif
/* end of command.h */
