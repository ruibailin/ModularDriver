
/*---------------------------
 * cve_spinlock.h
 *  Created on: 2017年7月29日
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

#ifndef SRC_DRV_CVE_DATA_CVE_SPINLOCK_H_
#define SRC_DRV_CVE_DATA_CVE_SPINLOCK_H_


extern void cve_spl_init_lock(void);
extern void cve_spl_lock_lock(long flags);
extern void cve_spl_unlock_lock(long flags);


#endif 
/* end of cve_spinlock.h */
