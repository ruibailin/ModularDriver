
/*------------------------------------
 * drv_scsi.c
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
#include "tb.h"
#include "state.h"
#include "status.h"
#include "./device/device.h"
/*================================================================*/
union STO_TB_U sto_tb;
enum STO_STATE_E sto_state= WAITING_FOR_COMMAND;
/*================================================================*/
static void sto_drv_scsi_test_unit(void *cbw);
static void sto_drv_scsi_test_unit(void *cbw)
{
	bool lun_present;
	unsigned char lun;

	lun = data_cbw_get_lun(cbw);
	lun_present = sto_drv_dev_is_present(lun);

    logf("scsi test_unit_ready %d", lun);
    //if(!usb_exclusive_storage()) {
    if (0) {
    	data_csw_send(sto_tb.csw, UMS_STATUS_FAIL);
        sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
    	data_cbw_wait_next();
    	data_sense_cur_not_ready();
    }
    if (lun_present)
    {
    	data_csw_send(sto_tb.csw, UMS_STATUS_GOOD);
        sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
    	data_cbw_wait_next();
       	data_sense_cur_init();
       	return;
    }
    else
    {
    	data_csw_send(sto_tb.csw, UMS_STATUS_FAIL);
        sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
    	data_cbw_wait_next();
    	data_sense_cur_not_ready();
       	return;
    }
}

static void sto_drv_scsi_report_luns(void *cbw);
static void sto_drv_scsi_report_luns(void *cbw)
{
    /*
     {
     logf("scsi report luns %d",lun);
     int allocation_length=0;
     int i;
     unsigned int response_length = 8+8*storage_num_drives();
     allocation_length|=(cbw->command_block[6]<<24);
     allocation_length|=(cbw->command_block[7]<<16);
     allocation_length|=(cbw->command_block[8]<<8);
     allocation_length|=(cbw->command_block[9]);
     BTR_USB_MEMSET(sto_tb.lun_data,0,sizeof(struct report_lun_data));
     sto_tb.lun_data->lun_list_length=htobe32(8*storage_num_drives());
     for(i=0;i<storage_num_drives();i++)
     {
     #ifdef HAVE_HOTSWAP
     if(storage_removable(i))
     sto_tb.lun_data->luns[i][1]=1;
     else
     #endif
     sto_tb.lun_data->luns[i][1]=0;
     }
     send_command_result(sto_tb.lun_data,
     MIN(response_length, length));
     break;
     }
     */

}

static void sto_drv_scsi_inquiry(void *cbw);
static void sto_drv_scsi_inquiry(void *cbw)
{
	int length;
	unsigned char cb4;
	length = data_cbw_get_length(cbw);

    logf("scsi inquiry %d\n\r", lun);
    data_fill_scsi_inquiry(sto_tb.inquiry);
    cb4 = data_cbw_get_command_block(cbw,4);
    length = MIN(length, cb4);
    data_inquiry(sto_tb.inquiry,length);
    sto_state = SENDING_RESULT;
}

static void sto_drv_scsi_request_sense(void *cbw);
static void sto_drv_scsi_request_sense(void *cbw)
{
	int ll,length;
	ll = data_sense_request(sto_tb.sense_data);
	length = data_cbw_get_length(cbw);
	sto_drv_epn_send_nb(sto_tb.sense_data, MIN(ll, length));
    sto_state = SENDING_RESULT;
    logf("scsi request_sense1 %d", lun);
}

static void sto_drv_scsi_mode_sense_10(void *cbw);
static void sto_drv_scsi_mode_sense_10(void *cbw)
{
	bool lun_present;
	unsigned char lun,page_code;
	int div,mul,ll;

    unsigned int length;
    unsigned int block_size;
    unsigned int block_count;
    unsigned int block_size_mult;

	lun = data_cbw_get_lun(cbw);
	lun_present = sto_drv_dev_is_present(lun);

    if (!lun_present) {
        data_sense_cur_not_ready();
        sto_drv_epn_send_nb(NULL, 0);
        sto_state = SENDING_FAILED_RESULT;
        return;
    }
    /*unsigned char pc = (cbw->command_block[2] & 0xc0) >>6;*/
    page_code = data_cbw_get_page_code(cbw);
    logf("scsi mode_sense_10 %d %X", lun, page_code);
    if(page_code != 0x3f)
    {
        data_sense_cur_illegal();
        sto_drv_epn_send_nb(NULL, 0);
        sto_state = SENDING_FAILED_RESULT;
        return;
    }

#ifdef USB_USE_RAMDISK
    block_size = SECTOR_SIZE;
    block_count = RAMDISK_SIZE;
#else
    storage_get_info(lun,&info);
    block_size=info.sector_size;
    block_count=info.num_sectors;
#endif
    block_size_mult = 1;
#ifdef MAX_LOG_SECTOR_SIZE
    block_size_mult = disk_sector_multiplier;
#endif

	div = block_count / block_size_mult;
	mul = block_size * block_size_mult;

    length = data_cbw_get_length(cbw);
	ll = data_mode_sense_10_3f(sto_tb.ms_data_10,div,mul);

	sto_drv_epn_send_nb(sto_tb.ms_data_10, MIN(ll, length));
	sto_state = SENDING_RESULT;
}

