
/*------------------------------------
 * interrupt.c
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

/** Core Interrupt Register */
#define GINTSTS             GLOBAL_REG(0x014)
/* NOTE: GINTSTS bits are the same as in GINTMSK plus this one */
#define GINTSTS_curmode     (1 << 0) /** Current mode, 0 for device */

/** Core Interrupt Mask Register */
#define GINTMSK                 GLOBAL_REG(0x018)
#define GINTMSK_modemismatch    (1 << 1) /** mode mismatch ? */
#define GINTMSK_otgintr         (1 << 2)
#define GINTMSK_sofintr         (1 << 3)
#define GINTMSK_rxstsqlvl       (1 << 4)
#define GINTMSK_nptxfempty      (1 << 5) /** Non-periodic TX fifo empty ? */
#define GINTMSK_ginnakeff       (1 << 6)
#define GINTMSK_goutnakeff      (1 << 7)
#define GINTMSK_i2cintr         (1 << 9)
#define GINTMSK_erlysuspend     (1 << 10)
#define GINTMSK_usbsuspend      (1 << 11) /** USB suspend */
#define GINTMSK_usbreset        (1 << 12) /** USB reset */
#define GINTMSK_enumdone        (1 << 13) /** Enumeration done */
#define GINTMSK_isooutdrop      (1 << 14)
#define GINTMSK_eopframe        (1 << 15)
#define GINTMSK_epmismatch      (1 << 17) /** endpoint mismatch ? */
#define GINTMSK_inepintr        (1 << 18) /** in pending ? */
#define GINTMSK_outepintr       (1 << 19) /** out pending ? */
#define GINTMSK_incomplisoin    (1 << 20) /** ISP in complete ? */
#define GINTMSK_incomplisoout   (1 << 21) /** ISO out complete ? */
#define GINTMSK_portintr        (1 << 24) /** Port status change ? */
#define GINTMSK_hcintr          (1 << 25)
#define GINTMSK_ptxfempty       (1 << 26) /** Periodic TX fifof empty ? */
#define GINTMSK_conidstschng    (1 << 28)
#define GINTMSK_disconnect      (1 << 29) /** Disconnect */
#define GINTMSK_sessreqintr     (1 << 30) /** Session request */
#define GINTMSK_wkupintr        (0x80000000) //(1 << 31) /** Wake up */

/*================================================================*/
#include "../../driver/endpoint/endpoint.h"
extern void core_data_reset(void);
static void int_from_usb_reset(void);
static void int_from_usb_reset()
{
    panicf("usb-drv: bus reset\n\r");

    d_ctl_clear_remote_wakeup();

    /* Flush FIFOs */
    g_rst_flush_tx_fifos(0x10);

    g_rst_flush_learning_queue();

    d_cfg_reset_device_addr();

    otg_drv_epn_reset();

    otg_drv_ep0_prepare_setup_ep0();

    core_data_reset();
    // flg = 1;
}

static void int_from_usb_enum_done(void);
static void int_from_usb_enum_done()
{
	int stype;
    /* read speed */

    panicf("usb-drv: enum done\n\r");
	stype = d_sts_get_port_speed_type();
    if(stype)
        panicf("usb-drv: HS\n\r");
    else
        panicf("usb-drv: FS\n\r");
    //  flg = 1;
}

static void int_from_otg_int(void);
static void int_from_otg_int()
{
    panicf("usb-drv: otg int\n\r");
	g_otg_int_clear();
    //  flg = 1;
}

static void int_from_usb_endpoint(void);
static void int_from_usb_endpoint()
{
    panicf("usb-drv: endpoint int\n\r");
    otg_drv_epn_handle_ints();
    //  flg = 1;
}

extern void otg_enable(bool on);
static void int_from_disconnect(void);
static void int_from_disconnect()
{
    panicf("usb-drv: disconnect\n\r");
	otg_drv_epn_cancel_transfer(true);
	otg_enable(false);
    //  flg = 1;
}

int g_int_get_type(void);
int g_int_get_type()
{
    /* some bits in GINTSTS can be set even though we didn't enable the interrupt source
     * so AND it with the actual mask */
	int ret;
    unsigned long sts;
    sts = GINTSTS & GINTMSK;

    if (sts & GINTMSK_usbreset) {
        int_from_usb_reset();
        ret = 1;
    }

    if (sts & GINTMSK_enumdone) {
        int_from_usb_enum_done();
        ret = 2;
    }

    if (sts & GINTMSK_otgintr) {
        int_from_otg_int();
        ret = 3;
    }

    if (sts & (GINTMSK_outepintr | GINTMSK_inepintr)) {
        int_from_usb_endpoint();
        ret = 4;
    }

    if (sts & GINTMSK_disconnect) {
        int_from_disconnect();
        ret = 5;
    }

    //if(flg)
    GINTSTS = sts;
    return ret;
}
/*================================================================*/
void g_int_enable_all(void);
void g_int_enable_all()
{
    /* Enable interrupts */
    GINTMSK = (u32_t) ((GINTMSK_usbreset) | (GINTMSK_enumdone) | (GINTMSK_inepintr) | (GINTMSK_outepintr) | (GINTMSK_disconnect)
            | (GINTMSK_usbsuspend) | (GINTMSK_wkupintr) | (GINTMSK_portintr) | (GINTMSK_otgintr));
}

void g_int_clear_all(void);
void g_int_clear_all()
{
    /* Clear any pending interrupt */
    GINTSTS = 0xffffffff;
}
/*================================================================*/
/* end of interrupt.c */
