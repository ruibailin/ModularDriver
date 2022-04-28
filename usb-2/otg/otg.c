
/*------------------------------------
 * otg.c
 * Create:  2021-10-29
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

#include "./driver/2exp.h"
#include "./register/2exp.h"
/*================================================================*/
//Old name usb_drv should be called usb_otg
//usb_otg_enable()
//#define usb_otg_enable usb_enable

static void as3525v2_connect(void);
static void as3525v2_connect()
{
    panicf("usb-drv: DWC OTG");
    /* 1) enable usb core clock */

    // bitset32(&CGU_PERI, CGU_USB_CLOCK_ENABLE);
    //btr_nsecs_delay(BTR_USB_DELAY_NSECS);
    btr_nsecs_delay(BTR_USB_DELAY_NSECS);
    /* 2) enable usb phy clock */
    // CCU_USB = (CCU_USB & ~(3<<24)) | (1 << 24); /* ?? */
    /* PHY clock */
    // CGU_USB = 1<<5  /* enable */
    //    | 0 << 2
    //     | 0; /* source = ? (24MHz crystal?) */
    // btr_nsecs_delay(BTR_USB_DELAY_NSECS);
    /* 3) clear "stop pclk" */
    g_cg_clear_stop_pclk();
    btr_nsecs_delay(BTR_USB_DELAY_NSECS);
    /* 4) clear "power clamp" */
    g_p_clear_clamp();
    btr_nsecs_delay(BTR_USB_DELAY_NSECS);
    /* 5) clear "reset power down module" */
    g_p_clear_reset();
    btr_nsecs_delay(BTR_USB_DELAY_NSECS);
    /* 6) set "power on program done" */
    d_ctl_set_power_on();
    btr_nsecs_delay(BTR_USB_DELAY_NSECS);
    /* 7) core soft reset */
    g_rst_soft_reset_core();
    btr_nsecs_delay(BTR_USB_DELAY_NSECS);
    /* 8) hclk soft reset */
    g_rst_soft_reset_hclk();
    btr_nsecs_delay(BTR_USB_DELAY_NSECS);
    /* 9) flush and reset everything */
    g_rst_flush_and_reset();
    btr_nsecs_delay(BTR_USB_DELAY_NSECS);
    /* 10) force device mode*/
    g_usb_force_into_device_mode();
    btr_nsecs_delay(BTR_USB_DELAY_NSECS);
    /* 11) Do something that is probably CCU related but undocumented*/
    // CCU_USB |= 0x1000;
    // CCU_USB &= ~0x300000;
    //btr_nsecs_delay(BTR_USB_DELAY_NSECS);
    /* 12) reset usb core parameters (dev addr, speed, ...) */
    d_cfg_reset_device();
    btr_nsecs_delay(BTR_USB_DELAY_NSECS);
}

static void as3525v2_disconnect(void);
static void as3525v2_disconnect()
{
    /* Disable clock */
    //  CGU_USB = 0;
    // btr_nsecs_delay(BTR_USB_DELAY_NSECS);
    // bitclr32(&CGU_PERI, CGU_USB_CLOCK_ENABLE);
}

static void config_device_interrupts(void) {
	g_int_clear_all();
    g_otg_int_clear();
    g_int_enable_all();
}

static void flush_tx_fifos(int nums) {
	g_rst_flush_tx_fifos(nums);
    /* wait 3 phy clocks */
    //udelay(1);
    btr_nsecs_delay(1000);
}

static void prepare_setup_ep0(void) {
    panicf("usb-drv: prepare EP0\n\r");
    /* setup DMA */
    otg_drv_ep0_prepare_setup_ep0();
}

static void handle_ep0_complete(bool is_ack)
{
	otg_drv_ep0_handle_ep0_complete(is_ack);
}

static void handle_ep0_setup(void) {
	otg_drv_ep0_handle_ep0_setup();
}


void otg_reconnection(void);
void otg_reconnection()
{
	d_ctl_reconnect();
}

void otg_disconnection(void);
void otg_disconnection()
{
	d_ctl_disconnect();
}

void otg_reset_endpoints(void);
void otg_reset_endpoints()
{
	otg_drv_epn_reset();
}

static void cancel_all_transfers(bool cancel_ep0){
    panicf("usb-drv: cancel all transfers\n\r");
    //  int flags = disable_irq_save();
    otg_drv_epn_cancel_transfer(false);
}

static void core_dev_init(void)
{
	otg_drv_dev_init();
}
static void core_init(void)
{
	otg_drv_core_init();
}

static void enable_global_interrupts(void) {
    //   VIC_INT_ENABLE = INTERRUPT_USB;
	otg_drv_core_enable_global_interrupts();

}

