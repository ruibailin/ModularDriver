
/*------------------------------------
 * storage.c
 * Create:  2021-11-14
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


#include "../1imp.h"
/*================================================================*/
bool usb_storage_removable(int lun);
bool usb_storage_removable(int lun)
{
	return true;
}

bool usb_storage_present(int lun);
bool usb_storage_present(int lun)
{
	return true;
}
/*================================================================*/

/* end of storage.c */
