
/*---------------------------
 * ram_rw_addr.c
 *  Created on: 2017年8月15日
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

#include "../../ive_test.h"
#if	IVE_UNIT_TEST
#include "../../code/hw_cve/1ram/c_share.h"
#include "../../code/hw_cve/1ram/ram_rw_func.h"
/**************************************************/
void *ram_read_addr(void *ram);
void *ram_read_addr(void *ram)
{
	void *ptr;
#ifdef	__SIZEOF_POINTER__
	#if __SIZEOF_POINTER__ == 8
	ptr=(void *)ram_read_qword(ram);
	#else
	ptr=(void *)ram_read_dword(ram);
	#endif
#else
	ptr=(void *)ram_read_dword(ram);
#endif
	return(ptr);
}
/**************************************************/
void ram_write_addr(void *ram,void *d);
void ram_write_addr(void *ram,void *d)
{
#ifdef	__SIZEOF_POINTER__
	#if __SIZEOF_POINTER__ == 8
	ram_write_qword(ram,(QWORD)d);
	#else
	ram_write_dword(ram,(DWORD)d);
	#endif
#else
	ram_write_dword(ram,(DWORD)d);
#endif
}
#endif
/* end of ram_rw_addr.c */
