/*---------------------------
 * svr.h
 *  Created on: Aug 10, 2017
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#ifndef SVR_H_
#define SVR_H_

extern void app_svr_init_skt(void);
extern void app_svr_free_skt(void);
extern void app_svr_recv_frm(char *frm,int w,int h);
extern void app_svr_send_frm(char *frm,int w,int h);
#endif 
/* end of svr.h */
