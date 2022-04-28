/*---------------------------
 * os_clock.c
 *  Created on: Jul 5, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#include "c_share.h"

#include <linux/device.h>
#include <linux/clk.h>
/**************************************************/
void *os_get_clk_from_dev(void *dev,const char *name);
void *os_get_clk_from_dev(void *dev,const char *name)
{
	struct clk *clock;
	clock=clk_get((struct device *)dev,name);
	return((void *)clock);
}
/**************************************************/
void os_get_clock_rate(void *clock);
void os_get_clock_rate(void *clock)
{
	clk_get_rate((struct clk *)clock);
}
/**************************************************/
void os_set_clock_rate(void *clock,int rate);
void os_set_clock_rate(void *clock,int rate)
{
	clk_set_rate((struct clk *)clock,rate);
}
/**************************************************/
void os_prepare_clock(void *clk);
void os_prepare_clock(void *clk)
{
	clk_prepare_enable((struct clk *)clk);
}
/**************************************************/
void os_unprepare_clock(void *clk);
void os_unprepare_clock(void *clk)
{
	clk_disable_unprepare((struct clk *)clk);
}
/* end of os_clock.c */
