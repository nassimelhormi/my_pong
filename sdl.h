#ifndef __SDL_H__
#define __SDL_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

# define CELL_SIZE  20
# define ZOOM       1.5

typedef struct	    s_sdl
{
    SDL_Point       screen_size;
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Texture     *img_menu;
    SDL_Texture     *menu_background;
    SDL_Texture     *white_black;
    SDL_Texture     *join_game;
    SDL_Texture     *create_game;
    SDL_Texture     *server_welcome;
    SDL_Texture     *ground;
    SDL_Texture     *player;
}                   t_sdl;

// sdl.c
t_sdl       *init_sdl();
void        destroy_sdl(t_sdl *sdl);
void		sdl_menu(t_sdl *sdl);
t_sdl       *init_fronts(t_sdl *sdl);
t_sdl       *init_window(t_sdl *sdl);
void        sdl_map(char **map, t_sdl *sdl);

#endif