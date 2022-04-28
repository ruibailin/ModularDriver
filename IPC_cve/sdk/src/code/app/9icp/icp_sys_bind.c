
/*---------------------------
 * zx_icp_sys_bind.c
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
#include "zc_sys.h"
int32_t icp_init_sys_bind(void);
int32_t icp_init_sys_bind(void)
{
	int32_t ret;
	ret = zc_sys_init();
	if (ret)
	    printf("IVE init Sys error! %d\n",ret);
    return ret;
}

/**************************************************/
int32_t icp_bind_sys_chn(void);
int32_t icp_bind_sys_chn(void)
{
	int32_t ret;
	zc_sys_chn_t src_chn;
	zc_sys_chn_t dst_chn;

	ret=ISP_ON_LINE_EN;
	if(ret == 0)
	{
		src_chn.devID = ZC_ID_ISP;
		src_chn.grpID = 0;
		src_chn.chnID = 0;
		dst_chn.devID = ZC_ID_VPE;
		dst_chn.grpID = 0;
		dst_chn.chnID = 0;
		ret = zc_sys_bind(&src_chn, &dst_chn);
	    if(ret)
			printf("Bind isp and vpe error!\n");
	}
	else
	{
	    src_chn.devID = ZC_ID_VPE;
	    src_chn.grpID = 0;
	    src_chn.chnID = VPE_TO_VOE_CHN_ID;
	    dst_chn.devID = ZC_ID_VOE;
	    dst_chn.grpID = 0;
	    dst_chn.chnID = 0;
	    ret = zc_sys_bind(&src_chn,&dst_chn);
	 	if (ret)
			printf("Bind vpe and voe error!\n");
	}
    return ret;
}
/**************************************************/
int32_t icp_unbind_sys_chn(void);
int32_t icp_unbind_sys_chn(void)
{
	int32_t ret;
	zc_sys_chn_t src_chn;
	zc_sys_chn_t dst_chn;

	ret=ISP_ON_LINE_EN;
	if(ret == 0)
	{
		src_chn.devID = ZC_ID_ISP;
		src_chn.grpID = 0;
		src_chn.chnID = 0;
		dst_chn.devID = ZC_ID_VPE;
		dst_chn.grpID = 0;
		dst_chn.chnID = 0;
		ret = zc_sys_unbind(&src_chn, &dst_chn);
	    if(ret)
			printf("UnBind isp and vpe error!\n");
	}
	else
	{
	    src_chn.devID = ZC_ID_VPE;
	    src_chn.grpID = 0;
	    src_chn.chnID = VPE_TO_VOE_CHN_ID;
	    dst_chn.devID = ZC_ID_VOE;
	    dst_chn.grpID = 0;
	    dst_chn.chnID = 0;
	    ret = zc_sys_unbind(&src_chn,&dst_chn);
	 	if (ret)
			printf("UnBind vpe and voe error!\n");
	}
	return(ret);
}
/* end of zx_icp_sys_bind.c */
