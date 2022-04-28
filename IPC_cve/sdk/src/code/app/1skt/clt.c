/*---------------------------
 * clt.c
 *  Created on: Aug 8, 2017
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include "c_share.h"

/**************************************************/
static int app_skt_fd;
static void clt_create_skt(void);
static void clt_create_skt(void)
{
    app_skt_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(app_skt_fd>=0)
    	return;
	printf("Client create socket error: %s(errno: %d)\n", strerror(errno),errno);
}
/**************************************************/
static struct sockaddr_in svr_skt_addr;
static const char *svr_ip_addr="127.0.0.1";
static void clt_bind_skt(void);
static void clt_bind_skt(void)
{
    if( app_skt_fd < 0)
    	return;

    memset(&svr_skt_addr, 0, sizeof(svr_skt_addr));
    svr_skt_addr.sin_family = AF_INET;
    svr_skt_addr.sin_port = htons(APP_SKT_PORT);

    int ret;
    ret=inet_pton(AF_INET, svr_ip_addr, &svr_skt_addr.sin_addr);
    if( ret >0 )
    	return;

    printf("inet_pton error for %s\n",svr_ip_addr);
    close(app_skt_fd);
    app_skt_fd=-1;
}
/**************************************************/
static void clt_connect_skt(void);
static void clt_connect_skt(void)
{
	int ret;
    ret = connect(app_skt_fd, (struct sockaddr*)&svr_skt_addr, sizeof(svr_skt_addr));
    if( ret >= 0)
    	return;

   	printf("Client connect error: %s(errno: %d)\n",strerror(errno),errno);
   	close(app_skt_fd);
   	app_skt_fd=-1;
}
/**************************************************/
static void clt_disconnect_skt(void);
static void clt_disconnect_skt(void)
{

}
/**************************************************/
static void clt_distroy_skt(void);
static void clt_distroy_skt(void)
{
   	printf("Client disconnect socket %d\n",app_skt_fd);
   	close(app_skt_fd);
   	app_skt_fd=-1;
}
/**************************************************/
void app_clt_init_skt(void);
void app_clt_init_skt(void)
{
    clt_create_skt();
    clt_bind_skt();

	clt_connect_skt();
}
/**************************************************/
void app_clt_free_skt(void);
void app_clt_free_skt(void)
{
	clt_disconnect_skt();

	clt_distroy_skt();
}


/**************************************************/
static const char *magic="Received!";
static void clt_send_skt(char *buf,int size);
static void clt_send_skt(char *buf,int size)
{
	if(app_skt_fd < 0)
		return;

	int sen_len;
	//向服务端发数据
    sen_len = send(app_skt_fd, buf, size, 0);
    if( sen_len != size)
    	goto send_err;

    //接受服务端发回确认信息
    int rec_len;
    char rec_buf[16];
    rec_len = recv(app_skt_fd, rec_buf, strlen(magic),0);
    if(rec_len > 0)
    	return;
send_err:
	printf("Client send buffer error,%d\n",sen_len);
	close(app_skt_fd);
	app_skt_fd=-1;
}
/**************************************************/
static void clt_recv_skt(char *buf,int size);
static void clt_recv_skt(char *buf,int size)
{
	if(app_skt_fd < 0)
		return;

    //接受服务端发的信息
    int rec_len;
    rec_len = recv(app_skt_fd, buf, size,0);
    if(rec_len != size)
    	goto recv_err;

	int sen_len;
	//向服务端发回确认信息
    sen_len = send(app_skt_fd, magic, strlen(magic), 0);
    if( sen_len != -1)
    	return;

recv_err:
	printf("Client receive buffer error\n");
	close(app_skt_fd);
	app_skt_fd=-1;
}


/**************************************************/
void app_clt_send_frm(char *frm,int w,int h);
void app_clt_send_frm(char *frm,int w,int h)
{
	int i;
	char *ptr;
	ptr=frm;
	printf("Client begins to send:\n");
	for(i=0;i<h;i++)
	{
		printf(".");
		clt_send_skt(ptr,w);
		ptr += w;
		if(app_skt_fd==-1)
		{
			printf("Wrong when client transfer %d line\n",i);
			break;
		}
	}
}

/**************************************************/
void app_clt_recv_frm(char *frm,int w,int h);
void app_clt_recv_frm(char *frm,int w,int h)
{
	int i;
	char *ptr;
	ptr=frm;
	printf("Client begins to receive:\n");
	for(i=0;i<h;i++)
	{
		printf(".");
		clt_recv_skt(ptr,w);
		ptr += w;
		if(app_skt_fd==-1)
		{
			printf("Wrong when client receive %d line\n",i);
			break;
		}
	}
}

/* end of clt.c */
