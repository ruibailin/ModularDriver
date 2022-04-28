
/*------------------------------------
 * command.c
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

#include "../driver/state.h"
/*================================================================*/
#define CBW_SIGNATURE            0x43425355
#define CSW_SIGNATURE            0x53425355

#define htole32(x) (x)

struct command_status_wrapper {
    unsigned int signature;
    unsigned int tag;
    unsigned int data_residue;
    unsigned char status;
}__attribute__ ((packed));

struct command_block_wrapper {
    unsigned int signature;
    unsigned int tag;
    unsigned int data_transfer_length;
    unsigned char flags;
    unsigned char lun;
    unsigned char command_length;
    unsigned char command_block[16];
}__attribute__ ((packed));

struct current_command{
    unsigned int sector;
    unsigned int count;
    unsigned int orig_count;
    unsigned int cur_cmd;
    unsigned int tag;
    unsigned int lun;
    unsigned char *data[2];
    unsigned char data_select;
    unsigned int last_result;
};
static struct current_command cur_cmd;
/*================================================================*/
static void fill_sector(int sector_no, char *buf)
{
	if (sector_no == 1)
	{
	    buf[0] = 0xF8;
	    buf[1] = 0xFF;
	    buf[2] = 0xFF;
	    buf[3] = 0xFF;
        return;
	}
	if (sector_no == 2) {
	    buf[0] = 0xF8;
	    buf[1] = 0xFF;
	    buf[2] = 0xFF;
	    buf[3] = 0xFF;
        return;
	}
    /*little endding*/
    if (sector_no != 0)
        return;
    buf[0] = 0xEB;
    buf[1] = 0x3C;
    buf[2] = 0x90;

    buf[3] = 'M';
    buf[4] = 'S';
    buf[5] = 'D';
    buf[6] = 'O';
    buf[7] = 'S';
    buf[8] = '5';
    buf[9] = '.';
    buf[10] = '0';

    buf[11] = 0x00;
    buf[12] = 0x02;
    buf[13] = 0x01;
    buf[14] = 0x01;
    buf[15] = 0x00;
    buf[16] = 0x01;
    buf[17] = 0x00;
    buf[18] = 0x02;
    buf[19] = 0x00;
    buf[20] = 0x00;
    buf[21] = 0xF8;
    buf[22] = 0x00;
    buf[23] = 0x01;
    buf[24] = 0x3F;
    buf[25] = 0x00;
    buf[26] = 0xFF;
    buf[27] = 0x00;
    buf[28] = 0x00;
    buf[29] = 0x00;
    buf[30] = 0x00;
    buf[31] = 0x00;
    buf[32] = 0x00;
    buf[33] = 0x00;
    buf[34] = 0x01;
    buf[35] = 0x00;
    buf[36] = 0x00;
    buf[38] = 0x29;
    buf[39] = 0x54;
    buf[40] = 0xF4;
    buf[41] = 0x3B;
    buf[42] = 0x14;

    buf[43] = 'M';
    buf[44] = 's';
    buf[45] = 'd';
    buf[46] = 'o';
    buf[47] = 's';
    buf[48] = 0;
    /*FAT16*/
    buf[54] = 'F';
    buf[55] = 'A';
    buf[56] = 'T';
    buf[57] = '1';
    buf[58] = '6';
    buf[59] = 0;

    buf[510] = 0x55;
    buf[511] = 0xAA;
}

