
/*------------------------------------
 * transfer.h
 * Create:  2021-11-17
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


#ifndef USB_STO_DRIVER_TRANSFER_H_
#define USB_STO_DRIVER_TRANSFER_H_
/*================================================================*/
extern void sto_drv_tran_complete(int ep, int dir, int status, int length);
extern void sto_drv_tran_ini_buffer(void);
extern void sto_drv_tran_def_buffer(void);
/*================================================================*/
#endif
/* end of transfer.h */