static void sto_drv_scsi_mode_sense_6(void *cbw);
static void sto_drv_scsi_mode_sense_6(void *cbw)
{
	bool lun_present;
	unsigned char lun,page_code;
	int div,mul,ll;

    unsigned int length;
    unsigned int block_size;
    unsigned int block_count;
    unsigned int block_size_mult;

	lun = data_cbw_get_lun(cbw);
	lun_present = sto_drv_dev_is_present(lun);

    logf("SCSI_MODE_SENSE_6[%d]\n\r", lun_present);
    if (!lun_present) {
        sto_drv_epn_send_nb(NULL, 0);
        data_sense_cur_not_ready();
        sto_state = SENDING_FAILED_RESULT;
        return;
    }
    /*unsigned char pc = (cbw->command_block[2] & 0xc0) >>6;*/
    page_code = data_cbw_get_page_code(cbw);

    logf("scsi mode_sense_6 %d %x\n\r", lun, page_code);
    if(page_code != 0x3f)
    {
        logf("NB2\n\r");
        sto_drv_epn_send_nb(NULL, 0);
        data_sense_cur_illegal();
        sto_state = SENDING_FAILED_RESULT;
    }

#ifdef USB_USE_RAMDISK
    block_size = SECTOR_SIZE;
    block_count = RAMDISK_SIZE;
#else
    storage_get_info(lun,&info);
    block_size=info.sector_size;
    block_count=info.num_sectors;
#endif
    block_size_mult = 1;
#ifdef MAX_LOG_SECTOR_SIZE
    block_size_mult = disk_sector_multiplier;
#endif

	div = block_count / block_size_mult;
	mul = block_size * block_size_mult;

    length = data_cbw_get_length(cbw);
	ll = data_mode_sense_6_3f(sto_tb.ms_data_6,div,mul);
	sto_drv_epn_send_nb(sto_tb.ms_data_6, MIN(ll, length));
	sto_state = SENDING_RESULT;
}

static void sto_drv_scsi_stop_unit(void *cbw);
static void sto_drv_scsi_stop_unit(void *cbw)
{
    unsigned char cb4,lun;

    logf("scsi start_stop unit %d", lun);
	data_csw_send(sto_tb.csw, UMS_STATUS_GOOD);
    sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
	data_cbw_wait_next();
   	data_sense_cur_init();


    cb4 = data_cbw_get_command_block(cbw,4);

    if ((cb4 & 0xf0) != 0) /*load/eject bit is invalid*/
		return;
	logf("scsi load/eject");
    if ((cb4 & 0x01) != 0) /* start */
		return;
    if ((cb4 & 0x02) == 0) /* not eject */
		return;

    logf("scsi eject");
	lun = data_cbw_get_lun(cbw);
	sto_drv_dev_set_eject(lun,true);
}

static void sto_drv_scsi_allow_removal(void *cbw);
static void sto_drv_scsi_allow_removal(void *cbw)
{
    char cb4;

    cb4 = data_cbw_get_command_block(cbw,4);
    if ((cb4) == 0) {
        // locked[lun]=false;
        //queue_broadcast(SYS_USB_LUN_LOCKED, (lun<<16)+0);

    	//btr_printf(0,"false\n\r");
    } else {
        // locked[lun]=true;
        //queue_broadcast(SYS_USB_LUN_LOCKED, (lun<<16)+1);
        //btr_printf(0,"true\n\r");
    }
	data_csw_send(sto_tb.csw, UMS_STATUS_GOOD);
	data_cbw_wait_next();
   	data_sense_cur_init();
    sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;

}

