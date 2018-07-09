#include "list.h"

/***
 *  list_player.c
 *  fonction en rapport à la list
 ***/

/***
 *  Initialise la strucutre s_list_player
 *  @param empty
 *  @return t_list_player
 ***/
t_list_player *init_list_player()
{
    t_list_player *list_player;

    list_player = malloc(sizeof(t_list_player));
    if (list_player == NULL)
        return (0);
    list_player->first = NULL;
    list_player->last = NULL;
    list_player->nb_player = 0;

    return (list_player);
}

/***
 *  Affiche le contenu de la list (print des fd des clients)
 *  @param t_list_player
 *  @return void
 ***/
void  print_list_player(t_list_player *list)
{
  t_player *tmp;

  tmp = list->first;
  while (tmp)
  {
    printf("[+] %d", tmp->index);
    tmp = tmp->next;
  }
  putchar('\n');
}

/***
 *  Free une list et son contenu
 *  @param t_list_player
 *  @return void
 ***/
void destroy_list_player(t_list_player *list_player)
{
  t_player *cursor;
  t_player *tmp;

  cursor = list_player->first;
  while (cursor)
    {
      tmp = cursor;
      destroy_player(list_player, tmp);
      cursor = cursor->next;
    }
  free(list_player);
}
