/*---------------------------
 * svr.c
 *  Created on: Aug 8, 2017
 *      Author: Bailin Rui
 *---------------------------
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

#include "01import.h"

/**************************************************/

static  int    app_skt_fd, app_cnct_fd;

/**************************************************/
static void svr_create_skt(void);
static void svr_create_skt(void)
{
    app_skt_fd = socket(AF_INET, SOCK_STREAM, 0);
    if( app_skt_fd != -1 )
    	return;
   	os_print("create socket error: %s(errno: %d)\n",strerror(errno),errno);
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(APP_SKT_PORT);

    int ret;
    ret=bind(app_skt_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if( ret != -1)
    	return;

    os_print("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
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

    os_print("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
    close(app_skt_fd);
    app_skt_fd=-1;
}
/**************************************************/
static void svr_connect_skt(void);
static void svr_connect_skt(void)
{
	if(app_skt_fd == -1)
		return;

	os_print("======waiting for client's request======\n");
    app_cnct_fd = accept(app_skt_fd, (struct sockaddr*)NULL, NULL);
    if( app_cnct_fd != -1)
    	return;

   	os_print("Server accept socket error: %s(errno: %d)",strerror(errno),errno);
    close(app_skt_fd);
    app_skt_fd=-1;
}
/**************************************************/
static void svr_disconnect_skt(void);
static void svr_disconnect_skt(void)
{
	if(app_skt_fd == -1)
		return;

	os_print("Server connect %d successfully released!\n",app_cnct_fd);
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
void app_svr_recv_skt(char *buf,int size);
void app_svr_recv_skt(char *buf,int size)
{
	if(app_skt_fd == -1)
		return;

	if(app_cnct_fd == -1)
		return;

	int rec_len;
	rec_len = recv(app_cnct_fd, buf, size, 0);
    if(rec_len != size)
    	goto recv_err;

	int sen_len;
	sen_len=send(app_cnct_fd, magic, strlen(magic),0);
    if(sen_len != -1)
    	return;

recv_err:
	os_print("Server receive buffer error\n");
	close(app_cnct_fd);
	app_cnct_fd=-1;
}
/**************************************************/
void app_svr_send_skt(char *buf,int size);
void app_svr_send_skt(char *buf,int size)
{
	if(app_skt_fd == -1)
		return;

	if(app_cnct_fd == -1)
		return;

	int sen_len;
	sen_len=send(app_cnct_fd, buf, size, 0);
    if(sen_len != size)
    	goto send_err;

    int rec_len;
    char rec_buf[16];
    rec_len = recv(app_cnct_fd, rec_buf, strlen(magic), 0);
    if(rec_len > 0)
       	return;

send_err:
	os_print("Server receive buffer error\n");
	close(app_cnct_fd);
	app_cnct_fd=-1;
}

/* end of svr.c */
