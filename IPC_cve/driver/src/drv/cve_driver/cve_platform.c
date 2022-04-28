/*---------------------------
 * cve_platform.c
 *  Created on: Jul 9, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Implement the functions
 *defined in ../pfm_driver/platform.c
 *
 *
 *
 *---------------------------
 */


#include "c_share.h"
/**************************************************/
#include <linux/ioport.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>
int pfm_drv_func(probe)(struct platform_device *pdev);
int pfm_drv_func(probe)(struct platform_device *pdev)
{
	int ret;
	long addr;
	ret=0;
	os_print("%s to run probe!\n",DRV_MODULE_NAME);
	addr=(long)pdev;
	os_print("Probe find platform device address is %lx !\n",addr);

    void __iomem *io_base;
#if TEST_WITHOUT_CVE_HW
    cve_io_init_base();
#else
    struct device_node *np;
    np = of_find_compatible_node(NULL, NULL, "zte,zx296805-opvcrm");
    if(np != pdev->dev.of_node)
    	os_print("CVE find PDEV->dev.of_node address is different from np!");
    os_print("CVE find device_node address is 0x%lx\n",np);
    os_print("CVE find PDEV->dev.of_node address is 0x%lx\n",pdev->dev.of_node);
    io_base = of_iomap(np, 0);
    cve_io_set_reset(io_base);
    os_print("CVE find reset address is 0x%lx\n",io_base);


    struct resource *res;
    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    io_base  = devm_ioremap_resource(&(pdev->dev), res);	/*或 io_base = of_iomap(pdev->dev.of_node,0);*/
    cve_io_set_base(io_base);
    os_print("CVE find hw mapped start address is 0x%lx\n",io_base);
#endif
    cve_spl_init_lock();
    io_base=cve_io_get_base();
    cve_top_set_base_addr(io_base);
    cve_wq_init_head();

    return(ret);
}

/**************************************************/
int pfm_drv_func(remove)(void *pdev);
int pfm_drv_func(remove)(void *pdev)
{
	int ret;
	ret=0;
	os_print("%s to run remove!\n",DRV_MODULE_NAME);
	return(ret);
}

/**************************************************/
void pfm_drv_func(shutdown)(void *pdev);
void pfm_drv_func(shutdown)(void *pdev)
{
	os_print("%s to run shutdown!\n",DRV_MODULE_NAME);
}



/* end of cve_platform.c */
