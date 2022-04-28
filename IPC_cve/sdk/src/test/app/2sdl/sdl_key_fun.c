
/*---------------------------
 * sdl_key_fun.c
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
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

/**************************************************/
int sdl_check_quit_key();
int sdl_check_quit_key()
{
	int done;
	done=0;
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            done = 1;
            break;
        }
        if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE))
        {
            done = 1;
            break;
        }
    }
    return(done);
}
#endif
#endif
/* end of sdl_key_fun.c */
