/*---------------------------
 * ive_test.c
 *  Created on: Jun 25, 2017
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

#include <stdio.h>
#include <stdlib.h>
extern void test_hw_opr(void);
extern void test_hw_ram(void);
extern void test_hw_reg(void);
extern void test_sw_blk(void);
extern void test_sw_opr(void);
extern void test_sw_reg(void);
extern void test_sw_cve(void);
extern void test_app_sdl(void);
extern void test_app_opr(void);
/**************************************************/
int main(int argc,char *argv[])
{
	test_app_opr();

	test_app_sdl();
	test_hw_ram();
	test_hw_reg();
	test_hw_opr();
	test_sw_blk();
	test_sw_opr();
	test_sw_reg();
	test_sw_cve();

	return EXIT_SUCCESS;
}

#endif
/* end of ive_test.c */
