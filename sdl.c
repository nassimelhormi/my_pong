#include "sdl.h"
#include "socket.h"
#include "list.h"
#include "map.h"

t_game pong;

/***
 *  sdl.c
 *  fonction sdl
 ***/

/***
 *  Initialise la strucutre s_sdl
 *  @param empty
 *  @return t_sdl
 ***/
t_sdl *init_sdl()
{
    t_sdl *sdl;

    sdl = malloc(sizeof(t_sdl));
    if (sdl == NULL)
    {
        printf("Allocation structure sdl fail.\n");
        return (NULL);
    }
    sdl->screen_size.x = 640;
    sdl->screen_size.y = 480;
    sdl->window = NULL;
    sdl->renderer = NULL;
    sdl->img_menu = NULL;
    sdl->menu_background = NULL;
    sdl->white_black = NULL;
    sdl->join_game = NULL;
    sdl->create_game = NULL;
    sdl->server_welcome = NULL;
    sdl->ground = NULL;
    sdl->player = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        destroy_sdl(sdl);
        printf("SDL_Init fail.\n");
        return (NULL);
    }
    IMG_Init(IMG_INIT_JPG);
    TTF_Init();

    return (sdl);
}

/***
 *  Initialise la window et le renderer de la structure s_sdl
 *  @param t_sdl
 *  @return t_sdl
 ***/
t_sdl *init_window(t_sdl *sdl)
{
    SDL_Window	*window;
    SDL_Renderer	*renderer;
    window = SDL_CreateWindow("Pong by Nassim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sdl->screen_size.x, sdl->screen_size.y, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Initialisation of the Window failed.\n");
        return (NULL);
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
      SDL_ShowSimpleMessageBox(0, "renderer init error", SDL_GetError(), window);
      printf("Initialisation of the Renderer failed.\n");
      return (NULL);
    }
    sdl->window = window;
    sdl->renderer = renderer;

    return (sdl);
}

/***
 *  Initialise les fronts (police, image, message) de la structure s_sdl
 *  @param t_sdl
 *  @return t_sdl
 ***/
t_sdl *init_fronts(t_sdl *sdl)
{
    if (!sdl->renderer)
    {
        printf("No renderer\n");
        return (NULL);
    }
    SDL_Surface *image, *surface_player,*surface_ground,*join_game_text, *create_server_text, *server_welcome_text, *white;
    SDL_Texture *background_texture, *ground, *player,*join_texture, *server_texture, *server_welcome, *white_black;
    SDL_Color black = {65, 105, 225, 0};
    TTF_Font *police;

    image = IMG_Load("./trollface.jpg");
    white = IMG_Load("./white.jpg");
    if (!image || !white)
    {
        printf("Images not loaded.\n");
        SDL_ShowSimpleMessageBox(0, "img init error", SDL_GetError(), sdl->window);
    }
    police = TTF_OpenFont("./bm.ttf", 65);
    if (police)
        printf("police ok\n");
    else
        printf("non la police bug\n");
    join_game_text = TTF_RenderText_Blended(police, "join_game", black);
    create_server_text = TTF_RenderText_Blended(police, "create_server", black);
    server_welcome_text = TTF_RenderText_Blended(police, "WELCOME TO THE SERVER", black);

    background_texture = SDL_CreateTextureFromSurface(sdl->renderer, image);
    white_black = SDL_CreateTextureFromSurface(sdl->renderer, white);

    join_texture = SDL_CreateTextureFromSurface(sdl->renderer, join_game_text);
    server_texture = SDL_CreateTextureFromSurface(sdl->renderer, create_server_text);
    server_welcome = SDL_CreateTextureFromSurface(sdl->renderer, server_welcome_text);
    
    if (!background_texture)
    {
      printf("No textures loaded 1.\n");
      SDL_ShowSimpleMessageBox(0, "init texture error", SDL_GetError(), sdl->window);
    }
    if (!join_texture)
    {
      printf("No textures loaded 2.\n");
      SDL_ShowSimpleMessageBox(0, "init texture error", SDL_GetError(), sdl->window);
    }
    if (!white_black)
    {
      printf("No textures loaded 4.\n");
      SDL_ShowSimpleMessageBox(0, "init texture error", SDL_GetError(), sdl->window);
    }
    if (!server_texture)
    {
      printf("No textures loaded 3.\n");
      SDL_ShowSimpleMessageBox(0, "init texture error", SDL_GetError(), sdl->window);
    }
    surface_ground = IMG_Load("./ground.png");
    surface_player = IMG_Load("./player.png");
    
    ground = SDL_CreateTextureFromSurface(sdl->renderer, surface_ground);
    player = SDL_CreateTextureFromSurface(sdl->renderer, surface_player);

    sdl->menu_background = background_texture;
    sdl->white_black = white_black;
    sdl->join_game = join_texture;
    sdl->create_game = server_texture;
    sdl->server_welcome = server_welcome;
    sdl->ground = ground;
    sdl->player = player;

    return (sdl);
}

