
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

#include "0ctr.h"
#include "1imp.h"
/*================================================================*/
/** Device IN Endpoint (ep) Control Register */
#define DIEPCTL(ep)     DEVICE_REG(0x100 + (ep) * 0x20)
/** Device OUT Endpoint (ep) Control Register */
#define DOEPCTL(ep)     DEVICE_REG(0x300 + (ep) * 0x20)

/** Maximum Packet Size
 * IN/OUT EPn
 * IN/OUT EP0 - 2 bits
 *  2'b00: 64 Bytes
 *  2'b01: 32
 *  2'b10: 16
 *  2'b11: 8 */
#define DEPCTL_mps_bitp         0
#define DEPCTL_mps_bits         0x7ff
#define DEPCTL_MPS_64           0
#define DEPCTL_MPS_32           1
#define DEPCTL_MPS_16           2
#define DEPCTL_MPS_8            3
/** Next Endpoint
 * IN EPn/IN EP0
 * OUT EPn/OUT EP0 - reserved */
#define DEPCTL_nextep_bitp      11
#define DEPCTL_nextep_bits      0xf
#define DEPCTL_usbactep         (1 << 15) /** USB Active Endpoint */
/** Endpoint DPID (INTR/Bulk IN and OUT endpoints)
 * This field contains the PID of the packet going to
 * be received or transmitted on this endpoint. The
 * application should program the PID of the first
 * packet going to be received or transmitted on this
 * endpoint , after the endpoint is
 * activated. Application use the SetD1PID and
 * SetD0PID fields of this register to program either
 * D0 or D1 PID.
 *
 * The encoding for this field is
 * - 0: D0
 * - 1: D1
 */
#define DEPCTL_dpid             (1 << 16)
#define DEPCTL_naksts           (1 << 17) /** NAK Status */
/** Endpoint Type
 *  2'b00: Control
 *  2'b01: Isochronous
 *  2'b10: Bulk
 *  2'b11: Interrupt */
#define DEPCTL_eptype_bitp      18
#define DEPCTL_eptype_bits      0x3
/** Snoop Mode
 * OUT EPn/OUT EP0
 * IN EPn/IN EP0 - reserved */
#define DEPCTL_snp              (1 << 20)
#define DEPCTL_stall            (1 << 21) /** Stall Handshake */
/** Tx Fifo Number
 * IN EPn/IN EP0
 * OUT EPn/OUT EP0 - reserved */
#define DEPCTL_txfnum_bitp      22
#define DEPCTL_txfnum_bits      0xf

#define DEPCTL_cnak             (1 << 26) /** Clear NAK */
#define DEPCTL_snak             (1 << 27) /** Set NAK */
/** Set DATA0 PID (INTR/Bulk IN and OUT endpoints)
 * Writing to this field sets the Endpoint DPID (DPID)
 * field in this register to DATA0. Set Even
 * (micro)frame (SetEvenFr) (ISO IN and OUT Endpoints)
 * Writing to this field sets the Even/Odd
 * (micro)frame (EO_FrNum) field to even (micro)
 * frame.
 */
#define DEPCTL_setd0pid         (1 << 28)
/** Set DATA1 PID (INTR/Bulk IN and OUT endpoints)
 * Writing to this field sets the Endpoint DPID (DPID)
 * field in this register to DATA1 Set Odd
 * (micro)frame (SetOddFr) (ISO IN and OUT Endpoints)
 * Writing to this field sets the Even/Odd
 * (micro)frame (EO_FrNum) field to odd (micro) frame.
 */
#define DEPCTL_setd1pid         (1 << 29)
#define DEPCTL_epdis            (1 << 30) /** Endpoint disable */
#define DEPCTL_epena            (0x80000000)  //(1 << 31) /** Endpoint enable */
/*================================================================*/
void d_ep_ctl_enable_ep0_out(void);
void d_ep_ctl_enable_ep0_out()
{
    DOEPCTL(0) |= DEPCTL_epena | DEPCTL_cnak;
}

void d_ep_ctl_active_ep0(void);
void d_ep_ctl_active_ep0()
{
    DOEPCTL(0) = (DEPCTL_MPS_64 << DEPCTL_mps_bitp) | DEPCTL_usbactep | DEPCTL_snak;
    DIEPCTL(0) = (DEPCTL_MPS_64 << DEPCTL_mps_bitp) | DEPCTL_usbactep | DEPCTL_snak;
}

