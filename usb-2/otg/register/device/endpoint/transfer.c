
/*------------------------------------
 * transfer.c
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
/** Device IN Endpoint (ep) Transfer Size Register */
#define DIEPTSIZ(ep)    DEVICE_REG(0x100 + (ep) * 0x20 + 0x10)
/** Device OUT Endpoint (ep) Transfer Size Register */
#define DOEPTSIZ(ep)    DEVICE_REG(0x300 + (ep) * 0x20 + 0x10)

/** Device Endpoint (ep) DMA Address Register */
#define DOEPDMA(ep)     DEVICE_REG(0x300 + (ep) * 0x20 + 0x14)

/* valid for any D{I,O}EPTSIZi with 1<=i<=15, NOT for i=0 ! */
#define DEPTSIZ_xfersize_bitp   0 /** Transfer Size */
#define DEPTSIZ_xfersize_bits   0x7ffff
#define DEPTSIZ_pkcnt_bitp      19 /** Packet Count */
#define DEPTSIZ_pkcnt_bits      0x3ff
#define DEPTSIZ_mc_bitp         29 /** Multi Count - Periodic IN endpoints */
#define DEPTSIZ_mc_bits         0x3

/* idem but for i=0 */
#define DEPTSIZ0_xfersize_bitp  0 /** Transfer Size */
#define DEPTSIZ0_xfersize_bits  0x7f
#define DEPTSIZ0_pkcnt_bitp     19 /** Packet Count */
#define DEPTSIZ0_pkcnt_bits     0x3
#define DEPTSIZ0_supcnt_bitp    29 /** Setup Packet Count (DOEPTSIZ0 Only) */
#define DEPTSIZ0_supcnt_bits    0x3

/** Device IN Endpoint (ep) DMA Address Register */
#define DIEPDMA(ep)     DEVICE_REG(0x100 + (ep) * 0x20 + 0x14)
/** Device IN Endpoint (ep) Transmit FIFO Status Register */
#define DTXFSTS(ep)     DEVICE_REG(0x100 + (ep) * 0x20 + 0x18)
/*================================================================*/
void d_ep_set_dma_addr_out(int paddr);
void d_ep_set_dma_addr_out(int paddr)
{
	 DOEPDMA(0) = (unsigned long)BTR_PA((u32_t)paddr | BTR_MEM_OFFSET);
}

void d_ep_set_dma_ep0_out(void);
void d_ep_set_dma_ep0_out()
{
    /* Setup EP0 OUT with the following parameters:
     * packet count = 1
     * setup packet count = 1
     * transfer size = 8 (setup packet)
     */
    DOEPTSIZ(0) = (1 << DEPTSIZ0_supcnt_bitp) | (1 << DEPTSIZ0_pkcnt_bitp) | 8;

    d_ep_ctl_enable_ep0_out();
//    DOEPCTL(0) |= DEPCTL_epena | DEPCTL_cnak;
}

int d_ep_in_get_xfr_len(int ep);
int d_ep_in_get_xfr_len(int ep)
{
	int size;
	size = (DIEPTSIZ(ep) & DEPTSIZ_xfersize_bits);
	return size;
}

int d_ep_out_get_xfr_len(int ep);
int d_ep_out_get_xfr_len(int ep)
{
	int size;
	size=(DOEPTSIZ(ep) & DEPTSIZ_xfersize_bits);
	return size;
}

void d_ep_transfer_packet(int ep, void *ptr, int len, bool dir_in);
void d_ep_transfer_packet(int ep, void *ptr, int len, bool dir_in)
{
	int type, mps, nb_packets;

	volatile unsigned long *eptsiz = dir_in ? &DIEPTSIZ(ep) : &DOEPTSIZ(ep);
    volatile unsigned long *epdma = dir_in ? &DIEPDMA(ep) : &DOEPDMA(ep);
#define DEPTSIZ *eptsiz
#define DEPDMA  *epdma

    type = d_ep_ctl_get_type(ep,dir_in);
    mps = d_sts_get_mps_by_type(type);
    nb_packets = (len + mps - 1) / mps;

	epdma = dir_in ? &DIEPDMA(ep) : &DOEPDMA(ep);
	eptsiz = dir_in ? &DIEPTSIZ(ep) : &DOEPTSIZ(ep);
    if (len == 0) {
        DEPDMA = 0x10000000;
        DEPTSIZ = 1 << DEPTSIZ_pkcnt_bitp;
    } else {
        DEPDMA = (unsigned long) BTR_PA(((unsigned long)ptr | BTR_MEM_OFFSET));
        DEPTSIZ = (nb_packets << DEPTSIZ_pkcnt_bitp) | len;
        /*
         if(dir_in)
         clean_dcache_range(ptr, len);
         else
         dump_dcache_range(ptr, len);
         */
    }
#undef DEPTSIZ
#undef DEPDMA
}

/*================================================================*/
/* end of transfer.c */
