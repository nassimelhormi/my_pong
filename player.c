#include "list.h"

/***
 *  player.c
 *  fonction player
 ***/

/***
 *  Initialise la strucutre s_player
 *  @param name
 *  @return t_player
 ***/
t_player *init_player(char *name)
{
  t_player *player;

  player = malloc(sizeof(t_player));
  if (player == NULL)
      return (0);

  player->name = strdup(name);
  player->index = 0;
  player->status = 0;
  player->prev = NULL;
  player->next = NULL;
  
  return (player);
}

/***
 *  Ajout de player dans la list chainé
 *  @param t_list_player, t_player
 *  @return void
 ***/
void add_player(t_list_player *list_player, t_player *player)
{
    player->next = NULL;
    player->prev = NULL;
    if (list_player->nb_player == 0)
    {
      list_player->first = player;
      list_player->last = player;
    }
    else if (list_player->nb_player > 0)
    {
      list_player->last->next = player;
      player->prev = list_player->last;
      list_player->last = player;
      player->next = NULL;
    }
    list_player->nb_player++;
}

/***
 *  Supprime un joueur de la list
 *  @param t_list_player, t_player
 *  @return void
 ***/
void	destroy_player(t_list_player *list_player, t_player *player)
{
  if (list_player->nb_player == 1 && player == list_player->last)
    {
      list_player->last = NULL;
      list_player->first = NULL;
      list_player->nb_player = 0;
    }
  else if (list_player->nb_player > 1 && player == list_player->first)
    {
      list_player->first = list_player->first->next;
      list_player->first->prev= NULL;
      list_player->nb_player--;
    }
  else if (list_player->nb_player > 1 && player == list_player->last)
    {
      list_player->last = list_player->last->prev;
      list_player->last->next = NULL;
      list_player->nb_player--;
    }
  else
    {
      player->next->prev = player->prev;
      player->prev->next = player->next;
      list_player->nb_player--;
    }
  free(player->name);
  free(player);
}