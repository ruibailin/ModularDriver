
/*---------------------------
 * cve_top_reg.h
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

#ifndef SRC_DRV_CVE_DATA_CVE_TOP_REG_H_
#define SRC_DRV_CVE_DATA_CVE_TOP_REG_H_

extern void cve_top_set_base_addr(void *top);
extern int cve_top_get_irq_state(void);
extern int cve_top_get_irq_done(void);
extern int cve_top_get_irq_axi(void);
extern int cve_top_get_irq_err(void);

#endif 
/* end of cve_top_reg.h */