static void sto_drv_scsi_read_format(void *cbw);
static void sto_drv_scsi_read_format(void *cbw)
{
	bool lun_present;
	unsigned char lun,page_code;
	int div,mul,ll;

    unsigned int length;
    unsigned int block_size;
    unsigned int block_count;
    unsigned int block_size_mult;

	lun = data_cbw_get_lun(cbw);
	lun_present = sto_drv_dev_is_present(lun);

    logf("scsi read_format_capacity %d", lun);

    if (!lun_present) {
        sto_drv_epn_send_nb(NULL, 0);
        data_sense_cur_not_ready();
        sto_state = SENDING_FAILED_RESULT;
        return;
    }

#ifdef USB_USE_RAMDISK
    block_size = SECTOR_SIZE;
    block_count = RAMDISK_SIZE;
#else
    storage_get_info(lun,&info);
    block_size=info.sector_size;
    block_count=info.num_sectors;
#endif
    block_size_mult = 1;
#ifdef MAX_LOG_SECTOR_SIZE
    block_size_mult = disk_sector_multiplier;
#endif

    div = block_count / block_size_mult - 1;
    mul = block_size * block_size_mult;
    ll = data_read_format_capacity_data(sto_tb.format_capacity_data,div,mul);
    sto_drv_epn_send_nb(sto_tb.format_capacity_data, MIN(ll, length));

    sto_state = SENDING_RESULT;
}

static void sto_drv_scsi_read_capacity(void *cbw);
static void sto_drv_scsi_read_capacity(void *cbw)
{
	bool lun_present;
	unsigned char lun,page_code;
	int div,mul,ll;

    unsigned int length;
    unsigned int block_size;
    unsigned int block_count;
    unsigned int block_size_mult;

	lun = data_cbw_get_lun(cbw);
	lun_present = sto_drv_dev_is_present(lun);


    logf("scsi read_capacity %d", lun);

    if (!lun_present) {
        sto_drv_epn_send_nb(NULL, 0);
        sto_state = SENDING_FAILED_RESULT;
        data_sense_cur_not_ready();
        return;
    }

#ifdef USB_USE_RAMDISK
    block_size = SECTOR_SIZE;
    block_count = RAMDISK_SIZE;
#else
    storage_get_info(lun,&info);
    block_size=info.sector_size;
    block_count=info.num_sectors;
#endif
    block_size_mult = 1;
#ifdef MAX_LOG_SECTOR_SIZE
    block_size_mult = disk_sector_multiplier;
#endif


    /* "block count" actually means "number of last block" */
	div = block_count / block_size_mult - 1;
	mul = block_size * block_size_mult;

	ll = data_read_capacity_data(sto_tb.capacity_data,div,mul);
    sto_drv_epn_send_nb(sto_tb.capacity_data, MIN(ll, length));
    sto_state = SENDING_RESULT;
}

static void sto_drv_scsi_read_10(void *cbw);
static void sto_drv_scsi_read_10(void *cbw)
{
	bool lun_present;
	unsigned char lun,page_code;
	int div,mul,ll;

    unsigned int length;
    unsigned int block_size;
    unsigned int block_count;
    unsigned int block_size_mult;

	lun = data_cbw_get_lun(cbw);
	lun_present = sto_drv_dev_is_present(lun);

    logf("scsi read10 %d %d\n\r", lun, lun_present);
    if (!lun_present) {
        sto_drv_epn_send_nb(NULL, 0);
        data_sense_cur_not_ready();
        sto_state = SENDING_FAILED_RESULT;
        return;
    }

#ifdef USB_USE_RAMDISK
    block_size = SECTOR_SIZE;
    block_count = RAMDISK_SIZE;
#else
    storage_get_info(lun,&info);
    block_size=info.sector_size;
    block_count=info.num_sectors;
#endif
    block_size_mult = 1;
#ifdef MAX_LOG_SECTOR_SIZE
    block_size_mult = disk_sector_multiplier;
#endif

    data_cmd_read_10(sto_tb.transfer_buffer,cbw,block_size_mult);
    ll = data_cmd_get_length();
    if ( ll > block_count) {
    	data_csw_send(sto_tb.csw, UMS_STATUS_FAIL);
    	data_cbw_wait_next();
    	data_sense_cur_illegal();
        sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
    }
    else
    {
    	data_cmd_read_sector();
        data_cmd_send_and_read_next();
    }
}

static void sto_drv_scsi_write_10(void *cbw);
static void sto_drv_scsi_write_10(void *cbw)
{
	bool lun_present;
	unsigned char lun,page_code;
	int div,mul,ll;

    unsigned int length;
    unsigned int block_size;
    unsigned int block_count;
    unsigned int block_size_mult;

	lun = data_cbw_get_lun(cbw);
	lun_present = sto_drv_dev_is_present(lun);

    logf("scsi write10 %d\n\r", lun);
    if (!lun_present) {
    	data_csw_send(sto_tb.csw, UMS_STATUS_FAIL);
        sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
    	data_cbw_wait_next();
    	data_sense_cur_not_ready();
        return;
    }

#ifdef USB_USE_RAMDISK
    block_size = SECTOR_SIZE;
    block_count = RAMDISK_SIZE;
#else
    storage_get_info(lun,&info);
    block_size=info.sector_size;
    block_count=info.num_sectors;
#endif
    block_size_mult = 1;
#ifdef MAX_LOG_SECTOR_SIZE
    block_size_mult = disk_sector_multiplier;
#endif

    data_cmd_write_10(sto_tb.transfer_buffer,cbw,block_size_mult);

    /* expect data */
    ll = data_cmd_get_length();
    if ( ll > block_count) {
    	data_csw_send(sto_tb.csw, UMS_STATUS_FAIL);
    	data_cbw_wait_next();
        data_sense_cur_illegal();
        sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
    }
    else
    {
        if (data_cmd_get_sector() >= 289)             //TODO
        {

        }
       data_cmd_write_10_read();
       sto_state = RECEIVING_BLOCKS;
    }

}