/***
 *  Creation d'un menu sdl
 *  @param t_sdl
 *  @return void
 ***/
void		sdl_menu(t_sdl *sdl)
{
    int		quit = 0;
    int		x;
    int   	y;
    int     map_shown;
    SDL_Event	event_queue;
    SDL_Rect      join_position = {200, 300, 400, 60};
    SDL_Rect      create_position = {200, 400, 400, 60};

    map_shown = 0;
    while(!quit) 
    {
        while(SDL_PollEvent(&event_queue)) 
        {
            switch(event_queue.type)
            {
                case SDL_QUIT:
	                quit = 1;
	                break;
                case SDL_MOUSEBUTTONDOWN:
	                x = event_queue.button.x;
	                y = event_queue.button.y;
	                if (( x > join_position.x ) && ( x < join_position.x + join_position.w ) && ( y > join_position.y ) && ( y < join_position.y + join_position.h ) ) {
                        start_client(sdl);
                        map_shown = 1;
                        //print_map(pong.map_client);
                        printf("join button pressed\n");
	                }
	                if (( x > create_position.x ) && ( x < create_position.x + create_position.w ) && ( y > create_position.y ) && ( y < create_position.y + create_position.h ) ) {
                        start_server();
                        printf("server button pressed\n");
	                }
	                break;
            }
        }
        if (map_shown == 0)
        {
            SDL_RenderClear(sdl->renderer);
            SDL_RenderCopy(sdl->renderer, sdl->menu_background, NULL, NULL);
            SDL_RenderCopy(sdl->renderer, sdl->join_game, NULL, &join_position);
            SDL_RenderCopy(sdl->renderer, sdl->create_game, NULL, &create_position);
            SDL_RenderPresent(sdl->renderer);
        }
    }
    return;
}

/***
 *  Delete la strucutre s_sdl
 *  @param t_sdl
 *  @return void
 ***/
void destroy_sdl(t_sdl *sdl)
{
    if (sdl)
    {
        if (sdl->img_menu)
            SDL_DestroyTexture(sdl->img_menu);
        if (sdl->renderer)
            SDL_DestroyRenderer(sdl->renderer);
        if (sdl->window)
            SDL_DestroyWindow(sdl->window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        free(sdl);
    }
}

void sdl_map(char **map, t_sdl *sdl)
{
    SDL_Rect      pos_case;
    
    int y;
    int x;

    pos_case.x = 0;
    pos_case.y = 0;
    pos_case.w = CELL_SIZE * ZOOM;
    pos_case.h = CELL_SIZE * ZOOM;
    for (x = 0; x < SIZE; x++)
    {
        for (y =0; y < SIZE; y++)
        {
            pos_case.x = x  * CELL_SIZE * ZOOM;
            if (map[y][x] == '1')
            {
                SDL_RenderCopy(sdl->renderer, sdl->player, NULL, &pos_case);
            }
            else
            {
                SDL_RenderCopy(sdl->renderer, sdl->ground, NULL, &pos_case);
            }
        }
    }
}