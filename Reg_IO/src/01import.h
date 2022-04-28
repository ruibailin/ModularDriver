
/*---------------------------
 * 01import.h
 *  Created on: Apr 16, 2019
 *      Author: Steve Rui
 *---------------------------
 *
 *
 *
 *
 *
 *---------------------------
 */

#ifndef SCR_01IMPORT_H_
#define SRC_01IMPORT_H_


/**************************************************/
#define	PFMDRV_MODULE_NAME				"rbl_reg"			//platform driver

#define IOCTL_MAGIC_NUM					's'
#define IOCTL_CMD(x)					_IO(IOCTL_MAGIC_NUM,x)

#define FILE_CMD_READ32_REG				IOCTL_CMD(1)
#define FILE_CMD_WRITE32_REG			IOCTL_CMD(2)
#define FILE_CMD_READ16_REG				IOCTL_CMD(3)
#define FILE_CMD_WRITE16_REG			IOCTL_CMD(4)
#define FILE_CMD_READ8_REG				IOCTL_CMD(5)
#define FILE_CMD_WRITE8_REG				IOCTL_CMD(6)

typedef union{
		int  	reg32;
		short   reg16[2];
		char   	reg8[4];
	}IO_REG_VAL_U;

typedef struct{
		int	phy_add;
		IO_REG_VAL_U val;
	}IO_REG_CMD_T;

/**************************************************/
#endif 
/* end of 01import.h */