/*================================================================*/
unsigned int file_len = 0;
unsigned int file_len_count = 0;
unsigned char file_idx = 0;
char 	*usb_core_databuf;
extern bool 	usb_file_section_ok;
int data_cmd_send_next_sector(void);
int data_cmd_send_next_sector()
{
	int send_csw;
	send_csw =0 ;
    unsigned int next_sector = cur_cmd.sector + (WRITE_BUFFER_SIZE / SECTOR_SIZE);
    unsigned int next_count = cur_cmd.count - MIN(cur_cmd.count, WRITE_BUFFER_SIZE/SECTOR_SIZE);
    int next_select = !cur_cmd.data_select;

    if (next_count != 0) {
        /* Ask the host to send more, to the other buffer */
    	sto_drv_epn_recv(cur_cmd.data[next_select], MIN(WRITE_BUFFER_SIZE, next_count*SECTOR_SIZE));
        sto_state = RECEIVING_BLOCKS;
    }

    /* Now write the data that just came in, while the host is
     sending the next bit */
#ifdef USB_USE_RAMDISK
    //BTR_USB_MEMCPY(ramdisk_buffer + cur_cmd.sector*SECTOR_SIZE,
    //cur_cmd.data[cur_cmd.data_select],
    //MIN(WRITE_BUFFER_SIZE/SECTOR_SIZE, cur_cmd.count)*SECTOR_SIZE);
    if (cur_cmd.sector >= 289)                        //TODO
    {
        //btr_asm_memcpy(ramdisk_buffer + file_len_count,
        //cur_cmd.data[cur_cmd.data_select],
        //MIN(WRITE_BUFFER_SIZE/SECTOR_SIZE, cur_cmd.count)*SECTOR_SIZE);

    	usb_core_databuf = (char *) cur_cmd.data[cur_cmd.data_select];

        file_len_count += SECTOR_SIZE;
        usb_file_section_ok = true;
    }

    if (cur_cmd.sector == 257)                        //root directory
    {
        unsigned int aw, bw, cw, dw;
        aw = (unsigned int) cur_cmd.data[cur_cmd.data_select][95 + (file_idx * 96)] << 24;
        bw = (unsigned int) cur_cmd.data[cur_cmd.data_select][94 + (file_idx * 96)] << 16;
        cw = (unsigned int) cur_cmd.data[cur_cmd.data_select][93 + (file_idx * 96)] << 8;
        dw = (unsigned int) cur_cmd.data[cur_cmd.data_select][92 + (file_idx * 96)] << 0;
        file_len = (aw | bw | cw | dw);
        if (file_len == 0)
            file_len = 0xffffffff;
    }

#else
    int result = USBSTOR_WRITE_SECTORS_FILTER();

    if (result == 0) {
        result = storage_write_sectors(IF_MD2(cur_cmd.lun),
                cur_cmd.sector,
                MIN(WRITE_BUFFER_SIZE/SECTOR_SIZE, cur_cmd.count),
                cur_cmd.data[cur_cmd.data_select]);
    }

    if(result != 0) {
    	data_csw_send(tb.csw, UMS_STATUS_FAIL);
        state = WAITING_FOR_CSW_COMPLETION_OR_COMMAND;
    	data_cbw_wait_next();
    	data_sense_cur_error();
        return 0;
    }
#endif

    if (next_count == 0) {
        if (cur_cmd.sector >= 289)                        //TODO
        {
            //btr_printf(0,"file length is %x\r\n", file_len);
            //btr_printf(0,"data:[%x, %x, %x, %x]\n\r",
            //ramdisk_buffer[0],ramdisk_buffer[1],
            //ramdisk_buffer[2],ramdisk_buffer[3]);

            //btr_printf(0,"data2:[%x, %x, %x, %x] %d\n\r",
            //cur_cmd.data[cur_cmd.data_select][0],cur_cmd.data[cur_cmd.data_select][1],
            //cur_cmd.data[cur_cmd.data_select][2],cur_cmd.data[cur_cmd.data_select][3], (cur_cmd.count - next_count + 1));

            if (file_len_count >= file_len) {
                btr_printf(0,"Transfer done\r\n");
                //btr_printf(0,"Transfer done file_len_count = 0x%x , file_len = 0x%x\r\n", file_len_count, file_len);
                file_len_count = 0;
                file_idx++;
            }
        }
        //btr_msecs_delay(3000);
        send_csw =1;
    }

    /* Switch buffers for the next one */
    cur_cmd.data_select = !cur_cmd.data_select;
    cur_cmd.sector = next_sector;
    cur_cmd.count = next_count;

    return send_csw;

}

