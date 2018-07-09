#include "map.h"
#include "list.h"

t_game pong;

/***
 *  map_2.c
 *  deuxieme fichier de la gestion de map
 ***/

/***
 *  Mise à jour de la map
 *  @param t_player
 *  @return void
 ***/
/*void update_map(t_player *player)
{

}*/

/***
 *  Init map
 *  @param empty
 *  @return char **
 ***/
char  **init_map()
{
  int   i;
  int   j;
  char  **map;

  map = malloc(sizeof(char *) * SIZE);
  if (NULL == map)
   return NULL;
  for (i = 0; i < SIZE; i++)
  {
    map[i] = malloc(sizeof(char *) * SIZE);
    if (map[i] == NULL)
      return NULL;
    for (j = 0; j < SIZE; j++)
    {
      map[i][j] = 0;
    }
  }
  return (map);
}


/***
 *  Position de depart d'un joueur sur la map
 *  @param t_list_player et char **
 *  @return void
 ***/
void add_player_to_map(t_list_player *list_player, char **map)
{
    if (list_player->nb_player == 1)
    {
        map[7][0]   = '1';
        map[8][0]   = '1';
        map[9][0]   = '1';
        map[10][0]  = '1';
        map[11][0]  = '1';
        map[12][0]  = '1';
    }
    if (list_player->nb_player > 1)
    {
        map[7][19]   = '1';
        map[8][19]   = '1';
        map[9][19]   = '1';
        map[10][19]  = '1';
        map[11][19]  = '1';
        map[12][19]  = '1';
    }
}