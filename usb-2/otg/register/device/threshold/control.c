
/*------------------------------------
 * control.c
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

#include "../0ctr.h"
#include "../1imp.h"
/*================================================================*/
/** Device Thresholding control register */
#define DTHRCTL                     DEVICE_REG(0x30)
#define DTHRCTL_non_iso_thr_en      (1 << 0)
#define DTHRCTL_iso_thr_en          (1 << 1)
#define DTHRCTL_tx_thr_len_bitp     2
#define DTHRCTL_tx_thr_len_bits     0x1FF
#define DTHRCTL_rx_thr_en           (1 << 16)
#define DTHRCTL_rx_thr_len_bitp     17
#define DTHRCTL_rx_thr_len_bits     0x1FF

/*================================================================*/

/* end of control.c */