void data_cmd_send_and_read_next(void);
void data_cmd_send_and_read_next(void)
{

    int result = USBSTOR_READ_SECTORS_FILTER();

    if (result != 0 && cur_cmd.last_result == 0)
        cur_cmd.last_result = result;

    fill_sector(cur_cmd.sector, (char *) cur_cmd.data[cur_cmd.data_select]);
    sto_drv_epn_recv(cur_cmd.data[cur_cmd.data_select], MIN(READ_BUFFER_SIZE, cur_cmd.count*SECTOR_SIZE));
    sto_state = RECEIVING_BLOCKS;

    /* Switch buffers for the next one */
    cur_cmd.data_select = !cur_cmd.data_select;

    cur_cmd.sector += (READ_BUFFER_SIZE / SECTOR_SIZE);
    cur_cmd.count -= MIN(cur_cmd.count, READ_BUFFER_SIZE/SECTOR_SIZE);

    if (cur_cmd.count != 0) {
        /* already read the next bit, so we can send it out immediately when the
         * current transfer completes.  */
#ifdef USB_USE_RAMDISK
        //BTR_USB_MEMCPY(cur_cmd.data[cur_cmd.data_select],
        //        ramdisk_buffer + cur_cmd.sector*SECTOR_SIZE,
        //        MIN(READ_BUFFER_SIZE/SECTOR_SIZE, cur_cmd.count)*SECTOR_SIZE);

        BTR_USB_MEMSET(cur_cmd.data[cur_cmd.data_select], 0, MIN(READ_BUFFER_SIZE/SECTOR_SIZE,cur_cmd.count) * SECTOR_SIZE);
#else
        result = storage_read_sectors(IF_MD2(cur_cmd.lun,)
                cur_cmd.sector,
                MIN(READ_BUFFER_SIZE/SECTOR_SIZE, cur_cmd.count),
                cur_cmd.data[cur_cmd.data_select]);
        if(cur_cmd.last_result == 0)
        cur_cmd.last_result = result;

#endif
    }
}

/*================================================================*/
void data_csw_send(void *data,int status);
void data_csw_send(void *data,int status)
{
	struct command_status_wrapper *csw =(struct command_status_wrapper *)data;

    csw->signature = htole32(CSW_SIGNATURE);
    csw->tag = cur_cmd.tag;
    csw->data_residue = 0;
    csw->status = status;

    sto_drv_epn_send(data, sizeof(struct command_status_wrapper));
}

unsigned char data_cbw_get_page_code(void *data);
unsigned char data_cbw_get_page_code(void *data)
{
	struct command_block_wrapper *cbw =(struct command_block_wrapper *)data;

	unsigned char page;
	page = cbw->command_block[2] & 0x3f;

	return page;
}

unsigned char data_cbw_get_command_block(void *data,int id);
unsigned char data_cbw_get_command_block(void *data,int id)
{
	struct command_block_wrapper *cbw =(struct command_block_wrapper *)data;

	unsigned char page;
	page = cbw->command_block[id];

	return page;
}

/*================================================================*/
#define letoh32(x)	(x)
bool data_cbw_is_signed(void *data);
bool data_cbw_is_signed(void *data)
{
	struct command_block_wrapper *cbw =(struct command_block_wrapper *)data;
    if (letoh32(cbw->signature) == CBW_SIGNATURE)
    	return true;
    else
    	return false;
}

void data_cmd_save_cbw(void *data);
void data_cmd_save_cbw(void *data)
{
	struct command_block_wrapper *cbw =(struct command_block_wrapper *)data;
    cbw->signature = 0;
    cur_cmd.tag = cbw->tag;
    cur_cmd.lun = cbw->lun;
    cur_cmd.cur_cmd = cbw->command_block[0];
}

