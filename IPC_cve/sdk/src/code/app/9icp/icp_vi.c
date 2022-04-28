
/*---------------------------
 * zx_icp_vi.c
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
#include "zc_isp.h"
int icp_init_vi_misc();
int icp_init_vi_misc()
{
	int ret=0;
	vi_misc_param_t zc_vi_misc_param;

	memset(&zc_vi_misc_param, 0, sizeof(vi_misc_param_t));

	zc_vi_misc_param.port_type = DVP_PORT;
	zc_vi_misc_param.data_type = RAW12;
	ret = zc_vi_misc_init(&zc_vi_misc_param);
	if (ret)
	    printf("IVE init Vi_Misc error! %d\n",ret);
	return ret;
}

/* end of zx_icp_vi.c */
