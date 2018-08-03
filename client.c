#include "list.h"
#include "socket.h"
#include "map.h"

t_game pong;
/***
 *  client.c
 *  fonction server
 ***/

/***
 *  Boucle client
 *  @param empty
 *  @return void
 ***/
void client_loop()
{
    int sid;
    int co;
    struct sockaddr_in server_sock;
    char buffer[1024];
    char *map_for_client;

    map_for_client = NULL;
    sid = socket(AF_INET, SOCK_STREAM, 0);
    if (sid < 0)
    {
        perror("Socket Client");
        exit(1);
    }
    printf("[+] La socket client est : %d", sid);
    memset(&server_sock, '\0', sizeof(server_sock));
    server_sock.sin_family = AF_INET;
    server_sock.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_sock.sin_port = htons(PORT);

    co = connect(sid, (struct sockaddr *)&server_sock, sizeof(server_sock));
    if (co < 0)
    {
        perror("Connection Client");
        exit(1);
    }
    printf("[+] Le client est connecte au serveur\n");
    while(42)
    {
        //send(sid, buffer, strlen(buffer), 0);
        //printf("Envoi de datas au serveur...\n");
        if (recv(sid, buffer, 1024, 0) < 0)
        {
            perror("Recv Client");
            exit(1);
        }
        else
        {
            printf("Initialisation pong.map_client\n");
            pong.map_client = init_map();
            printf("Map received : %s\n", buffer);
            string_to_map(buffer, pong.map_client);
            print_map(pong.map_client);
        }
    }
    close(sid);
}

void start_client(t_sdl *sdl)
{
    SDL_Rect  join_position = {200, 300, 400, 60};

    //render updates from server
    SDL_RenderClear(sdl->renderer);
    SDL_RenderCopy(sdl->renderer, sdl->white_black, NULL, NULL);
    SDL_RenderCopy(sdl->renderer, sdl->server_welcome, NULL, &join_position);

    //Just pour le test, affiche un mur vide..
    SDL_RenderClear(sdl->renderer);
    SDL_RenderCopy(sdl->renderer, sdl->white_black, NULL, NULL);
    //paint_map(sdl, sdl->renderer, bomberman.map_client);
    //Fin de test

    SDL_RenderPresent(sdl->renderer);
    //sdl_map(pong.map_client, sdl);
    
    client_loop();
}
