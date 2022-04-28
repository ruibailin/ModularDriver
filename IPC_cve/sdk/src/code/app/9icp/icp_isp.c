
/*---------------------------
 * zx_icp_isp.c
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

#include "zc_isp.h"

#include "c_share.h"
/**************************************************/
int icp_init_isp(void);
int icp_init_isp(void)
{
	int32_t ret = 0;
	isp_param_t  zc_isp_param;

	memset(&zc_isp_param, 0, sizeof(isp_param_t));
	zc_isp_param.online_en = ISP_ON_LINE_EN;			/*g_isp_vpe_is_online*/
    if (zc_isp_param.online_en == 0)
        zc_isp_param.isp_frame.pixelfmt = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    else
        zc_isp_param.isp_frame.pixelfmt = PIXEL_FORMAT_UYVY_PACKAGE_422;
	zc_isp_param.is_need_dump = ISP_NEED_DUMP;
	zc_isp_param.isp_frame.width = 1920;
	zc_isp_param.isp_frame.height = 1080;
	ret = zc_isp_init(&zc_isp_param);
	if (ret)
	    printf("IVE init ISP error! %d\n",ret);
	return ret;
}
/**************************************************/
int icp_start_isp(void);
int icp_start_isp(void)
{
	int ret;
	ret = zc_isp_start();
	if (ret)
	{
		printf("IVE start Isp error! %d\n",ret);
	    return ret;
	}
	ret = zc_isp_start_alg();
	zc_isp_set_fps(30);
	return ret;
}

/**************************************************/
int icp_stop_isp(void);
int icp_stop_isp(void)
{
 	return zc_isp_stop();
}

/* end of zx_icp_isp.c */
