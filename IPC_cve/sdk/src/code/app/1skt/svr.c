/*---------------------------
 * svr.c
 *  Created on: Aug 8, 2017
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *To receive a yuv stream from IVE in 6805 board
 *svr:server
 *skt:socket
 *cnct:connect
 *fd:file description
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

static  int    app_skt_fd, app_cnct_fd;

/**************************************************/
static void svr_create_skt(void);
static void svr_create_skt(void)
{
    app_skt_fd = socket(AF_INET, SOCK_STREAM, 0);
    if( app_skt_fd != -1 )
    	return;
   	printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
}
/**************************************************/
static void svr_bind_skt(void);
static void svr_bind_skt(void)
{
	if(app_skt_fd == -1)
		return;

	struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。
    servaddr.sin_port = htons(APP_SKT_PORT);//设置的端口为DEFAULT_PORT

    //将本地地址绑定到所创建的套接字上
    int ret;
    ret=bind(app_skt_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if( ret != -1)
    	return;

    printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    close(app_skt_fd);
    app_skt_fd=-1;
   	return;
}
/**************************************************/
static void svr_listen_skt(void);
static void svr_listen_skt(void)
{
	if(app_skt_fd == -1)
		return;

    int ret;
    ret=listen(app_skt_fd, 10);
    if( ret != -1)
    	return;

    printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
    close(app_skt_fd);
    app_skt_fd=-1;
}
/**************************************************/
static void svr_connect_skt(void);
static void svr_connect_skt(void)
{
	if(app_skt_fd == -1)
		return;

	printf("======waiting for client's request======\n");
	//阻塞直到有客户端连接，不然多浪费CPU资源。
    app_cnct_fd = accept(app_skt_fd, (struct sockaddr*)NULL, NULL);
    if( app_cnct_fd != -1)
    	return;

   	printf("Server accept socket error: %s(errno: %d)",strerror(errno),errno);
    close(app_skt_fd);
    app_skt_fd=-1;
}
/**************************************************/
static void svr_disconnect_skt(void);
static void svr_disconnect_skt(void)
{
	if(app_skt_fd == -1)
		return;

	printf("Server connect %d successfully released!\n",app_cnct_fd);
	close(app_cnct_fd);
	app_cnct_fd=-1;
}
/**************************************************/
static void svr_distroy_skt(void);
static void svr_distroy_skt(void)
{
	if(app_skt_fd == -1)
		return;

    close(app_skt_fd);
    app_skt_fd=-1;
}
/**************************************************/
void app_svr_init_skt(void);
void app_svr_init_skt(void)
{
    svr_create_skt();
    svr_bind_skt();
    svr_listen_skt();

	svr_connect_skt();
}
/**************************************************/
void app_svr_free_skt(void);
void app_svr_free_skt(void)
{
	svr_disconnect_skt();

	svr_distroy_skt();
}

/**************************************************/
static const char *magic="Received!";
static void svr_recv_skt(char *buf,int size);
static void svr_recv_skt(char *buf,int size)
{
	if(app_skt_fd == -1)
		return;

	if(app_cnct_fd == -1)
		return;

	int rec_len;
	//接受客户端传过来的数据
	rec_len = recv(app_cnct_fd, buf, size, 0);
    if(rec_len != size)
    	goto recv_err;

	int sen_len;
    //向客户端发送回应数据
	sen_len=send(app_cnct_fd, magic, strlen(magic),0);
    if(sen_len != -1)
    	return;

recv_err:
	printf("Server receive buffer error\n");
	close(app_cnct_fd);
	app_cnct_fd=-1;
}
/**************************************************/
static void svr_send_skt(char *buf,int size);
static void svr_send_skt(char *buf,int size)
{
	if(app_skt_fd == -1)
		return;

	if(app_cnct_fd == -1)
		return;

	int sen_len;
    //向客户端发送数据
	sen_len=send(app_cnct_fd, buf, size, 0);
    if(sen_len != size)
    	goto send_err;

    //接受客户端传过来的回应数据
    int rec_len;
    char rec_buf[16];
    rec_len = recv(app_cnct_fd, rec_buf, strlen(magic), 0);
    if(rec_len > 0)
       	return;

send_err:
	printf("Server receive buffer error\n");
	close(app_cnct_fd);
	app_cnct_fd=-1;
}


/**************************************************/
void app_svr_recv_frm(char *frm,int w,int h);
void app_svr_recv_frm(char *frm,int w,int h)
{
	int i;
	char *ptr;
	ptr=frm;
	printf("Server begins to receive:\n");
	for(i=0;i<h;i++)
	{
		printf(".");
		svr_recv_skt(ptr,w);
		ptr += w;
		if(app_cnct_fd==-1)
			printf("Wrong when server receive %d line\n",i);
	}
}

/**************************************************/
void app_svr_send_frm(char *frm,int w,int h);
void app_svr_send_frm(char *frm,int w,int h)
{
	int i;
	char *ptr;
	ptr=frm;
	printf("Server begins to send:\n");
	for(i=0;i<h;i++)
	{
		printf(".");
		svr_send_skt(ptr,w);
		ptr += w;
		if(app_cnct_fd==-1)
			printf("Wrong when server send %d line\n",i);
	}
}

/* end of svr.c */
