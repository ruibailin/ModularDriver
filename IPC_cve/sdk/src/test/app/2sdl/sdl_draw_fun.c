
/*---------------------------
 * sdl_draw_fun.c
 *  Created on: 2017年7月12日
 *      Author: Bailin Rui
 *          作者：芮柏林
 *---------------------------
 *Provide basic draw function in screen;
 *
 *
 *
 *
 *---------------------------
 */

#include "c_share.h"

#if  IVE_UNIT_TEST
#if TEST_IN_UBUNTU
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
static SDL_Renderer *p_render;
static SDL_Window *p_screen;
/**************************************************/
void sdl_set_rgb_color(BYTE r,BYTE g,BYTE b);
void sdl_set_rgb_color(BYTE r,BYTE g,BYTE b)
{
	SDL_SetRenderDrawColor(p_render, r, g, b, 0xFF);
}
/**************************************************/
#include "../../../src/test/app/2sdl/yuv2rgb.h"
void sdl_set_yuv_color(BYTE y,BYTE u,BYTE v);
void sdl_set_yuv_color(BYTE y,BYTE u,BYTE v)
{
	BYTE r,g, b;
	r=yuv_get_r(y,u,v);
	g=yuv_get_g(y,u,v);
	b=yuv_get_b(y,u,v);
	SDL_SetRenderDrawColor(p_render, r, g, b, 0xFF);
}

/**************************************************/
void sdl_draw_point(int x,int y);
void sdl_draw_point(int x,int y)
{
	SDL_RenderDrawPoint(p_render, x,y);
}

/**************************************************/
void sdl_draw_rect(int x,int y,int w,int h);
void sdl_draw_rect(int x,int y,int w,int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(p_render, &rect);
}

/**************************************************/
void sdl_draw_line(int x1, int y1, int x2, int y2);
void sdl_draw_line(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(p_render, x1, y1, x2, y2);
}
/**************************************************/
void sdl_create_window(int w,int h);
void sdl_create_window(int w,int h)
{
	int ret;
	ret=SDL_Init(SDL_INIT_VIDEO);
	if(ret)
	{
    	printf("Unable to init SDL: %s\n", SDL_GetError());
        SDL_Quit();
	}
    p_screen = SDL_CreateWindow("Chess Board", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
	if(p_screen==NULL)
	{
    	printf("Unable to create SDL Window: %s\n", SDL_GetError());
        SDL_Quit();
	}

	SDL_Surface *p_surface;
	p_surface = SDL_GetWindowSurface(p_screen);
	p_render = SDL_CreateSoftwareRenderer(p_surface);

	if(p_render==NULL)
	{
    	printf("Unable to create SDL Render: %s\n", SDL_GetError());
        SDL_Quit();
	}

	SDL_SetRenderDrawColor(p_render, 0, 0, 0, 0xFF);
	sdl_draw_rect( 0, 0, w, h);
    SDL_UpdateWindowSurface(p_screen);
}
/**************************************************/
void sdl_flush_window(void);
void sdl_flush_window(void)
{
    SDL_UpdateWindowSurface(p_screen);
}

/**************************************************/
void sdl_delete_window(void);
void sdl_delete_window(void)
{
    SDL_Quit();
}
#endif
#endif
/* end of sdl_draw_fun.c */
