
/*---------------------------
 * zx_icp_voe_vl.c
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
int icp_voe_set_vl_mode();
int icp_voe_set_vl_mode()
{
	int32_t ret = 0;
	uint32_t width  = VOE_CHN_WIDTH;
	uint32_t height = VOE_CHN_HEIGHT;

	voe_vl_attr_t layer_attr;
	layer_attr.disp_rect.x  = 0;
	layer_attr.disp_rect.y  = 0;
	layer_attr.disp_rect.w  = width;
	layer_attr.disp_rect.h  = height;

	layer_attr.image_size.w = width;
	layer_attr.image_size.h = height;
	layer_attr.pixel_format = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
	ret = zc_voe_vl_set_attr(0, &layer_attr);
	if (ret)
	    printf("IVE set Voe videolayer attribute error! %d\n",ret);
    return ret;
}

/**************************************************/
int icp_voe_open_vl_display();
int icp_voe_open_vl_display()
{
	int ret;
	ret = zc_voe_vl_enable(0);
	if (ret)
	    printf("IVE enable Voe videolayer error! %d\n",ret);
    return ret;
}
/**************************************************/
int icp_voe_shut_vl_display();
int icp_voe_shut_vl_display()
{
	int ret;
	ret=zc_voe_vl_disable(0);
	if (ret)
	    printf("IVE disable Voe videolayer error! %d\n",ret);
    return ret;
}

/* end of zx_icp_voe_vl.c */
