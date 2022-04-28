
/*---------------------------
 * zx_icp_vpe_chn.c
 *  Created on: 2017年8月4日
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
/**************************************************/
#include "zc_vpe.h"
int icp_vpe_set_chncve_mode(void);
int icp_vpe_set_chncve_mode(void)
{
	int32_t ret  = 0;
	vpe_chn_mod_t  chn_mode;
	uint32_t chn_id = VPE_TO_CVE_CHN_ID;
	//����ͨ��ģʽ
    chn_mode.chn_work_mode = VPE_CHN_MODE_AUTO;
    chn_mode.pixel_fmt = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
	chn_mode.height = IVE_FRM_HEIGHT;
	chn_mode.width = IVE_FRM_WIDTH;
	chn_mode.compress_mode = COMPRESS_MODE_NONE;
	ret = zc_vpe_set_chn_mode(0,chn_id,&chn_mode);
	if (ret)
	    printf("IVE set Vpe channel to CVE mode error! %d\n",ret);
	return ret;
}
/**************************************************/
int icp_vpe_set_chncve_attr(void);
int icp_vpe_set_chncve_attr(void)
{
	int32_t ret  = 0;
	vpe_chn_attr_t chn_attr;
	uint32_t chn_id = VPE_TO_CVE_CHN_ID;

	chn_attr.border_enable = ZC_FALSE;
	chn_attr.flip_enable = ZC_FALSE;
	chn_attr.mirror_enable = ZC_FALSE;
	chn_attr.src_frame_rate = -1;
	chn_attr.dst_frame_rate = -1;
	chn_attr.border_cfg.bottom_width = 0;
	chn_attr.border_cfg.left_width   = 0;
	chn_attr.border_cfg.right_width  = 0;
	chn_attr.border_cfg.top_width    = 0;
	chn_attr.border_cfg.color= 0x00101010;
	ret = zc_vpe_set_chn_attr(0,chn_id,&chn_attr);
	if (ret)
	    printf("IVE set Vpe channel to CVE attribute error! %d\n",ret);
	return ret;
}

/**************************************************/
int icp_vpe_set_chncve_depth(void);
int icp_vpe_set_chncve_depth(void)
{
	int32_t ret  = 0;
	uint32_t chn_id = VPE_TO_CVE_CHN_ID;

	ret = zc_vpe_set_depth(0,chn_id,8);
	if (ret)
	    printf("IVE set Vpe buffer depth error! %d\n",ret);
	return ret;
}
/**************************************************/
int icp_vpe_enable_chncve(void);
int icp_vpe_enable_chncve(void)
{
	int32_t ret  = 0;
	uint32_t chn_id = VPE_TO_CVE_CHN_ID;

	ret =  zc_vpe_enable_chn(0,chn_id);
	if (ret)
	    printf("IVE fail to enable Vpe channel to CVE! %d\n",ret);
	return ret;
}
/**************************************************/
#define IVE_MD_MAX_FRM	16
static video_frame_t *ive_md_frm[IVE_MD_MAX_FRM];
void icp_vpe_get_chncve_frm(int frm);
void icp_vpe_get_chncve_frm(int frm)
{
	int ret;
    uint32_t grp_num = 0, chn_id = VPE_TO_CVE_CHN_ID;
    int32_t time_ms = 20000;
    ret = zc_vpe_get_chn_frame(grp_num, chn_id, ive_md_frm[frm], time_ms);
    if (ret != ZC_SUCCESS)
        printf("zc_vpe_get_chncve_frame fail, vpe_grp(%d),vpe_chn(%d),err(%#x)!\n", grp_num, chn_id, ret);
}

/**************************************************/
void icp_vpe_ret_chncve_frm(int frm);
void icp_vpe_ret_chncve_frm(int frm)
{
	int ret;
    uint32_t grp_num = 0, chn_id = VPE_TO_CVE_CHN_ID;
    int32_t time_ms = 20000;
    ret = zc_vpe_release_chn_frame(grp_num, chn_id, ive_md_frm[frm]);
    if (ret != ZC_SUCCESS)
        printf("zc_vpe_release_chncve_frame fail, vpe_grp(%d),vpe_chn(%d),err(%#x)!\n", grp_num, chn_id, ret);
}
/**************************************************/
int icp_vpe_get_frm_width(int frm);
int icp_vpe_get_frm_width(int frm)
{
	return(ive_md_frm[frm]->width);
}
/**************************************************/
int icp_vpe_get_frm_height(int frm);
int icp_vpe_get_frm_height(int frm)
{
	return(ive_md_frm[frm]->height);
}
/**************************************************/
int icp_vpe_get_frm_phy_addr(int frm);
int icp_vpe_get_frm_phy_addr(int frm)
{
	return(ive_md_frm[frm]->phyaddr_y);
}
/**************************************************/
void *icp_vpe_get_frm_vir_addr(int frm);
void *icp_vpe_get_frm_vir_addr(int frm)
{
	return(ive_md_frm[frm]->viraddr_y);
}


/* end of zx_icp_vpe_chn.c */
