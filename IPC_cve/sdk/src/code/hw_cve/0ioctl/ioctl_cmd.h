
/*---------------------------
 * ioctl_cmd.h
 *  Created on: 2017年8月3日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *
 *
 *
 *
 *
 *---------------------------
 */

#ifndef SRC_CODE_HW_CVE_0IOCTL_IOCTL_CMD_H_
#define SRC_CODE_HW_CVE_0IOCTL_IOCTL_CMD_H_

extern void cmd_write_32(int off,int val);
extern int cmd_read_32(int off);
extern void cmd_wait_done(void);
extern void cmd_stop_wait(void);
extern void cmd_reset_asic(void);

#endif 
/* end of ioctl_cmd.h */
