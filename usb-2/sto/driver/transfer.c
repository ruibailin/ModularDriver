
/*------------------------------------
 * transfer.c
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

#include "0ctr.h"
#include "1imp.h"
#include "state.h"
#include "status.h"
#include "tb.h"
#include "./device/device.h"

static unsigned char *cbw_buffer;
/*================================================================*/
static void sto_drv_tran_recieving_blocks(int dir,int status,int length)
{
	unsigned int ll,ii;

	if(sto_state !=RECEIVING_BLOCKS)
		return;

    if (dir == USB_DIR_IN) {
        //btr_printf(0,"IN received in RECEIVING");
    }
    logf("scsi write %d %d", cur_cmd.sector, cur_cmd.count);

    if (status != 0)
    {
        btr_printf(0,"Transfer failed %X\r\n", status);
    	data_csw_send(sto_tb.csw, UMS_STATUS_FAIL);

        sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
       	data_cbw_wait_next();
        /* TODO fill in cur_sense_data */
        data_sense_cur_init();
        return;
    }


    ll = (unsigned int) length;
    ii = SECTOR_SIZE * data_cmd_get_count();
    if ( (ll != ii) && (ll != WRITE_BUFFER_SIZE)) {
    	btr_printf(0,"unexpected length :%d", length);
        return;
    }

    ii = data_cmd_send_next_sector();
    if(ii == 0)
    	return;

	data_csw_send(sto_tb.csw, UMS_STATUS_GOOD);
    sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
	data_cbw_wait_next();
   	data_sense_cur_init();
}

static void sto_drv_tran_for_csw_or_command(int dir)
{
	if(sto_state != WAITING_FOR_CSW_COMPLETION_OR_COMMAND)
		return;

    if (dir == USB_DIR_IN)
    {
        /* This was the CSW */
        sto_state = WAITING_FOR_COMMAND;
    } else
    {
        /* This was the command */
        sto_state = WAITING_FOR_CSW_COMPLETION;
        /* We now have the CBW, but we won't execute it yet to avoid
         * issues with the still-pending CSW */
    }
}


static void sto_drv_tran_for_command(int dir)
{
	if(sto_state != WAITING_FOR_COMMAND)
		return;

    if (dir == USB_DIR_IN) {
        logf("IN received in WAITING_FOR_COMMAND");
    }
    sto_drv_scsi_handle_cbw(cbw_buffer);
}

static void sto_drv_tran_for_csw_completion(int dir)
{

	if(sto_state != WAITING_FOR_CSW_COMPLETION)
		return;

    if (dir == USB_DIR_OUT) {
        logf("OUT received in WAITING_FOR_CSW_COMPLETION");
    }
    sto_drv_scsi_handle_cbw(cbw_buffer);
}
static void sto_drv_tran_sending_result(int dir,int status)
{
	if( sto_state != SENDING_RESULT)
		return;

    if (dir == USB_DIR_OUT) {
        logf("OUT received in SENDING");
    }

    if (status == 0) {
        logf("data sent, now send csw");
    	data_csw_send(sto_tb.csw, UMS_STATUS_GOOD);
    }
    else
    	data_csw_send(sto_tb.csw, UMS_STATUS_FAIL);

   	sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
  	data_cbw_wait_next();
    /* TODO fill in cur_sense_data */
   	data_sense_cur_init();

}

static void sto_drv_tran_sending_failed(int dir)
{

	if(sto_state != SENDING_FAILED_RESULT)
		return;

    if (dir == USB_DIR_OUT) {
        logf("OUT received in SENDING");
    }
	data_csw_send(sto_tb.csw, UMS_STATUS_FAIL);
    sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
	data_cbw_wait_next();
}

static void sto_drv_tran_sending_block(int dir,int status)
{
	unsigned int i;

	if(sto_state != SENDING_BLOCKS)
		return;

	if (dir == USB_DIR_OUT) {
        logf("OUT received in SENDING");
    }

    if (status != 0)
    {
    	data_csw_send(sto_tb.csw, UMS_STATUS_FAIL);
        sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
    	data_cbw_wait_next();
        /* TODO fill in cur_sense_data */
    	data_sense_cur_init();
    	return;
    }

    i = data_cmd_get_count();
    if (i != 0)
    {
    	data_cmd_send_and_read_next();
        return;
    }

    logf("data sent, now send csw");
    i = data_cmd_get_last_result();
    if (i != 0) {
            /* The last read failed. */
        	data_csw_send(sto_tb.csw, UMS_STATUS_FAIL);
            sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
        	data_cbw_wait_next();
        	data_sense_cur_error();
            return;
        }

    data_csw_send(sto_tb.csw, UMS_STATUS_GOOD);
    sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
	data_cbw_wait_next();
   	data_sense_cur_init();
}

static void sto_drv_tran_recieving_time()
{
	if(sto_state !=RECEIVING_TIME)
		return;

    /*
     tm.tm_year=(sto_tb.transfer_buffer[0]<<8)+sto_tb.transfer_buffer[1] - 1900;
     tm.tm_yday=(sto_tb.transfer_buffer[2]<<8)+sto_tb.transfer_buffer[3];
     tm.tm_hour=sto_tb.transfer_buffer[5];
     tm.tm_min=sto_tb.transfer_buffer[6];
     tm.tm_sec=sto_tb.transfer_buffer[7];
     yearday_to_daymonth(tm.tm_yday,tm.tm_year + 1900,&tm.tm_mday,&tm.tm_mon);
     set_day_of_week(&tm);
     set_time(&tm);
     */

	data_csw_send(sto_tb.csw, UMS_STATUS_GOOD);
    sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
	data_cbw_wait_next();
   	data_sense_cur_init();
}

/*================================================================*/
void sto_drv_tran_complete(int ep, int dir, int status, int length);
void sto_drv_tran_complete(int ep, int dir, int status, int length) {
	sto_drv_tran_recieving_blocks(dir,status,length);
	sto_drv_tran_for_csw_or_command(dir);
	sto_drv_tran_for_command(dir);
	sto_drv_tran_for_csw_completion(dir);
	sto_drv_tran_sending_result(dir,status);
	sto_drv_tran_sending_failed(dir);
	sto_drv_tran_sending_block(dir,status);
	sto_drv_tran_recieving_time();
}

#include "./device/endpoint.h"
void sto_drv_tran_ini_buffer(void);
void sto_drv_tran_ini_buffer()
{
#ifdef USB_USE_RAMDISK
    //static unsigned char _ramdisk_buffer[RAMDISK_SIZE*SECTOR_SIZE];
    //ramdisk_buffer = (unsigned char *)(0x00F00000 + (512* 1024) * 2); ;
#endif
	//static unsigned char _cbw_buffer[MAX_CBW_SIZE]
    //USB_DEVBSS_ATTR __attribute__((aligned(32)));

    cbw_buffer = (unsigned char *) response_data + 64;
    sto_tb.transfer_buffer = (u8_t *) cbw_buffer + MAX_CBW_SIZE;
    sto_drv_epn_recv(cbw_buffer,MAX_CBW_SIZE);
    //ramdisk_buffer = cbw_buffer + MAX_CBW_SIZE + 1024;
}

void sto_drv_tran_def_buffer(void);
void sto_drv_tran_def_buffer()
{
    cbw_buffer = (unsigned char *) response_data + 64;
    sto_drv_epn_recv(cbw_buffer,MAX_CBW_SIZE);
}
/*================================================================*/

/* end of transfer.c */
