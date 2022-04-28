
/*---------------------------
 * zx_icp_voe.c
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
#include "zc_voe.h"
int icp_set_voe_mode();
int icp_set_voe_mode()
{
	int32_t ret = 0;
	voe_pub_attr_t pub_attr;

	pub_attr.interface_timing_type = TVIF_STD_NTSC_M;
	pub_attr.interface_type        = TVOUT_VENC_CVBS;
	pub_attr.background_color      = 0x000000FF;
	ret = zc_voe_set_pub_attr(0, &pub_attr);
	if (ret)
	    printf("IVE set Voe public attribute error! %d\n",ret);
    return ret;
}

/* end of zx_icp_voe.c */
