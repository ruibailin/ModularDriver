/*---------------------------
 * ram_rw_addr.c
 *  Created on: Jun 26, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *Save and get void * from ram.
 *Good for both 64 bit and 32 bit address
 *
 *
 *---------------------------
 */

#include "c_share.h"
#include "ram_rw_func.h"

#if	!IVE_UNIT_TEST
/**************************************************/
void *ram_read_addr(void *ram);
void *ram_read_addr(void *ram)
{
	void *ptr;
	ptr=(void *)ram_read_dword(ram);
	return(ptr);
}

/**************************************************/
void ram_write_addr(void *ram,void *d);
void ram_write_addr(void *ram,void *d)
{
	ram_write_dword(ram,(DWORD)d);
}

#endif

/* end of ram_rw_addr.c */
