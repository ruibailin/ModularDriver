
/*---------------------------
 * cve_io_base.h
 *  Created on: 2017年7月27日
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

#ifndef SRC_DRV_CVE_DATA_CVE_IO_BASE_H_
#define SRC_DRV_CVE_DATA_CVE_IO_BASE_H_

extern void cve_io_init_base(void);
extern void cve_io_set_base(void *base);
extern void *cve_io_get_base(void);
extern int cve_io_read_dword(int offset);
extern void cve_io_write_dword(int offset,int val);

#endif 
/* end of cve_io_base.h */
