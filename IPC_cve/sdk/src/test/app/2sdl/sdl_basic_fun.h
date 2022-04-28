
/*---------------------------
 * sdl_basic_fun.h
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

#ifndef APP_2SDL_SDL_BASIC_FUN_H_
#define APP_2SDL_SDL_BASIC_FUN_H_

#include "h_share.h"

extern int sdl_check_quit_key();
extern void sdl_set_rgb_color(BYTE r,BYTE g,BYTE b);
extern void sdl_set_yuv_color(BYTE y,BYTE u,BYTE v);
extern void sdl_draw_point(int x,int y);
extern void sdl_draw_rect(int x,int y,int w,int h);
extern void sdl_draw_line(int x1, int y1, int x2, int y2);
extern void sdl_create_window(int w,int h);
extern void sdl_flush_window(void);
extern void sdl_delete_window(void);

extern void app_show_string(BYTE *out,int w,int h);

#endif 
/* end of sdl_basic_fun.h */
