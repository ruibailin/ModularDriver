/*---------------------------
 * hw_cve.c
 *  Created on: Jun 22, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *�������Ӳ��CVE�����������й���
 *
 *
 *
 *---------------------------
 */


#include <semaphore.h>
#include <sys/types.h>
#include "c_share.h"
static sem_t sem_id;
static int req_num;
static void cve_ini_sem(void);
static void cve_ini_sem(void)
{
	req_num=0;
	sem_init(&sem_id, 0, 1);
}

/**************************************************/
static void cve_get_sem(void);
static void cve_get_sem(void)
{
	req_num++;
	sem_wait(&sem_id);
}
/**************************************************/
static void cve_ret_sem(void);
static void cve_ret_sem(void)
{
	if(req_num==0)
		return;
	req_num--;
	sem_post(&sem_id);
}
/**************************************************/
void ini_hw_cve();
void ini_hw_cve()
{
	void *base_ptr;
	io_open_file();

	base_ptr=0x0000;

	base_ptr += 0x0000;
	top_ini_base_addr(base_ptr);

	base_ptr += 0x0400;
	knl0_ini_base_addr(base_ptr);	

	base_ptr += 0x0400;
	knl1_ini_base_addr(base_ptr);

	base_ptr += 0x0400;
	knl2_ini_base_addr(base_ptr);

	knl0_clr_opr_enabler(0xFFFFFFFF);
	knl1_clr_opr_enabler(0xFFFFFFFF);
	knl2_clr_opr_enabler(0xFFFFFFFF);
	top_set_clr_irq_state(0x00);
	top_set_start_reg(0x00);

	top_ini_sw_reg();
	knl0_ini_sw_reg();
	knl0_ini_sw_reg();
	knl0_ini_sw_reg();

	cve_ini_sem();
}
/**************************************************/
void reset_hw_cve()
{
	cmd_reset_asic();
	knl0_clr_opr_enabler(0xFFFFFFFF);
	knl1_clr_opr_enabler(0xFFFFFFFF);
	knl2_clr_opr_enabler(0xFFFFFFFF);
	top_set_clr_irq_state(0x00);
	top_set_start_reg(0x00);

	top_ini_sw_reg();
	knl0_ini_sw_reg();
	knl0_ini_sw_reg();
	knl0_ini_sw_reg();

	while(1)
	{
		if(req_num == 0) break;
		cve_ret_sem();
	}
}

/**************************************************/
void get_hw_cve();
void get_hw_cve()
{
	cve_get_sem();
}
/**************************************************/
/*return CVE after use*/
void ret_hw_cve();
void ret_hw_cve()
{
	cve_ret_sem();
}

/* end of hw_cve.c */
