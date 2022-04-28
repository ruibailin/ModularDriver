
/*---------------------------
 * zx_icp_vpe_grp.c
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
int icp_create_vpe_grp(void);
int icp_create_vpe_grp(void)
{
	int32_t ret = 0;
	vpe_grp_attr_t grp_attr;

	//��������or����ģʽ
	grp_attr.online_mode = ISP_ON_LINE_EN;		/*g_isp_vpe_is_online;*/
	if (grp_attr.online_mode == 0)
		grp_attr.pixel_fmt = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
	else
	    grp_attr.pixel_fmt = PIXEL_FORMAT_YUV_SEMIPLANAR_422;

	grp_attr.width = 1920;
	grp_attr.height = 1080;
	//����GROUP
	ret = zc_vpe_create_grp(0, &grp_attr);
	if (ret)
	    printf("IVE create Vpe group error! %d\n",ret);

	return ret;
}

/**************************************************/
int icp_start_vpe_grp(void);
int icp_start_vpe_grp(void)
{
	int32_t ret = 0;
	ret = zc_vpe_start_grp(0);
	if (ret)
	    printf("IVE start Vpe group error! %d\n",ret);
	return ret;
}
/**************************************************/
int icp_stop_vpe_grp(void);
int icp_stop_vpe_grp(void)
{
	int32_t ret = 0;
	ret = zc_vpe_stop_grp(0);
	if (ret)
	    printf("IVE stop Vpe group error! %d\n",ret);
	return ret;
}
/**************************************************/
int icp_destroy_vpe_grp(void);
int icp_destroy_vpe_grp(void)
{
	int32_t ret = 0;
	ret = zc_vpe_destroy_grp(0);
	if (ret)
	    printf("IVE destroy Vpe group error! %d\n",ret);
	return ret;
}


/* end of zx_icp_vpe_grp.c */
