
/*---------------------------
 * zx_icp_vpe_chn_voe.c
 *  Created on: 2017年8月7日
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
int icp_vpe_set_chnvoe_mode(void);
int icp_vpe_set_chnvoe_mode(void)
{
	int32_t ret  = 0;
	vpe_chn_mod_t  chn_mode;
	uint32_t chn_id = VPE_TO_VOE_CHN_ID;
	//����ͨ��ģʽ
    chn_mode.chn_work_mode = VPE_CHN_MODE_AUTO;
    chn_mode.pixel_fmt = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
	chn_mode.height = VOE_CHN_HEIGHT;
	chn_mode.width = VOE_CHN_WIDTH;
	chn_mode.compress_mode = COMPRESS_MODE_NONE;
	ret = zc_vpe_set_chn_mode(0,chn_id,&chn_mode);
	if (ret)
	    printf("IVE set Vpe channel to VOE mode error! %d\n",ret);
	return ret;
}
/**************************************************/
int icp_vpe_set_chnvoe_attr(void);
int icp_vpe_set_chnvoe_attr(void)
{
	int32_t ret  = 0;
	vpe_chn_attr_t chn_attr;
	uint32_t chn_id = VPE_TO_VOE_CHN_ID;

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
	    printf("IVE set Vpe channel to VOE attribute error! %d\n",ret);
	return ret;
}

/**************************************************/
int icp_vpe_set_chnvoe_depth(void);
int icp_vpe_set_chnvoe_depth(void)
{
	int32_t ret  = 0;
	uint32_t chn_id = VPE_TO_VOE_CHN_ID;

	ret = zc_vpe_set_depth(0,chn_id,5);
	if (ret)
	    printf("IVE set Vpe to VOE buffer depth error! %d\n",ret);
	return ret;
}
/**************************************************/
int icp_vpe_enable_chnvoe(void);
int icp_vpe_enable_chnvoe(void)
{
	int32_t ret  = 0;
	uint32_t chn_id = VPE_TO_VOE_CHN_ID;

	ret =  zc_vpe_enable_chn(0,chn_id);
	if (ret)
	    printf("IVE fail to enable Vpe channel to VOE! %d\n",ret);
	return ret;
}
/* end of zx_icp_vpe_chn_voe.c */
