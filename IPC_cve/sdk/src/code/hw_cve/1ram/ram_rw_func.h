/*
 * ram_rw.h
 *
 *  Created on: 2017��6��8��
 *      Author: bailin rui
 */

#ifndef RAM_RW_FUNC_H_
#define RAM_RW_FUNC_H_


extern  WORD  ram_read_word(void *ram);
extern  DWORD ram_read_dword(void *ram);
extern  QWORD ram_read_qword(void *ram);
extern  void *ram_read_addr(void *ram);

extern  void  ram_write_word(void *ram, WORD w);
extern  void  ram_write_dword(void *ram,DWORD d);
extern  void  ram_write_qword(void *ram,QWORD d);
extern  void  ram_write_addr(void *ram,void *d);


#endif /* RAM_RW_FUNC_H_ */
