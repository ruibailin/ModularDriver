/*---------------------------
 * t_svr.c
 *  Created on: Aug 13, 2017
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *Test svr.c
 *
 *
 *
 *---------------------------
 */


#include <stdio.h>
#include <stdlib.h>

#include "../../code/app/1skt/c_share.h"

static char *s_buf, *r_buf;
#define	FRM_W	720
#define FRM_H	576
#define INPUTFILE1  "./720x576_FourPeople_3_refm.yuv"
/**************************************************/
#include <assert.h>
#include <errno.h>
#include <string.h>
static void	yuv_get_nfrm(void *buf,int n);
static void	yuv_get_nfrm(void *buf,int n)
{
    FILE *fp;
    int size;
    long offset;

    size=FRM_W*FRM_H;
    offset=size*3;
    offset >>= 2;
    offset *= n;
    fp = fopen(INPUTFILE1, "rb");
    if (fp==NULL)
    {
    	printf("%s, open input file:%s ERR!\n",  __func__,INPUTFILE1);
        printf("ERROR is %s\n", strerror(errno));
    	return;
    }
    if(fseek(fp, offset, SEEK_SET))
    {
    	printf("No %d frame found!\n", n);
        fclose(fp);
    	return;
    }
    if (fread(buf, sizeof(unsigned char),  size, fp)!= size)
    {
       printf("Read n frame error, fp(%p),addr(%p), size(%d)\n", fp, buf,size);
       fclose(fp);
       return;
    }
    fclose(fp);
}

/**************************************************/
static int compare_char_buf(void)
{
	int i,j,k;
	k=0;
	for(i=0;i++;i<FRM_H)
		for(j=0;j++;j<FRM_W)
		{
			if(s_buf[k] != r_buf[k])
				return(0);
			k++;
		}
	return(1);
}

/**************************************************/
#include "../../code/app/1skt/svr.h"
void app_svr(void);
void app_svr(void)
{
	s_buf=malloc(FRM_W*FRM_H);
	if(s_buf == NULL)
		return;

	r_buf=malloc(FRM_W*FRM_H);
	if(r_buf == NULL)
		return;

	yuv_get_nfrm(s_buf,0);
	app_svr_init_skt();

	app_svr_recv_frm(r_buf,FRM_W,FRM_H);
	int ret;
	ret=compare_char_buf();
	if(ret)
		printf("Server socket is OK\n");
	else
		printf("Server socket is wrong\n");

	app_svr_send_frm(s_buf,FRM_W,FRM_H);

	app_svr_recv_frm(r_buf,FRM_W,FRM_H);
	app_svr_send_frm(s_buf,FRM_W,FRM_H);
	app_svr_recv_frm(r_buf,FRM_W,FRM_H);
	app_svr_send_frm(s_buf,FRM_W,FRM_H);


	app_svr_free_skt();
}

/**************************************************/

#include <stdio.h>
#include <stdlib.h>
int svr_main(int argc, char** argv);
int svr_main(int argc, char** argv)
{
	puts("Run as server\n");
	app_svr();
	return EXIT_SUCCESS;
}

/* end of t_svr.c */