static void disable_global_interrupts(void) {
	otg_drv_core_disable_global_interrupts();
    // VIC_INT_EN_CLEAR = INTERRUPT_USB;
}

static int usb_probe(void) {
#if defined(__BTR_FPGA__)
    if(btr_read32(fpga_test__base + fpga_test__j23_card_sel_reg__offset) != 1)
    {
        return ERR_DEV_NO_FOUND;
    }
#endif //__BTR_FPGA__
    return ERR_OK;
}
/*================================================================*/
int otg_init(void);
int otg_init() {
    unsigned i, ep;
    int ret;
    panicf("otg_init");

    if ((ret = usb_probe()) != ERR_OK) {
        panicf("No device found");
        return ret;
    }

    /* Boost cpu */
    // cpu_boost(1);
    /* Enable PHY and clocks (but leave pullups disabled) */
    as3525v2_connect();
    panicf("usb-drv: synopsis id: %lx", g_id_get_vendor());
    /* Core init */
    otg_drv_core_init();

    otg_drv_epn_wakeup_init();

    otg_drv_core_enable_global_interrupts();

    return 0;
}

void otg_exit(void);
void otg_exit(void) {
    panicf("otg_exit");

    otg_drv_core_disable_global_interrupts();
    as3525v2_disconnect();
    //   cpu_boost(0);
}

void otg_enable(bool on);
void otg_enable(bool on)
{
    if (on)
        otg_init();
    else
        otg_exit();
}

static void handle_ep_in_int(int ep){
	panicf("ep_in_int[%d]\n\r", ep);
	otg_drv_epn_handle_in_int(ep);
}

static void handle_ep_out_int(int ep) {
	   panicf("epn_out_int[%d]\n\r", ep);
	   otg_drv_epn_handle_out_int(ep);
}

static void handle_ep_ints(void){
	 otg_drv_epn_handle_ints();
}

/* interrupt service routine */
int otg_interrupt(void);
int otg_interrupt(void) {
	int ret;
	ret = g_int_get_type();
    return ret;
}

int otg_port_speed(void);
int otg_port_speed()
{

	int speed;
	speed = d_sts_get_port_speed_type();
    return speed;
}

/*
static unsigned long otg_mps_by_type(int type) {

}*/

/*================================================================*/
int otg_request_endpoint(int type, int dir);
int otg_request_endpoint(int type, int dir)
{

	int ret;

    ret = otg_drv_epn_request(type,dir);

    return ret;
}


void otg_release_endpoint(int ep);
void otg_release_endpoint(int ep)
{
    //panicf("usb-drv: release EP%d %s\n\r", EP_NUM(ep), EP_DIR(ep) == DIR_IN ? "IN" : "OUT");
	otg_drv_epn_release(ep);
}


/*================================================================*/

void otg_cancel_all_transfers(void);
void otg_cancel_all_transfers()
{
    panicf("usb-drv: cancel all transfers\n\r");
    //  int flags = disable_irq_save();
	otg_drv_epn_cancel_transfer(false);
}

static int otg_transfer(int ep, void *ptr, int len, bool dir_in, bool blocking)
{
	return otg_drv_epn_begin_transfer(ep, ptr, len, dir_in, blocking);
}

int otg_recv(int ep, void *ptr, int len);
int otg_recv(int ep, void *ptr, int len)
{
    return otg_drv_epn_begin_transfer(ep, ptr, len, false, false);
}

int otg_send(int ep, void *ptr, int len);
int otg_send(int ep, void *ptr, int len)
{
    BTR_USB_CACHE_WRITE();
    return otg_drv_epn_begin_transfer(ep, ptr, len, true, true);
}

int otg_send_nonblocking(int ep, void *ptr, int len);
int otg_send_nonblocking(int ep, void *ptr, int len)
{
    BTR_USB_CACHE_WRITE();
    return otg_drv_epn_begin_transfer(ep, ptr, len, true, false);
}

/*================================================================*/
void otg_set_test_mode(int mode);
void otg_set_test_mode(int mode)
{
	d_ctl_set_test_mode(mode);
}

void otg_set_address(int address);
void otg_set_address(int address)
{
	d_cfg_set_device_addr( address);
}

void otg_stall(int ep, bool stall, bool in);
void otg_stall(int ep, bool stall, bool in)
{
    panicf("usb-drv: %sstall EP%d %s", stall ? "" : "un", ep, in ? "IN" : "OUT");

    d_ep_ctl_stall(ep, stall, in);
}

bool otg_is_stalled(int ep, bool in);
bool otg_is_stalled(int ep, bool in)
{
    return  d_ep_ctl_is_stalled(ep, in);
}


/*================================================================*/

/* end of otg.c */
