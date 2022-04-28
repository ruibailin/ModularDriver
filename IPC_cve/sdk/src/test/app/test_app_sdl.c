
/*---------------------------
 * test_app_sdl.c
 *  Created on: 2017年7月12日
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

#include "../src/test/c_share.h"

#if  IVE_UNIT_TEST
#if  TEST_APP_SDL
#include "../app/2sdl/sdl_basic_fun.h"
#include "../app/2sdl/rgb2yuv.h"
#include <stdio.h>
#include <stdlib.h>

/**************************************************/
#include "../../test/test_app_sdl.h"

extern BYTE logodata_100x100_bgra[40000];
static void draw_logo();
static void draw_logo()
{
	int i,j,k;
	BYTE r,g,b,y,u,v;
	k=0;
	for(i=0;i<100;i++)
		for(j=0;j<100;j++)
		{
			r=logodata_100x100_bgra[4*k+2];
			g=logodata_100x100_bgra[4*k+1];
			b=logodata_100x100_bgra[4*k+0];
			y=rgb_get_y(r,g,b);
			u=rgb_get_u(r,g,b);
			v=rgb_get_v(r,g,b);
	    	sdl_set_rgb_color(y,u,y);
	    	sdl_draw_point(i,j);

	    	sdl_set_rgb_color(r,g,b);
	    	sdl_draw_point(200+i,j);
			k++;
		}
}
/**************************************************/
static void	draw_chess_board(void);
static void	draw_chess_board()
{
    int row = 0,column = 0;
    int b,w;
    for(row=0 ; row < 8; row++)
    {
        for(column=0 ; column < 8; column++)
        {
        	b = row&0x01;
        	w = column&0x01;
        	if(b^w)
        		sdl_set_rgb_color( 0, 0, 0);
        	else
           		sdl_set_rgb_color( 0xFF, 0xFF, 0xFF);
        	sdl_draw_rect(row*80,column*60,80,60);
        }
    }
}

/**************************************************/
static void	draw_random_gray(void);
static void	draw_random_gray()
{
    int row = 0,column = 0;

    BYTE y;
	srandom(255);
    for(row=0 ; row < 640; row++)
    {
        for(column=0 ; column < 480; column++)
        {
        	y=random();
       		sdl_set_yuv_color( y, 0x00, 0x00);
        	sdl_draw_point(row,column);
        }
    }
}
/**************************************************/
static void	draw_random_color(void);
static void	draw_random_color()
{
	unsigned char r,g,b;
    int row = 0,column = 0;
	srandom(1024);
	for(row=0 ; row < 640; row++)
    {
        for(column=0 ; column < 480; column++)
        {
        	r=random();
        	g=random();
           	b=random();
       		sdl_set_rgb_color( r, g, b);
        	sdl_draw_point(row,column);
        }
    }
}

/**************************************************/
static void	draw_change_gray(void);
static void	draw_change_gray()
{
	unsigned char g;
	g=0;
	int row = 0,column = 0;
    for(row=0 ; row < 640; row++)
    {
    	g++;
        for(column=0 ; column < 480; column++)
        {
       		sdl_set_yuv_color( g, 0, 0);
        	sdl_draw_point(row,column);
        }
    }
}
/**************************************************/
static void	draw_change_color(void);
static void	draw_change_color()
{
	unsigned char g;
	g=0;

	int row = 0,column = 0;
	for(row=0 ; row < 640; row++)
    {
		g++;
        for(column=0 ; column < 480; column++)
        {
       		sdl_set_yuv_color( g, g, g);
        	sdl_draw_point(row,column);
        }
    }
}


/**************************************************/
static void test_logo();
static void test_logo()
{
	int done;
	done=0;
    while (!done) {
    done=sdl_check_quit_key();
    draw_logo();
    sdl_flush_window();
    }
}
/**************************************************/
static void test_chess_board();
static void test_chess_board()
{
	int done;
	done=0;
    while (!done) {
    done=sdl_check_quit_key();
    draw_chess_board();
    sdl_flush_window();
    }
}
/**************************************************/
static void test_random_gray();
static void test_random_gray()
{
	int done;
	done=0;
    while (!done) {
    done=sdl_check_quit_key();
    draw_random_gray();
    sdl_flush_window();
    }
}
/**************************************************/
static void test_random_color();
static void test_random_color()
{
	int done;
	done=0;
    while (!done) {
    done=sdl_check_quit_key();
    draw_random_color();
    sdl_flush_window();
    }
}
/**************************************************/
static void test_change_gray();
static void test_change_gray()
{
	int done;
	done=0;
    while (!done) {
    done=sdl_check_quit_key();
    draw_change_gray();
    sdl_flush_window();
    }
}
/**************************************************/
static void test_change_color();
static void test_change_color()
{
	int done;
	done=0;
    while (!done) {
    done=sdl_check_quit_key();
    draw_change_color();
    sdl_flush_window();
    }
}
/**************************************************/
#endif
void test_app_sdl();
void test_app_sdl()
{
#if  TEST_APP_SDL
	sdl_create_window(640,480);

	test_logo();
	test_logo();
	test_random_gray();
	test_random_gray();
	test_chess_board();
	test_chess_board();
	test_random_color();
	test_random_color();

	test_change_gray();
	test_change_gray();

	/*
	test_change_color();
	test_change_color();
	test_random_gray();
	test_random_gray();
	test_chess_board();
	test_chess_board();
	test_random_color();
	test_random_color();
	test_change_gray();
	test_change_gray();
	test_change_color();
	test_change_color();
*/
    sdl_delete_window();
#endif
}
#endif
/* end of test_app_sdl.c */
