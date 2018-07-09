#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct		s_player
{
  char			      *name;
  int             index;
  int             status; //0: dead, 10: alive
  struct          s_player	*next;
  struct          s_player	*prev;
}                 t_player;

typedef struct		  s_list_player
{
  struct            s_player		*first;
  struct            s_player		*last;
  int		            nb_player;
}			              t_list_player;


// player.c
t_player        *init_player(char *name);
void            add_player(t_list_player *list_player, t_player *player);
void	          destroy_player(t_list_player *list_player, t_player *player);

// list.c
t_list_player   *init_list_player();
void            print_list_player(t_list_player *list);
void            destroy_list_player(t_list_player *list_player);

#endif