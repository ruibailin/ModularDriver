
/*------------------------------------
 * desc.h
 * Create:  2021-11-13
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


#ifndef USB_STO_DESC_DESC_H_
#define USB_STO_DESC_DESC_H_
/*================================================================*/
extern u8_t *sto_desc_if_get_config(u8_t *dest,int interface);

extern u8_t *sto_desc_ep_get_config(u8_t *dest,int mps, int ep_in,int ep_out);

/*================================================================*/
#endif
/* end of desc.h */
