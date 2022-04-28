/*---------------------------
 * platform.c
 *  Created on: Jul 8, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Universal driver platform
 *Don't change it
 *
 *---------------------------
 */

#include "c_share.h"
/**************************************************/
#include <linux/device.h>
#include <linux/pm.h>
extern int pfm_drv_pm_suspend(struct device *dev);
extern int pfm_drv_pm_resume(struct device *dev);
extern int pfm_drv_pm_runtime_suspend(struct device *dev);
extern int pfm_drv_pm_runtime_resume(struct device *dev);
static const struct dev_pm_ops pfm_drv_pm_ops = {
    .suspend         = pfm_drv_pm_suspend,
    .resume          = pfm_drv_pm_resume,
    .runtime_suspend = pfm_drv_pm_runtime_suspend,
    .runtime_resume  = pfm_drv_pm_runtime_resume,
};

/**************************************************/
#include <linux/mod_devicetable.h>
static const struct of_device_id pfm_drv_dt_ids[] = {
        { .compatible = DRV_COMPATIBLE_NAME, },
        { }
};
/**************************************************/
#include <linux/module.h>
MODULE_DEVICE_TABLE(of, pfm_drv_dt_ids);
/**************************************************/
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
/**************************************************/
struct pfm_drv_reg
{
	dev_t *dev_no;
	struct cdev *cdev;
	struct class *cls;
	struct device *dev;
};
static struct pfm_drv_reg drv_reg;
static int drv_major=0;
/**************************************************/
#include <linux/gfp.h>
#include <linux/slab.h>
extern int pfm_drv_func(probe)(struct platform_device *pdev);

extern void *pfm_drv_alloc_dev_t(int major);
extern void pfm_cdev_set_file_ops(void *cedv);
extern int pfm_drv_clk_func(init)(struct device *dev);
extern int pfm_drv_clk_func(open)(void);
extern int pfm_drv_set_isr(int irq,void *data);
static	int pfm_drv_func_probe(struct platform_device *pdev);
static	int pfm_drv_func_probe(struct platform_device *pdev)
{
	int ret;
	ret=0;

	drv_reg.dev_no=pfm_drv_alloc_dev_t(drv_major);
	if (drv_reg.dev_no==NULL)
		goto dev_t_err;
	os_print("%s success to register dev_no %d \n",DRV_MODULE_NAME,drv_major);
	drv_major=MAJOR(*(drv_reg.dev_no));

	drv_reg.cdev=cdev_alloc();
	if(drv_reg.cdev==NULL)
		goto cdev_err;

	os_print("%s success to alloc cdev \n",DRV_MODULE_NAME);
	pfm_cdev_set_file_ops(drv_reg.cdev);
	drv_reg.cdev->owner=THIS_MODULE;
	ret=cdev_add(drv_reg.cdev,*(drv_reg.dev_no),1);
	if(ret!=0)
		goto cdev_err;

	os_print("%s success to add cdev \n",DRV_MODULE_NAME);
	drv_reg.cls=class_create(THIS_MODULE,DRV_MODULE_NAME);		/*"sys/class/...*/
	if(drv_reg.cls==NULL)
		goto class_err;

	os_print("%s success to create class \n",DRV_MODULE_NAME);
	drv_reg.dev=device_create(drv_reg.cls,NULL,*(drv_reg.dev_no),"%s",DRV_MODULE_NAME);
	if(drv_reg.dev==NULL)
		goto device_err;

	os_print("%s success to create device \n",DRV_MODULE_NAME);
	pfm_drv_func(probe)(pdev);

	pfm_drv_clk_func(init)(&(pdev->dev));
	pfm_drv_clk_func(open)();

	pfm_drv_set_isr(CVE_INT_DONE,pdev);
	pfm_drv_set_isr(CVE_INT_ERR,pdev);


	return(ret);

device_err:
	ret++;
	os_print("%s fail to create device \n",DRV_MODULE_NAME);
	class_destroy(drv_reg.cls);
class_err:
	ret++;
	os_print("%s fail to alloc class \n",DRV_MODULE_NAME);
	cdev_del(drv_reg.cdev);
cdev_err:
	ret++;
	os_print("%s fail to alloc cdev \n",DRV_MODULE_NAME);
	unregister_chrdev_region(*(drv_reg.dev_no), 1);
dev_t_err:
	ret++;
	os_print("%s fail to register dev_no %d \n",DRV_MODULE_NAME,drv_major);
	kfree(drv_reg.dev_no);
	return(ret);
}
/**************************************************/
extern int pfm_drv_func(remove)(struct platform_device *pdev);
extern int pfm_drv_clk_func(shut)(void);
static	int pfm_drv_func_remove(struct platform_device *pdev);
static	int pfm_drv_func_remove(struct platform_device *pdev)
{
	pfm_drv_func(remove)(pdev);
	pfm_drv_clk_func(shut)();

	os_print("%s go to remove device \n",DRV_MODULE_NAME);
	device_destroy(drv_reg.cls,*(drv_reg.dev_no));
	os_print("%s go to remove class \n",DRV_MODULE_NAME);
	class_destroy(drv_reg.cls);
	os_print("%s go to remove cdev \n",DRV_MODULE_NAME);
	cdev_del(drv_reg.cdev);
	os_print("%s go to remove dev_t \n",DRV_MODULE_NAME);
	unregister_chrdev_region(*(drv_reg.dev_no), 1);
	kfree(drv_reg.dev_no);
	return(0);
}

/**************************************************/
extern void pfm_drv_func(shutdown)(struct platform_device *pdev);
static	void pfm_drv_func_shutdown(struct platform_device *pdev);
static	void pfm_drv_func_shutdown(struct platform_device *pdev)
{
	pfm_drv_func(shutdown)(pdev);
}

/**************************************************/
static struct platform_driver pfm_drv = {
    .driver = {
        .name   = DRV_MODULE_NAME,
        .owner  = THIS_MODULE,
        .pm     = &pfm_drv_pm_ops,
        .of_match_table = pfm_drv_dt_ids,
    },
    .probe      = pfm_drv_func_probe,
    .remove     = pfm_drv_func_remove,
    .shutdown   = pfm_drv_func_shutdown,
};

/**************************************************/
int drv_module_func(init)(void);
int drv_module_func(init)()
{
	int ret;
	os_print("%s go to register driver!\n",DRV_MODULE_NAME);
	ret=platform_driver_register(&pfm_drv);
    if (ret)
        os_print("%s fail to register driver,error is %d!\n",DRV_MODULE_NAME,ret);
	return(ret);
}
/**************************************************/
void drv_module_func(exit)(void);
void drv_module_func(exit)()
{
    os_print("%s go to unregister driver!\n",DRV_MODULE_NAME);
	platform_driver_unregister(&pfm_drv);
}
/* end of platform.c */