#define MAX_CBW_SIZE 64
void data_cbw_wait_next(void);
void data_cbw_wait_next()
{
	/* Already start waiting for the next command */
	sto_drv_tran_def_buffer();
	//usb_drv_recv(ep_out, cbw_buffer, MAX_CBW_SIZE);
    /* The next completed transfer will be either the CSW one
     * or the new command */
}

bool data_cbw_is_rec_time(void *cmd);
bool data_cbw_is_rec_time(void *cmd)
{
	struct command_block_wrapper *cbw = (struct command_block_wrapper *)cmd;
	if (cbw->command_block[1] != 1)
		return 0;
	if (cbw->command_block[2] != 0)
		return 0;
	if (cbw->command_block[3] != 0x0c)
		return 0;
	if (cbw->command_block[4] != 0)
		return 0;
	if (cbw->command_block[5] != 0)
		return 0;
	if (cbw->command_block[6] != 0)
		return 0;
	if (cbw->command_block[7] != 0)
		return 0;
	if ((cbw->command_block[8] != 0) && (cbw->command_block[8] != 0x0c))
		return 0;
	if (cbw->command_block[9] != 0)
		return 0;

	return 1;
}

void data_cmd_write_10(void *transfer_buffer,void *cmd,int block_size);
void data_cmd_write_10(void *transfer_buffer,void *cmd,int block_size)
{
	struct command_block_wrapper *cbw = (struct command_block_wrapper *)cmd;

    cur_cmd.data[0] = transfer_buffer + 512;
    cur_cmd.data[1] = transfer_buffer + 512 * 2;
    cur_cmd.data_select = 0;

    unsigned int aw, bw, cw, dw;
    aw = (unsigned int) cbw->command_block[2] << 24;
    bw = (unsigned int) cbw->command_block[3] << 16;
    cw = (unsigned int) cbw->command_block[4] << 8;
    dw = (unsigned int) cbw->command_block[5] << 0;
    cur_cmd.sector = block_size * (aw | bw | cw | dw);
    cur_cmd.count = block_size * (cbw->command_block[7] << 8 | cbw->command_block[8]);

    //btr_printf(0,"SCSI_WRITE_10 %d %d\n\r", cur_cmd.sector, cur_cmd.count);
    //CON_PRINTF('#');
    btr_printf(0,"W_%08X_%08X\r\n", cur_cmd.sector, cur_cmd.count);

    cur_cmd.orig_count = cur_cmd.count;
}

unsigned int data_cmd_get_count(void);
unsigned int data_cmd_get_count()
{
	return cur_cmd.count;
}

unsigned int data_cmd_get_last_result(void);
unsigned int data_cmd_get_last_result()
{
	return cur_cmd.last_result;
}

int data_cmd_get_sector(void);
int data_cmd_get_sector()
{
	return cur_cmd.sector;
}

int data_cmd_get_length(void);
int data_cmd_get_length()
{
	return cur_cmd.sector+cur_cmd.count;

}

unsigned char data_cbw_get_length(void *data);
unsigned char data_cbw_get_length(void *data)
{
	struct command_block_wrapper *cbw = (struct command_block_wrapper *)data;
	return cbw->command_length;

}

unsigned char data_cbw_get_lun(void *data);
unsigned char data_cbw_get_lun(void *data)
{
	unsigned char lun;
	struct command_block_wrapper *cbw;
	cbw = (struct command_block_wrapper *)data;

	lun = cbw->lun;
#ifdef USB_HIDE_FIRST_DRIVE
    lun++;
#endif
	return lun;
}