void d_ep_ctl_enable_in(int ep);
void d_ep_ctl_enable_in(int ep)
{
        if (DIEPCTL(ep) & DEPCTL_epena)
            DIEPCTL(ep) = DEPCTL_snak;
        else
            DIEPCTL(ep) = 0;
}

void d_ep_ctl_enable_out(int ep);
void d_ep_ctl_enable_out(int ep)
{
        if (DOEPCTL(ep) & DEPCTL_epena)
            DOEPCTL(ep) = DEPCTL_snak;
        else
            DIEPCTL(ep) = 0;
}

/*================================================================*/
void d_ep_ctl_setup_nextep(int ep,int next_ep);
void d_ep_ctl_setup_nextep(int ep,int next_ep)
{
    DIEPCTL(ep) = (DIEPCTL(ep) & ~bitm(DEPCTL, nextep)) | (next_ep << DEPCTL_nextep_bitp);
}

void d_ep_ctl_set_idle(int ep,bool dir_in);
void d_ep_ctl_set_idle(int ep,bool dir_in)
{
	if(dir_in == DIR_OUT)
	    DOEPCTL(ep) |= DEPCTL_epena | DEPCTL_cnak;
	else
	    DIEPCTL(ep) |= DEPCTL_epena | DEPCTL_cnak;
}

void d_ep_ctl_set_busy(int ep,bool dir_in);
void d_ep_ctl_set_busy(int ep,bool dir_in)
{
	if(dir_in == DIR_OUT)
	{
		DOEPCTL(ep) &= ~DEPCTL_stall;
		DOEPCTL(ep) |= DEPCTL_usbactep;
	}
	else
	{
		DIEPCTL(ep) &= ~DEPCTL_stall;
		DIEPCTL(ep) |= DEPCTL_usbactep;
	}
}

void d_ep_ctl_deactive(int ep,bool dir_in);
void d_ep_ctl_deactive(int ep,bool dir_in)
{
	if(dir_in == DIR_OUT)
	    DOEPCTL(ep) = (DOEPCTL(ep) & ~DEPCTL_usbactep) | DEPCTL_snak;
	else
	    DIEPCTL(ep) = (DIEPCTL(ep) & ~DEPCTL_usbactep) | DEPCTL_snak;
}

int d_ep_ctl_get_type(int ep,bool dir_in);
int d_ep_ctl_get_type(int ep,bool dir_in)
{
    volatile unsigned long *epctl = dir_in ? &DIEPCTL(ep) : &DOEPCTL(ep);
#define DEPCTL  *epctl
	int type;
	type= extract(DEPCTL, eptype);
	return type;
#undef DEPCTL
}

void d_ep_ctl_stall(int ep, int stall, bool dir_in);
void d_ep_ctl_stall(int ep, int stall, bool dir_in)
{
    if (dir_in == DIR_IN) {
        if (stall)
            DIEPCTL(ep) |= DEPCTL_stall;
        else
            DIEPCTL(ep) &= ~DEPCTL_stall;
    } else {
        if (stall)
            DOEPCTL(ep) |= DEPCTL_stall;
        else
            DOEPCTL(ep) &= ~DEPCTL_stall;
    }
}

bool  d_ep_ctl_is_stalled(int ep, bool dir_in);
bool  d_ep_ctl_is_stalled(int ep, bool dir_in)
{
	if(dir_in == DIR_IN)
		return (DIEPCTL(ep) & DEPCTL_stall);
	else
		return (DOEPCTL(ep) & DEPCTL_stall);
}

void d_ep_ctl_request(int ep,int type,int dir);
void d_ep_ctl_request(int ep,int type,int dir)
{
    unsigned long data;
    unsigned long mask;

    data = DEPCTL_setd0pid | (type << DEPCTL_eptype_bitp) | (d_sts_get_mps_by_type(type) << DEPCTL_mps_bitp)
                | DEPCTL_usbactep | DEPCTL_snak;
    mask = ~(bitm(DEPCTL, eptype) | bitm(DEPCTL, mps));

    if (dir == USB_DIR_IN)
        DIEPCTL(ep) = (DIEPCTL(ep) & mask) | data;
    else
        DOEPCTL(ep) = (DOEPCTL(ep) & mask) | data;
}
/*================================================================*/
/* end of control.c */
