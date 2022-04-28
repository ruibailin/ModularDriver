/*---------------------------
 * hw_cve_irq.c
 *  Created on: Jul 3, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *����Ӳ��CVE�ж�
 *
 *
 *
 *---------------------------
 */


#include "c_share.h"

#if	!IVE_UNIT_TEST
#include "../0ioctl/ioctl_cmd.h"
/**************************************************/
int hw_wait_cve_done(int sleep,int max);
int hw_wait_cve_done(int sleep,int max)
{
	cmd_wait_done();
}
/**************************************************/
int top_wait_cve_done(int sleep,int max);
int top_wait_cve_done(int sleep,int max)
{
	cmd_wait_done();
}
#endif

/* end of hw_cve_irq.c */
