
/*------------------------------------
 * status.c
 * Create:  2021-10-26
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
/** Device Status Register */
#define DSTS                DEV_REG(0x08)
#define DSTS_suspsts        (1 << 0) /** Suspend status */
#define DSTS_enumspd_bitp   1 /** Enumerated speed */
#define DSTS_enumspd_bits   0x3
#define DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ 0
#define DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ 1
#define DSTS_ENUMSPD_LS_PHY_6MHZ           2
#define DSTS_ENUMSPD_FS_PHY_48MHZ          3
#define DSTS_errticerr      (1 << 3) /** Erratic errors ? */
#define DSTS_soffn_bitp     8 /** Frame or Microframe Number of the received SOF */
#define DSTS_soffn_bits     0x3fff/

/*================================================================*/
static const u8_t speed[4] =
{
		[DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ] = 1,
		[DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ] = 0,
		[DSTS_ENUMSPD_LS_PHY_6MHZ] = 0,
        [DSTS_ENUMSPD_FS_PHY_48MHZ] = 0,
};

int d_sts_get_port_speed_type(void);
int d_sts_get_port_speed_type(void)
{
    unsigned int enumspd;

    enumspd = extract(DSTS, enumspd);
    if (enumspd == DSTS_ENUMSPD_LS_PHY_6MHZ)
        panicf("usb-drv: LS is not supported");

    enumspd &= 3;
    return speed[enumspd];
}

/*================================================================*/
int d_sts_get_mps_by_type(int type);
int d_sts_get_mps_by_type(int type)
{
	int fs_hs,mps;
	fs_hs = d_sts_get_port_speed_type();

	fs_hs &= 1;
	type &= 3;
	mps = usb_get_ep_mps(type,fs_hs);
	return mps;
}
/*================================================================*/

/* end of status.c */
