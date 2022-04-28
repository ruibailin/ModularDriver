
/*---------------------------
 * app_show_string.c
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

#include "c_share.h"

#if  IVE_UNIT_TEST
#if TEST_IN_UBUNTU
#include "sdl_basic_fun.h"
/**************************************************/
static void app_draw_string(BYTE *out,int w,int h);
static void app_draw_string(BYTE *out,int w,int h)
{
	int i,j,k;
	k=0;
	for(i=0;i<h;i++)
		for(j=0;j<w;j++)
		{
	    	sdl_set_yuv_color(out[k],0,0);
	    	sdl_draw_point(j,i);
			k++;
		}
}
/**************************************************/
static void blk_draw_string(BYTE *out,int x,int y,int w,int h);
static void blk_draw_string(BYTE *out,int x,int y,int w,int h)
{
	int i,j,k;
	k=0;
	for(i=0;i<h;i++)
		for(j=0;j<w;j++)
		{
	    	sdl_set_yuv_color(out[k],0,0);
	    	sdl_draw_point(j+x,i+y);
			k++;
		}
}
/**************************************************/
void app_show_string(BYTE *out,int w,int h);
void app_show_string(BYTE *out,int w,int h)
{
	int done;
	done=0;
	while (!done) {
    done=sdl_check_quit_key();
    app_draw_string(out,w,h);
    sdl_flush_window();
    }
	done=0;
	while (!done) {
    done=sdl_check_quit_key();
    app_draw_string(out,w,h);
    sdl_flush_window();
    }
}
#endif
#endif
/* end of app_show_string.c */
