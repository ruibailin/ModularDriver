/*---------------------------
 * drv_frame.h
 *  Created on: Jul 8, 2017
 *      Author: Bailin Rui
 *          ×÷Õß£ºÜÇ°ØÁÖ
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#ifndef DRV_PFM_DRIVER_PFM_DRIVER_H_
#define DRV_PFM_DRIVER_PFM_DRIVER_H_

extern int pfm_reg_dev_number(int *major,void *no);
extern void pfm_set_cdev_file_ops(void *cdev);
extern int pfm_set_drv_isr(int irq,void *data);
extern void pfm_set_cdev_file_ops(void *cdev);
#endif 
/* end of drv_frame.h */
