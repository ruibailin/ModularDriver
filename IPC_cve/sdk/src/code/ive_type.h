/*
 * ive_type.h
 *
 *  Created on: 2017Äê6ÔÂ8ÈÕ
 *      Author: LOOK
 */

#ifndef IVE_TYPE_H_
#define IVE_TYPE_H_

/*used for ARM 32*/
#define SIZEOFINT	4
#if SIZEOFINT != 4
#error "Please redefine int32"
#endif

/*My Style*/
#ifndef	WORD
typedef unsigned char  	BYTE;
typedef unsigned short  WORD;
typedef signed short  	SWORD;
typedef unsigned int  	DWORD;
typedef unsigned long   QWORD;
#endif

/*ZTE Style*/
#ifndef	INT16
typedef          char  	INT8;
typedef 		 short  INT16;
typedef 		 int  	INT32;
typedef 		 long   INT64;
typedef unsigned char  	UINT8;
typedef unsigned short  UINT16;
typedef unsigned int  	UINT32;
typedef unsigned long   UINT64;
#endif

/*FFMPEG Style*/
#ifndef	Bit16u
typedef unsigned char  	Bit8u;
typedef unsigned short  Bit16u;
typedef unsigned int  	Bit32u;
typedef unsigned long   Bit64u;
typedef 		 char   Bit8s;
typedef 		 short  Bit16s;
typedef 		 int  	Bit32s;
typedef 		 long   Bit64s;
#endif

/*Boshs Style*/
#ifndef	u16
typedef unsigned char  	u8;
typedef unsigned short  u16;
typedef unsigned int  	u32;
typedef unsigned long   u64;
typedef 		 char   s8;
typedef 		 short  s16;
typedef 		 int  	s32;
typedef 		 long   s64;
#endif

/*Qemu Style*/
#ifndef	uint16_t
typedef unsigned char  	uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int  	uint32_t;
typedef unsigned long   uint64_t;
typedef          char  	sint8_t;
typedef 		 short  sint16_t;
typedef 		 int  	sint32_t;
typedef 		 long   sint64_t;
#endif

#ifndef boolean
typedef unsigned short  boolean;
#endif

#ifndef BOOL
typedef unsigned short  BOOL;
#endif

#ifndef TRUE
#define	TRUE	1
#define FAULSE  0
#endif

#ifndef NULL
#define NULL    (void *)0
#endif

#endif /* IVE_TYPE_H_ */
