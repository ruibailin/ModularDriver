
/*---------------------------
 * cve_wait_queue.h
 *  Created on: 2017年7月29日
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

#ifndef SRC_DRV_CVE_DATA_CVE_WAIT_QUEUE_H_
#define SRC_DRV_CVE_DATA_CVE_WAIT_QUEUE_H_

extern void cve_wq_init_head(void);
extern void cve_wq_hung_proc(int con);
extern void cve_wq_wake_proc(int con);

#endif 
/* end of cve_wait_queue.h */
