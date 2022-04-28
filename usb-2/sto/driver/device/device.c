
/*------------------------------------
 * hotswap.c
 * Create:  2021-11-05
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#include "0ctr.h"
#include "1imp.h"
/*================================================================*/
static bool ejected[NUM_DRIVES];
static bool locked[NUM_DRIVES];
static bool inserted;
/*================================================================*/
void sto_drv_dev_set_eject(int lun,bool eject);
void sto_drv_dev_set_eject(int lun,bool eject)
{
	ejected[lun]=eject;
}

bool sto_drv_dev_get_eject(int lun);
bool sto_drv_dev_get_eject(int lun)
{
	return ejected[lun];
}

bool sto_drv_dev_is_present(int lun);
bool sto_drv_dev_is_present(int lun)
{
	bool lun_present;
	lun_present = true;
#ifdef USB_HAVE_HOTSWAP
    if(usb_storage_removable(lun) && !usb_storage_present(lun)) {
        ejected[lun] = true;
    }
#endif
    if (ejected[lun])
        lun_present = false;

    return lun_present;
}


/*================================================================*/
static bool check_disk_present(IF_MD_NONVOID(int volume))
{
#ifdef USB_USE_RAMDISK
    return true;
#else
    unsigned char sector[SECTOR_SIZE];
    //return storage_read_sectors(IF_MD2(volume,)0,1,sector) == 0;
    return true;
#endif
}
void sto_drv_dev_notify_hotswap(int volume);
void sto_drv_dev_notify_hotswap(int volume)
{
    logf("notify %d",inserted);
    if(inserted && check_disk_present(IF_MD(volume))) {
        ejected[volume] = false;
    }
    else {
        ejected[volume] = true;
        /* If this happens while the device is locked, weird things may happen.
         At least try to keep our state consistent */
        locked[volume]=false;
    }
}
/*================================================================*/

/* end of hotswap.c */
