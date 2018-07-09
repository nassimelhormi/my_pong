#ifndef __MAP_H__
#define __MAP_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include "list.h"

# define SIZE 20
# define MAX_PLAYERS 2

typedef struct      s_game
{
  char			    **map_server;
  char			    **map_client;
  int               status; //0 ou 1
}                   t_game;

// map.c
char    *load_map();
void    print_map(char **map);
char    *map_to_string(char **map);
void    string_to_map(char* map_string, char **map);
void    free_map(char **map);

// map_2.c
void    add_player_to_map(t_list_player *list_player, char **map);
char    **init_map();

extern  t_game pong;

#endif