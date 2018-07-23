#include "list.h"
#include "sdl.h"
#include "socket.h"
#include "map.h"

/***
 *  main.c
 *  main fonction
 ***/

int main()
{
    t_sdl *sdl;

    sdl = init_sdl();
    sdl = init_window(sdl);
    sdl = init_fronts(sdl);
    sdl_menu(sdl);
    destroy_sdl(sdl);
    
    return (0);
}