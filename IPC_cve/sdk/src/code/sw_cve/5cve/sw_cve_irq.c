/*---------------------------
 * sw_cve_irq.c
 *  Created on: Jul 3, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#include "../../code/sw_cve/5cve/c_share.h"

/**************************************************/
void hw_set_cve_done(void);
void hw_set_cve_done(void)
{

	top_set_irq_state(0x80000000);

}
/**************************************************/
void hw_set_cve_undone(void);
void hw_set_cve_undone(void)
{

	top_set_irq_state(0x00000000);

}

/**************************************************/
/*Must used when use software CVE to test*/
void hw_wait_cve_clr_irq_state(DWORD bit);
void hw_wait_cve_clr_irq_state(DWORD bit)
{
	DWORD	state;
	int ii;

	ii=0;
	for(;;)
	{
		top_get_clr_irq_state(&state);
		state &= bit;
		if(state==0) return;
		usleep(10000);
		ii++;
		if(ii>=100) return;   /*wrong*/
	}
}

/**************************************************/
void top_set_cve_done(void);
void top_set_cve_done(void)
{

	top_set_irq_state(0x80000000);

}
/**************************************************/
void top_set_cve_undone(void);
void top_set_cve_undone(void)
{

	top_set_irq_state(0x00000000);

}

/**************************************************/
/*Must used when use software CVE to test*/
void top_wait_cve_clr_irq_state(DWORD bit);
void top_wait_cve_clr_irq_state(DWORD bit)
{
	DWORD	state;
	int ii;

	ii=0;
	for(;;)
	{
		top_get_clr_irq_state(&state);
		state &= bit;
		if(state==0) return;
		usleep(10000);
		ii++;
		if(ii>=100) return;   /*wrong*/
	}
}

/* end of sw_cve_irq.c */
