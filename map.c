#include "map.h"

/***
 *  map.c
 *  gestion de la map
 ***/

/***
 *  Load la map vierge contenu dans le fichier "pong.map"
 *  @param empty
 *  @return char *
 ***/
char *load_map()
{
    FILE *file = fopen("./pong.map", "r");
    char *map_from_file;
    size_t n = 0;
    int c;

    if (file == NULL)
        return NULL;
    map_from_file = malloc(1000);
    while ((c = fgetc(file)) != EOF)
        map_from_file[n++] = (char) c;
    map_from_file[n] = '\0';        

    return (map_from_file);
}

/***
 *  print une map 
 *  @param char **
 *  @return void
 ***/
void  print_map(char **map)
{
  int             i;
  int             j;

  for (i = 0; i < SIZE; i++)
  {
    for (j = 0; j < SIZE; j++)
    {
      printf(" %c ", map[i][j]);
    }
    printf("\n");
  }
}

/***
 *  Transforme un char ** en string
 *  @param char **
 *  @return char *
 ***/
char *map_to_string(char **map)
{
  char *map_string;
  int i;
  int j;
  int k;

  k = 0;
  map_string = malloc(sizeof(char *) * 420);
  for (i = 0; i < SIZE; i++)
  {
    for (j = 0; j < SIZE; j++)
    {
      map_string[k] = map[i][j];
      k++;
    }
    map_string[k] = '\n';
    k++;
  }
  map_string[k] = '\0';

  return (map_string);
}

/***
 *  Transforme un char * en char **
 *  @param char * et char **
 *  @return void
 ***/
void string_to_map(char* map_string, char **map)
{
  int i;
  int j;
  unsigned long k;
  
  i = 0;
  j = 0;
  k = 0;

  printf("Dans la fonction string_to_map\n");
  printf("map_string : %s", map_string);
  for (k = 0; k < strlen(map_string); k++)
  { 
      if (map_string[k] != '\n')
      {
        map[i][j] = map_string[k];
        j++;
      }
      else
      {
        i++;
        j = 0;
      }
  }
  printf("Fin de la fonction string_to_map\n");
}

/***
 *  Libere la memoire d'une map
 *  @param char **
 *  @return void
 ***/
void  free_map(char **map)
{
  int   i;

  for (i = 0; i < SIZE; i++)
  {
    free(map[i]);
  }
  free(map);
}

