/*---------------------------
 * clt.h
 *  Created on: Aug 11, 2017
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#ifndef CLT_H_
#define CLT_H_

extern void app_clt_init_skt(void);
extern void app_clt_free_skt(void);
extern void app_clt_send_frm(char *frm,int w,int h);
extern void app_clt_recv_frm(char *frm,int w,int h);

#endif 
/* end of clt.h */
