/*---------------------------
 * cve_interrupt.c
 *  Created on: Jul 9, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Implement the functions
 *defined in ../pfm_driver/interrupt.c
 *
 *
 *---------------------------
 */


#include "c_share.h"


/**************************************************/
int pfm_drv_int_func(server)(int irq, void *data);
int pfm_drv_int_func(server)(int irq, void *data)
{
	int ret;
	long flags;
	cve_spl_lock_lock(flags);

	ret=0;
	switch(irq)
	{
		case CVE_INT_DONE:
			os_print("CVE Interrupt is DONE \n");
			cve_wq_wake_proc(1);
			break;
		case CVE_INT_ERR:
			os_print("CVE Interrupt is ERR \n");
			cve_wq_wake_proc(1);
			break;
		default:
			break;
	}

	cve_spl_unlock_lock(flags);
	return(ret);
}
/* end of cve_interrupt.c */
