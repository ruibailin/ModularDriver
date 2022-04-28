
/*------------------------------------
 * desc.h
 * Create:  2021-11-11
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


#ifndef USB_CORE_DESC_DESC_H_
#define USB_CORE_DESC_DESC_H_
/*================================================================*/
extern int core_desc_cfg_set_type(char type);
extern int core_desc_cfg_get_len(void);
extern void *core_desc_cfg_get_add(void);
extern void core_desc_cfg_set_dt_config(int intf,int size);

extern void core_desc_dev_clr_serial(void);
extern void *core_desc_dev_get_add(void);
extern int core_desc_dev_get_len(void);

extern void *core_desc_qual_get_add(void);
extern int core_desc_qual_get_len(void);

extern void core_desc_usb_str_set_str0(int id);
extern void *core_desc_usb_str_get_add(int index);
extern int core_desc_usb_str_get_len(int index);
/*================================================================*/
#endif
/* end of desc.h */
