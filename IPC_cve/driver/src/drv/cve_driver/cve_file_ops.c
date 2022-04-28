/*---------------------------
 * cve_file_ops.c
 *  Created on: Jul 9, 2017
 *      Author: Bailin Rui
 *          ×÷Õß£ºÜÇ°ØÁÖ
 *---------------------------
 *Implement the functions
 *defined in ../pfm_driver/file_ops.c
 *except pfm_drv_file_func(ioctl)
 *
 *---------------------------
 */


#include "c_share.h"
/**************************************************/
int pfm_drv_file_func(open)(void *pinode,void *pfile);
int pfm_drv_file_func(open)(void *pinode,void *pfile)
{
	int ret;
	ret=0;
	os_print("%s to run file open!\n",DRV_MODULE_NAME);
	return(ret);
}
/**************************************************/
int pfm_drv_file_func(release)(void *pinode,void *pfile);
int pfm_drv_file_func(release)(void *pinode,void *pfile)
{
	int ret;
	ret=0;
	os_print("%s to run file release!\n",DRV_MODULE_NAME);
	return(ret);
}

/* end of cve_file_ops.c */
