/*---------------------------
 * sw_knl_base.h
 *  Created on: Jun 17, 2017
 *      Author: Bailin Rui
 *          ×÷Õß£ºÜÇ°ØÁÖ
 *---------------------------
 *
 *
 *
 *---------------------------
 */

#ifndef SW_CVE_2BLK_SW_KNL_BASE_H_
#define SW_CVE_2BLK_SW_KNL_BASE_H_

extern int  knl_get_blk5x5(char *in,char block[][5],int i,int j,int width,int height);
extern int 	knl_conv_blk5x5(char block[][5],char coeff[][5]);
extern int  knl_get_blk3x3(char *in,char block[][3],int i,int j,int width,int height);
extern int 	knl_conv_blk3x3(char block[][3],char coeff[][3]);

extern void	knl_copy_hori(char *out,char *in,int width,int i);
extern void	knl_copy_vert(char *out,char *in,int width,int j,int height);
extern void	knl_set_hori(char *out,char value,int width,int i);
extern void	knl_set_vert(char *out,char value,int width,int j,int height);
#endif

/* SW_CVE_2BLK_SW_KNL_BASE_H_ */
