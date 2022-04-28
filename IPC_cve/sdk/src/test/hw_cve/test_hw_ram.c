/*---------------------------
 * test_hw_ram.c
 *  Created on: Jun 9, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#include "../src/test/c_share.h"

#if  IVE_UNIT_TEST

#if TEST_HW_RAM
#include <stdio.h>
#include <stdlib.h>

/**************************************************/
static void test_ram_rw(void);
#include "../hw_cve/1ram/ram_rw_func.h"
static BYTE t_ram[8];
static void test_ram_rw(void)
{

	WORD ii,*wptr;
	DWORD jj, *dptr;

	ii=0x1234;
	wptr=(WORD *)t_ram;
	*wptr=ii;
	ram_write_word((void *)t_ram,ii);
	ii=ram_read_word((void *)t_ram);
	if(ii!=0x1234)
		printf("wrong");
	ii=*dptr;
	if(ii!=0x3412)
		printf("wrong");

	jj=0x12345678;
	dptr=(DWORD *)t_ram;
	*dptr=jj;
	ram_write_dword((void *)t_ram,jj);
	jj=ram_read_dword((void *)t_ram);
	if(jj!=0x12345678)
		printf("wrong");
	jj=*dptr;
	if(jj!=0x78563412)
		printf("wrong");
}
#endif

/**************************************************/
void test_hw_ram(void);
void test_hw_ram(void)
{
#if TEST_HW_RAM
	test_ram_rw();
#endif
}

#endif
/* end of test_hw_ram.c */
