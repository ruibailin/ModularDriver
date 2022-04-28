
/*---------------------------
 * zx_icp.h
 *  Created on: 2017年8月15日
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

#ifndef SRC_CODE_APP_9ICP_ZX_ICP_H_
#define SRC_CODE_APP_9ICP_ZX_ICP_H_

extern int icp_init_isp(void);
extern int icp_start_isp(void);
extern int icp_stop_isp(void);

extern int icp_init_sys_bind(void);
extern int icp_bind_sys_chn(void);
extern int icp_unbind_sys_chn(void);

extern void icp_frm_alloc_mem(int frm,int size);
extern int icp_frm_get_phy_addr(int frm);
extern void *icp_frm_get_vir_addr(int frm);
extern void icp_frm_free_mem(int frm);

extern int icp_init_vi_misc();

extern int icp_voe_set_vl_mode();
extern int icp_voe_open_vl_display();
extern int icp_voe_shut_vl_display();

extern int icp_set_voe_mode();

extern int icp_vpe_set_chncve_mode(void);
extern int icp_vpe_set_chncve_attr(void);
extern int icp_vpe_set_chncve_depth(void);
extern int icp_vpe_enable_chncve(void);
extern void icp_vpe_get_chncve_frm(int frm);
extern void icp_vpe_ret_chncve_frm(int frm);
extern int icp_vpe_get_frm_width(int frm);
extern int icp_vpe_get_frm_height(int frm);
extern int icp_vpe_get_frm_phy_addr(int frm);
extern void *icp_vpe_get_frm_vir_addr(int frm);

extern int icp_vpe_set_chnvoe_mode(void);
extern int icp_vpe_set_chnvoe_attr(void);
extern int icp_vpe_set_chnvoe_depth(void);
extern int icp_vpe_enable_chnvoe(void);

extern int icp_create_vpe_grp(void);
extern int icp_start_vpe_grp(void);
extern int icp_stop_vpe_grp(void);
extern int icp_destroy_vpe_grp(void);
#endif 
/* end of zx_icp.h */
