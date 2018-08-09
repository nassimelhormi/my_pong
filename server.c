#include "socket.h"
#include "list.h"
#include "map.h"

t_game pong;

/***
 *  server.c
 *  fonction server
 ***/

/***
 *  Initialise la strucutre s_server
 *  @param empty
 *  @return t_server
 ***/
t_server *init_struct_server()
{
    t_server *server;
    
    server = malloc(sizeof(server));
    if (server == NULL)
        return (NULL);

    server->fd = 0; 

    return (server);
}

/***
 *  Creation socket server
 *  @param t_server
 *  @return void
 ***/
void init_socket_server(t_server *server)
{
    int server_fd;
    struct sockaddr_in server_addr;
    struct protoent *protoent;

    protoent = getprotobyname("TCP");
    if ((server_fd = socket(AF_INET, SOCK_STREAM, protoent->p_proto)) == -1)
    {
        perror("Socket");
        exit(1);
    }
    printf("[+] La socket serveur est : %d", server_fd);
    putchar('\n');
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT); // 4242
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Bind");
        exit(1);
    }

    if (listen(server_fd, 2) == -1)
    {
        perror("Listen");
        exit(1);
    }

    server->fd = server_fd;
}

/***
 *  Boucle server avec acceptation de connection client et fork
 *  @param t_server
 *  @return void
 ***/
void server_loop(t_server *server, t_list_player *list_player)
{
    socklen_t sin_len_client;
    int new_socket;
    struct sockaddr_in client_addr;
    char buffer[1024];
    pid_t childpid;
    t_player *player;
    t_player *tmp;

    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    sin_len_client = sizeof(client_addr);
    while (42)
    {   
        player = init_player();
        printf("Server en attente de connection...\n");
        new_socket = accept(server->fd, (struct sockaddr *)&client_addr, &sin_len_client);
        player->index = new_socket;
        add_player(list_player, player);
        printf("Client %d accepted", new_socket);
        putchar('\n');
        add_player_to_map(list_player, pong.map_server);
        char *map_for_client = map_to_string(pong.map_server);
        printf("Fork...\n");
        if((childpid = fork()) == 0) 
        {
            close(server->fd);
            while(42)
            {
                strcpy(buffer, map_for_client);
                printf("Envoie la map au client : %s\n", buffer);
                if (list_player->nb_player == 1)
                {
                    send(new_socket, buffer, strlen(buffer), 0);
                }
                if (list_player->nb_player == 2)
                {
                    tmp = list_player->first;
                    while (tmp)
                    {
                        printf("Sending to all client\n");
                        send(tmp->index, buffer, strlen(buffer), 0);
                        tmp = tmp->next;
                    }
                }
                bzero(buffer, sizeof(buffer));
                recv(new_socket, &buffer, 3, 0);
                printf("recv from client %s\n", buffer);
            }
        }
    }
    close(new_socket);
}

void receiv_data_from_client(int client_fd, char *recvBuff)
{
    int res;
    int k;

    res = recv(client_fd, &recvBuff, 1023, 0);
    for (k=0; k<16; ++k) 
    { 
        printf("%d: 0x%02X, ", k, recvBuff[k]); 
    }
    sleep(1);
    printf("\n");
}

/***
 *  Run le server
 *  @param empty
 *  @return void
 ***/
void start_server()
{
    t_server *server;
    t_list_player *list_player;
    char *pong_string; 

    pong.map_server = init_map();
    pong_string = load_map();
    string_to_map(pong_string, pong.map_server);
    list_player = init_list_player();
    server = init_struct_server();
    init_socket_server(server);
    server_loop(server, list_player);
}
