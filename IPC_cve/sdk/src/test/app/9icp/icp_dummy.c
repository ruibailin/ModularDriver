
/*---------------------------
 * icp_dummy.c
 *  Created on: 2017年8月15日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *Provide dummy function when do unit test in Ubuntu
 *
 *
 *
 *
 *---------------------------
 */

#include "../../ive_test.h"
#if IVE_UNIT_TEST

#if !TEST_IN_6805
#include "zc_common.h"
#include "zc_sys.h"
/**************************************************/
#include "zc_isp.h"
int32_t zc_isp_init(isp_param_t *param);
int32_t zc_isp_init(isp_param_t *param)
{
	return(1);
}
uint32_t zc_isp_start(void);
uint32_t zc_isp_start(void)
{
	return(1);
}
uint32_t zc_isp_stop(void);
uint32_t zc_isp_stop(void)
{
	return(1);
}
uint32_t zc_isp_start_alg(void);
uint32_t zc_isp_start_alg(void)
{
	return(1);
}
/**************************************************/
#include "zc_sys.h"
int32_t zc_sys_init(void);
int32_t zc_sys_init(void)
{
	return(1);
}
int32_t zc_sys_bind(zc_sys_chn_t* pstsrcchn, zc_sys_chn_t* pstdestchn);
int32_t zc_sys_bind(zc_sys_chn_t* pstsrcchn, zc_sys_chn_t* pstdestchn)
{
	return(1);
}
uint32_t zc_isp_set_fps(uint8_t fps);
uint32_t zc_isp_set_fps(uint8_t fps)
{
	return(1);
}
uint32_t zc_isp_get_fps(uint8_t *fps);
uint32_t zc_isp_get_fps(uint8_t *fps)
{
	return(1);
}
int32_t zc_sys_unbind(zc_sys_chn_t* pstsrcchn, zc_sys_chn_t* pstdestchn);
int32_t zc_sys_unbind(zc_sys_chn_t* pstsrcchn, zc_sys_chn_t* pstdestchn)
{
	return(1);
}
/**************************************************/
#include "zc_sys.h"
int32_t zc_sys_mmm_alloc(uint32_t* phyaddr, void** viraddr, const char* strmmb, uint32_t size);
int32_t zc_sys_mmm_alloc(uint32_t* phyaddr, void** viraddr, const char* strmmb, uint32_t size)
{
	return(1);
}
int32_t zc_sys_mmm_free(uint32_t phyaddr, void* viraddr, uint32_t size);
int32_t zc_sys_mmm_free(uint32_t phyaddr, void* viraddr, uint32_t size)
{
	return(1);
}
/**************************************************/
#include "zc_isp.h"
int32_t zc_vi_misc_init(vi_misc_param_t *param);
int32_t zc_vi_misc_init(vi_misc_param_t *param)
{
	return(1);
}
/**************************************************/
#include "zc_voe.h"
int32_t zc_voe_vl_set_attr(int32_t vl_id, const voe_vl_attr_t *layer_attr);
int32_t zc_voe_vl_set_attr(int32_t vl_id, const voe_vl_attr_t *layer_attr)
{
	return(1);
}
int32_t zc_voe_vl_enable(int32_t vl_id);
int32_t zc_voe_vl_enable(int32_t vl_id)
{
	return(1);
}
int32_t zc_voe_vl_enable(int32_t vl_id);
int32_t zc_voe_vl_enable(int32_t vl_id)
{
	return(1);
}
/**************************************************/
#include "zc_voe.h"
int32_t zc_voe_set_pub_attr(int32_t chn_id, const voe_pub_attr_t *pub_attr);
int32_t zc_voe_set_pub_attr(int32_t chn_id, const voe_pub_attr_t *pub_attr)
{
	return(1);
}
/**************************************************/
#include "zc_vpe.h"
int32_t zc_vpe_create_grp(uint32_t grp_num, vpe_grp_attr_t *grp_attr);
int32_t zc_vpe_create_grp(uint32_t grp_num, vpe_grp_attr_t *grp_attr)
{
	return(1);
}
int32_t zc_vpe_start_grp(uint32_t grp_num);
int32_t zc_vpe_start_grp(uint32_t grp_num)
{
	return(1);
}
int32_t zc_vpe_destroy_grp(uint32_t grp_num);
int32_t zc_vpe_destroy_grp(uint32_t grp_num)
{
	return(1);
}
int32_t zc_vpe_set_chn_mode(uint32_t grp_num,uint32_t chn_id,vpe_chn_mod_t *chn_mod);
int32_t zc_vpe_set_chn_mode(uint32_t grp_num,uint32_t chn_id,vpe_chn_mod_t *chn_mod)
{
	return(1);
}
int32_t zc_vpe_set_chn_attr(uint32_t grp_num,uint32_t chn_id,vpe_chn_attr_t *chn_attr);
int32_t zc_vpe_set_chn_attr(uint32_t grp_num,uint32_t chn_id,vpe_chn_attr_t *chn_attr)
{
	return(1);
}
int32_t zc_vpe_set_depth(uint32_t grp_num,uint32_t chn_id,uint32_t depth);
int32_t zc_vpe_set_depth(uint32_t grp_num,uint32_t chn_id,uint32_t depth)
{
	return(1);
}
int32_t zc_vpe_enable_chn(uint32_t grp_num,uint32_t chn_id);
int32_t zc_vpe_enable_chn(uint32_t grp_num,uint32_t chn_id)
{
	return(1);
}
int32_t zc_vpe_get_chn_frame(uint32_t grp_num, uint32_t chn_id,video_frame_t *frame, int32_t time_ms);
int32_t zc_vpe_get_chn_frame(uint32_t grp_num, uint32_t chn_id,video_frame_t *frame, int32_t time_ms)
{
	return(1);
}
int32_t zc_vpe_release_chn_frame(uint32_t grp_num, uint32_t chn_id,video_frame_t *frame);
int32_t zc_vpe_release_chn_frame(uint32_t grp_num, uint32_t chn_id,video_frame_t *frame)
{
	return(1);
}
#endif
#endif
/* end of icp_dummy.c */
