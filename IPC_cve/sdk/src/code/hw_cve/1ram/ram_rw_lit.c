
/*---------------------------
 * ram_rw_lit.c
 *  Created on: 2017年6月8日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *Deal with big endian and little endian issue
 *
 *
 *
 *
 *---------------------------
 */
#include "c_share.h"
#include <stdio.h>
#include <stdlib.h>
#if	!IVE_UNIT_TEST
/**************************************************/
static DWORD up_down_dword(DWORD d);
static DWORD up_down_dword(DWORD d)
{
	typedef union{
		DWORD  reg32;
		WORD   reg16[2];
		BYTE   reg8[4];
	}U_IO;
	U_IO in,out;

	in.reg32=d;

	int ii;
	for(ii=0;ii<sizeof(DWORD);ii++)
	{
		out.reg8[sizeof(DWORD)-1-ii]=in.reg8[ii];
	}
	return(out.reg32);
}

/**************************************************/
#include "../0ioctl/ioctl_cmd.h"
int ram_read_dword(void *ram);
int ram_read_dword(void *ram)
{
	int val,big;
	big=cmd_read_32(ram);
	val=up_down_dword(big);
	printf("Read %d from 0x%0x\n",ram,val);
	return(val);
}
/**************************************************/
void ram_write_dword(void *ram,int val);
void ram_write_dword(void *ram,int val)
{
	int big;
	big=up_down_dword(val);
	cmd_write_32(ram,big);
	printf("Write %d to 0x%0x\n",ram,val);
}
#endif
/* end of ram_rw_lit*/
