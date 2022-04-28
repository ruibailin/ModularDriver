
/*---------------------------
 * cve_clock.c
 *  Created on: 2017年7月26日
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

#include <linux/device.h>
#include <linux/clk.h>
#include <linux/sh_clk.h>
#include <linux/of.h>
/*#include <linux/clk-provider.h>*/

#define CVE_WCLOCK               (297000000) /* 2d_wclk: 297m, 198m, 400m, 324m */
typedef enum
{
    CVE_PCLK = 0,
    CVE_WCLK,
    NIC400_M3,
    NIC400_M5,
    MAX_CLK_NUM,
}ZX_CVE_CLK_T;

static	struct clk *clock[MAX_CLK_NUM];
static unsigned int clk_rate;
/**************************************************/
int pfm_drv_clk_func(init)(struct device *dev);
int pfm_drv_clk_func(init)(struct device *dev)
{
	int ret;
#if TEST_WITHOUT_CVE_HW
	ret = 0;
#else
	clock[CVE_PCLK]=devm_clk_get(dev,"cve_pclk");
	clock[CVE_WCLK]=devm_clk_get(dev,"cve_aclk");
	clock[NIC400_M3]=devm_clk_get(dev,"opv_nic400_m3_aclk");
	clock[NIC400_M5]=devm_clk_get(dev,"opv_nic400_m5_aclk");
	ret=of_property_read_u32(dev->of_node,"clock-frequency",&clk_rate);
	if(ret)
		os_print("CVE read clock rate error!dev_of_node is 0x%lx \n",dev->of_node);
	else
		os_print("CVE read clock rate: %d is OK!\n",clk_rate);
#endif
	return(ret);
}
/**************************************************/
int pfm_drv_clk_func(open)(void);
int pfm_drv_clk_func(open)(void)
{
	int ret;
#if TEST_WITHOUT_CVE_HW
	ret = 0;
#else
	unsigned int get_rate;
	ret=clk_prepare_enable(clock[CVE_PCLK]);
	if(ret<0)
		os_print("CVE fail to enable clock CVE_PCLK!\n");
	else
		os_print("CVE success to enable clock CVE_PCLK!\n");

	ret=clk_set_rate(clock[CVE_WCLK],clk_rate);
	if(ret)
		os_print("CVE fail to set CVE_WCLK rate,%d!\n",clk_rate);
	else
		os_print("CVE success to set CVE_WCLK rate, %d!\n",clk_rate);

	get_rate=clk_get_rate(clock[CVE_WCLK]);
	if(get_rate!=clk_rate)
		os_print("CVE fail to set CVE_WCLK rate to be %d!,error rate is %d\n",clk_rate,get_rate);

	ret=clk_prepare_enable(clock[CVE_WCLK]);
	if(ret<0)
		os_print("CVE fail to enable clock CVE_WCLK!\n");
	else
		os_print("CVE success to enable clock CVE_WCLK!\n");
	ret=clk_prepare_enable(clock[NIC400_M3]);
	if(ret<0)
		os_print("CVE fail to enable clock NIC400_M3!\n");
	else
		os_print("CVE success to enable clock NIC400_M3!\n");

	ret=clk_set_rate(clock[NIC400_M5],CVE_WCLOCK);
	if(ret)
		os_print("CVE fail to set NIC400_M5 rate,%d!\n",CVE_WCLOCK);
	get_rate=clk_get_rate(clock[NIC400_M5]);
	if(get_rate!=CVE_WCLOCK)
		os_print("CVE fail to set NIC400_M5 rate to be %d!,error rate is %d\n",CVE_WCLOCK,get_rate);
	ret=clk_prepare_enable(clock[NIC400_M5]);
	if(ret<0)
		os_print("CVE fail to enable clock NIC400_M5!\n");
	else
		os_print("CVE success to enable clock NIC400_M5!\n");
#endif
	return(ret);
}
/**************************************************/
int pfm_drv_clk_func(shut)(void);
int pfm_drv_clk_func(shut)(void)
{
	int ret;
#if TEST_WITHOUT_CVE_HW
	ret=0;
#else
	ret=0;
	clk_disable_unprepare(clock[NIC400_M5]);
	clk_disable_unprepare(clock[NIC400_M3]);
	clk_disable_unprepare(clock[CVE_WCLK]);
	clk_disable_unprepare(clock[CVE_PCLK]);
	os_print("CVE success to disable clocks !\n");
#endif
	return(ret);
}

/* end of cve_clock.c */