static void sto_drv_scsi_write_buffer(void *cbw);
static void sto_drv_scsi_write_buffer(void *cbw)
{
	bool i;
	logf("SCSI_WRITE_BUFFER\n\r");
	i = data_cbw_is_rec_time(cbw);
    if (!i)
    	return;
	sto_drv_epn_recv(sto_tb.transfer_buffer, 12);
    sto_state = RECEIVING_TIME;
}

static void sto_drv_scsi_default(void *cbw);
static void sto_drv_scsi_default(void *cbw)
{
    //  btr_printf(0,"scsi unknown cmd\n\r");break;
	data_csw_send(sto_tb.csw, UMS_STATUS_FAIL);
    sto_state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
	data_cbw_wait_next();
    data_sense_cur_illegal();
}
/*================================================================*/
#define SCSI_TEST_UNIT_READY      0x00
#define SCSI_INQUIRY              0x12
#define SCSI_MODE_SENSE_6         0x1a
#define SCSI_MODE_SENSE_10        0x5a
#define SCSI_REQUEST_SENSE        0x03
#define SCSI_ALLOW_MEDIUM_REMOVAL 0x1e
#define SCSI_READ_CAPACITY        0x25
#define SCSI_READ_FORMAT_CAPACITY 0x23
#define SCSI_READ_10              0x28
#define SCSI_WRITE_10             0x2a
#define SCSI_START_STOP_UNIT      0x1b
#define SCSI_REPORT_LUNS          0xa0
#define SCSI_WRITE_BUFFER         0x3b

void sto_drv_scsi_handle_cbw(void * cbw);
void sto_drv_scsi_handle_cbw(void * cbw) {
    /* USB Mass Storage assumes LBA capability.
     TODO: support 48-bit LBA */
    if (!data_cbw_is_signed(cbw)) {
    	sto_drv_epn_stall();
        return;
    }

    /* Clear the signature to prevent possible bugs elsewhere
     * to trigger a second execution of the same command with
     * bogus data */
    data_cmd_save_cbw(cbw);

    //logf("cbw->command_block[0]=%x \n\r", cbw->command_block[0]);
    //logf("*%x_%x\n\r", cbw->command_block[0], state);
	unsigned char cmd0;
	cmd0 = data_cbw_get_command_block(cbw,0);
    switch (cmd0)
    {
    case SCSI_TEST_UNIT_READY:
    	sto_drv_scsi_test_unit(cbw);
        break;
    case SCSI_REPORT_LUNS:
    	sto_drv_scsi_report_luns(cbw);
        break;
    case SCSI_INQUIRY:
    	sto_drv_scsi_inquiry(cbw);
        break;
    case SCSI_REQUEST_SENSE:
    	sto_drv_scsi_request_sense(cbw);
        break;
    case SCSI_MODE_SENSE_10:
    	sto_drv_scsi_mode_sense_10(cbw);
        break;
    case SCSI_MODE_SENSE_6:
    	sto_drv_scsi_mode_sense_6(cbw);
        break;
    case SCSI_START_STOP_UNIT:
    	sto_drv_scsi_stop_unit(cbw);
        break;
    case SCSI_ALLOW_MEDIUM_REMOVAL:
    	sto_drv_scsi_allow_removal(cbw);
		break;
    case SCSI_READ_FORMAT_CAPACITY:
    	sto_drv_scsi_read_format(cbw);
        break;
    case SCSI_READ_CAPACITY:
    	sto_drv_scsi_read_capacity(cbw);
        break;
    case SCSI_READ_10:
    	sto_drv_scsi_read_10(cbw);
        break;
    case SCSI_WRITE_10:
    	sto_drv_scsi_write_10(cbw);
        break;
    case SCSI_WRITE_BUFFER:
    	sto_drv_scsi_write_buffer(cbw);
        break;
    default:
    	sto_drv_scsi_default(cbw);
		break;
    }
}

/*================================================================*/

/* end of drv_scsi.c */
