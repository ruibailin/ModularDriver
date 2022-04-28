
/*---------------------------
 * zx_icp_sys_mmm.c
 *  Created on: 2017年8月6日
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

#include "c_share.h"

#define IVE_MD_MAX_FRM	16
static	int phy_addr[IVE_MD_MAX_FRM];
static  void *vir_addr[IVE_MD_MAX_FRM];
static  int mem_size[IVE_MD_MAX_FRM];
/**************************************************/
#include "zc_sys.h"
void icp_frm_alloc_mem(int frm,int size);
void icp_frm_alloc_mem(int frm,int size)
{
	int ret;
	mem_size[frm]=size;
	ret=zc_sys_mmm_alloc(&phy_addr[frm],(void **)&vir_addr[frm],"ive_md",size);
	if(ret)
        printf("zc_sys_mmm_alloc fail 0x%x, line(%d)\n", ret, __LINE__);
}

/**************************************************/
int icp_frm_get_phy_addr(int frm);
int icp_frm_get_phy_addr(int frm)
{
	return(phy_addr[frm]);
}
/**************************************************/
void *icp_frm_get_vir_addr(int frm);
void *icp_frm_get_vir_addr(int frm)
{
	return(vir_addr[frm]);
}
/**************************************************/
void icp_frm_free_mem(int frm);
void icp_frm_free_mem(int frm)
{
	int ret;
	ret=zc_sys_mmm_free(phy_addr[frm],vir_addr[frm],mem_size[frm]);
    if (ret)
        printf("zc_sys_mmm_free fail 0x%x, line(%d)\n", ret, __LINE__);
}

/* end of zx_icp_sys_mmm.c */
