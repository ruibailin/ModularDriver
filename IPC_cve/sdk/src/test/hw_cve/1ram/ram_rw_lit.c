
/*---------------------------
 * ram_rw_lit.c
 *  Created on: 2017年8月15日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *To replace code/hw_cve/1ram/ram_rw_lit.c when test
 *
 *
 *
 *
 *---------------------------
 */

#include "../../ive_test.h"
#if	IVE_UNIT_TEST
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

#if	DRV_MODE_VCE
#include "../../code/hw_cve/0ioctl/ioctl_cmd.h"
/**************************************************/
int ram_read_dword(void *ram);
int ram_read_dword(void *ram)
{
	int val,big;
	big=cmd_read_32(ram);
	val=up_dwon_dword(big);
	return(val);
}
/**************************************************/
void ram_write_dword(void *ram,int val);
void ram_write_dword(void *ram,int val)
{
	int big;
	big=up_dwon_dword(val);
	cmd_write_32(ram,big);
}
#endif

#if	USR_MODE_VCE
/**************************************************/
static WORD up_down_word(WORD d);
static WORD up_down_word(WORD d)
{
	typedef union{
		WORD   reg16;
		BYTE   reg8[2];
	}U_IO;
	U_IO in,out;

	in.reg16=d;

	int ii;
	for(ii=0;ii<sizeof(WORD);ii++)
	{
		out.reg8[sizeof(WORD)-1-ii]=in.reg8[ii];
	}
	return(out.reg16);
}
/**************************************************/
static QWORD up_down_qword(QWORD q);
static QWORD up_down_qword(QWORD q)
{
	typedef union{
		QWORD  reg64;
		BYTE   reg8[8];
	}U_IO;
	U_IO in,out;

	in.reg64=q;

	int ii;
	for(ii=0;ii<sizeof(QWORD);ii++)
	{
		out.reg8[sizeof(QWORD)-1-ii]=in.reg8[ii];
	}
	return(out.reg64);
}

/**************************************************/
WORD  ram_read_word(void *ram);
WORD  ram_read_word(void *ram)
{
	WORD big,val;
	big=*(WORD *)ram;
	val=up_down_word(big);
	return(val);
}

/**************************************************/
DWORD ram_read_dword(void *ram);
DWORD ram_read_dword(void *ram)
{
	DWORD big,val;
	big=*(DWORD *)ram;
	val=up_down_dword(big);
	return(val);
}
/**************************************************/
QWORD ram_read_qword(void *ram);
QWORD ram_read_qword(void *ram)
{
	QWORD big,val;
	big=*(QWORD *)ram;
	val=up_down_qword(big);
	return(val);
}
/**************************************************/
void  ram_write_word(void *ram, WORD val);
void  ram_write_word(void *ram, WORD val)
{
	WORD big;
	big=up_down_word(val);
	*(WORD *)ram=big;
}
/**************************************************/
void  ram_write_dword(void *ram, DWORD val);
void  ram_write_dword(void *ram, DWORD val)
{
	DWORD big;
	big=up_down_dword(val);
	*(DWORD *)ram=big;
}
/**************************************************/
void  ram_write_qword(void *ram, QWORD val);
void  ram_write_qword(void *ram, QWORD val)
{
	QWORD big;
	big=up_down_qword(val);
	*(QWORD *)ram=big;
}
#endif
#endif



/* end of ram_rw_lit.c */
