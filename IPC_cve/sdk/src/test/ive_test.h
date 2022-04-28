
/*---------------------------
 * ive_test.h
 *  Created on: 2017年8月14日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *Define test method and thoughts
 *
 *
 *
 *
 *---------------------------
 */

#ifndef SRC_TEST_IVE_TEST_H_
#define SRC_TEST_IVE_TEST_H_
/**************************************************/
#define IVE_UNIT_TEST	1
#define IVE_NORMAL_VER	!IVE_UNIT_TEST

/**************************************************/
#if	IVE_UNIT_TEST									//Control test platform
#define TEST_IN_ARM		0
#define	TEST_IN_X86		!TEST_IN_ARM
#endif
/**************************************************/
#if	IVE_UNIT_TEST									//Control test platform
#define TEST_WITH_INTERUPT		1
#define	TEST_WITH_POLLING		!TEST_WITH_INTERUPT
#endif
#if TEST_IN_ARM
#define TEST_IN_6805	1
#define TEST_IN_67xx	!TEST_IN_6805
#endif
#if	TEST_IN_X86
#define TEST_IN_UBUNTU	1
#define TEST_IN_CYGWIN	!TEST_IN_UBUNTU
#endif
#if TEST_IN_UBUNTU
#define	TEST_IN_UBUNTU_64	1
#define TEST_IN_UBUNTU_32	!TEST_IN_UBUNTU_64
#endif
#if TEST_IN_CYGWIN
#deinfe TEST_IN_CYGWIN_64	1
#define	TEST_IN_CYGWIN_32	!TEST_IN_CYGWIN_64
#endif
/**************************************************/
#if	IVE_UNIT_TEST								//Control how to mimic hardware
#define	SOFTWARE_VPE	1						//use ffmpeg
#define	HARDWARE_VPE	!SOFTWARE_VPE
#define	SOFTWARE_VCE	1
#define	HARDWARE_VCE	!SOFTWARE_VCE
#define	SOFTWARE_VOE	1						//TCP/IP to remote PC
#define	HARDWARE_VOE	!SOFTWARE_VOE
#endif
#if	SOFTWARE_VCE
#define	USR_MODE_VCE		1					//Software VCE in user space
#define DRV_MODE_VCE		!USR_MODE_VCE		//Software VCE in driver space
#endif
/**************************************************/
#if	IVE_UNIT_TEST								//Control to test submodule
#define	TEST_APP_ICP		0
#define	TEST_APP_SKT		0
#define TEST_APP_OPR		0
#define TEST_APP_SDL		0
#define TEST_HW_FILE		0
#define TEST_HW_IOCTL		0
#define TEST_HW_RAM			0
#define TEST_HW_REG			0
#define TEST_HW_OPR			0
#define TEST_HW_CVE			0
#define TEST_SW_BLK			0
#define TEST_SW_OPR			0
#define TEST_SW_REG			0
#define TEST_SW_CVE			0
#endif

#endif 
/* end of ive_test.h */