#define USB_WRITE_BUFFER_SIZE (512)
#ifdef USB_WRITE_BUFFER_SIZE
#define WRITE_BUFFER_SIZE USB_WRITE_BUFFER_SIZE
#else
#if (CONFIG_STORAGE & STORAGE_SD)
#if CONFIG_CPU == AS3525
/* We'd need to implement multidescriptor dma for sizes >65535 */
#define WRITE_BUFFER_SIZE (1024*63)
#else
#define WRITE_BUFFER_SIZE (1024*64)
#endif /* CONFIG_CPU == AS3525 */
#else
#define WRITE_BUFFER_SIZE (1024*24)
#endif /* (CONFIG_STORAGE & STORAGE_SD) */
#endif /* USB_WRITE_BUFFER_SIZE */

#ifndef SECTOR_SIZE
#define SECTOR_SIZE 512
#endif

void data_cmd_write_10_read(void);
void data_cmd_write_10_read()
{
	sto_drv_epn_recv(cur_cmd.data[0], MIN(WRITE_BUFFER_SIZE, cur_cmd.count*SECTOR_SIZE));

}

#define READ_BUFFER_SIZE (512)

void data_cmd_read_10(void *transfer_buffer,void *cmd,int block_size);
void data_cmd_read_10(void *transfer_buffer,void *cmd,int block_size)
{
	struct command_block_wrapper *cbw = (struct command_block_wrapper *)cmd;

    cur_cmd.data[0] = transfer_buffer;
    cur_cmd.data[1] = ((unsigned char *)transfer_buffer) + READ_BUFFER_SIZE;                //[READ_BUFFER_SIZE];
    cur_cmd.data_select = 0;
    //btr_printf(0,"####0 %x %x %x %x %x %x %x\n\r", cbw->command_block[2],
    //cbw->command_block[3], cbw->command_block[4], cbw->command_block[5],
    //cbw->command_block[7], cbw->command_block[8], cur_cmd.sector);
    unsigned int a, b, c, d;
    a = (unsigned int) cbw->command_block[2] << 24;
    b = (unsigned int) cbw->command_block[3] << 16;
    c = (unsigned int) cbw->command_block[4] << 8;
    d = (unsigned int) cbw->command_block[5] << 0;

    cur_cmd.sector = block_size * (a | b | c | d);
    //((unsigned int)cbw->command_block[2] << 24 |
    // (unsigned int)cbw->command_block[3] << 16 |
    // (unsigned int)cbw->command_block[4] << 8  |
    // (unsigned int)cbw->command_block[5] );

    cur_cmd.count = block_size * (cbw->command_block[7] << 8 | cbw->command_block[8]);

    //cur_cmd.sector = 0;
    //cur_cmd.count = 1;
    cur_cmd.orig_count = cur_cmd.count;

    // btr_printf(0,"scsi read %d %d\n\r", cur_cmd.sector, cur_cmd.count);
    btr_printf(0,"R_%08X_%08X\r\n", cur_cmd.sector, cur_cmd.count);
    //CON_PUTCH ('.');
}

void data_cmd_read_sector(void);
void data_cmd_read_sector()
{
#ifdef USB_USE_RAMDISK
            //BTR_USB_MEMCPY(cur_cmd.data[cur_cmd.data_select],
            //ramdisk_buffer + cur_cmd.sector*SECTOR_SIZE,
            //MIN(READ_BUFFER_SIZE/SECTOR_SIZE,cur_cmd.count)*SECTOR_SIZE);
            BTR_USB_MEMSET(cur_cmd.data[cur_cmd.data_select], 0, MIN(READ_BUFFER_SIZE/SECTOR_SIZE,cur_cmd.count) * SECTOR_SIZE);
            fill_sector(cur_cmd.sector, (char *) cur_cmd.data[cur_cmd.data_select]);
#else
            cur_cmd.last_result = storage_read_sectors(IF_MD2(cur_cmd.lun,)
                    cur_cmd.sector,
                    MIN(READ_BUFFER_SIZE/SECTOR_SIZE, cur_cmd.count),
                    cur_cmd.data[cur_cmd.data_select]);
#endif
}

/*================================================================*/

/* end of command.c */
