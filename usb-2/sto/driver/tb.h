
/*------------------------------------
 * tb.h
 * Create:  2021-11-05
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


#ifndef USB_STO_DRIVER_TB_H_
#define USB_STO_DRIVER_TB_H_
/*================================================================*/
union STO_TB_U{
    unsigned char* transfer_buffer;
    void *inquiry;
    void *capacity_data;
    void *format_capacity_data;
    void *sense_data;
    void *ms_data_6;
    void *ms_data_10;
    void *lun_data;
    void *csw;
    char *max_lun;
};

extern union STO_TB_U sto_tb;
/*================================================================*/
#endif
/* end of tb.h */
