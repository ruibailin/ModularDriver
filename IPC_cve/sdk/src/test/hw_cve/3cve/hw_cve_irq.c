
/*---------------------------
 * hw_cve_irq.c
 *  Created on: 2017年8月15日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *
 *
 *
 *
 *
 *---------------------------
 */

#include "../../ive_test.h"

#if	IVE_UNIT_TEST
/**************************************************/
/*The maximum waiting time is sleep*max u second*/
#include <unistd.h>
int hw_wait_cve_done(int sleep,int max);
int hw_wait_cve_done(int sleep,int max)
{
	DWORD	state;
	int ii;

	ii=0;
	for(;;)
	{
		if(sleep !=0 )
			usleep(sleep);
		top_get_irq_state(&state);
		state &= 0x80000000;
		if(state!=0)
			break;
		ii++;
		if(ii>=max)
			break;   /*wrong*/
	}
	return(ii);
}

/**************************************************/
/*The maximum waiting time is sleep*max u second*/
/*This is old format function*/
int top_wait_cve_done(int sleep,int max);
int top_wait_cve_done(int sleep,int max)
{
	DWORD	state;
	int ii;

	ii=0;
	for(;;)
	{
		if(sleep !=0 )
			usleep(sleep);
		top_get_irq_state(&state);
		state &= 0x80000000;
		if(state!=0)
			break;
		ii++;
		if(ii>=max)
			break;   /*wrong*/
	}
	return(ii);
}
#endif
/* end of hw_cve_irq.c */
