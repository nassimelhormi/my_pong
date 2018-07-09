#ifndef __LIST_H__
#define __LIST_H__

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

# define PORT 4242

typedef struct	    s_server
{
  int               fd;
}                   t_server;

typedef struct	    s_client
{
  int               fd_first;
  int               fd_second;
}                   t_client;

// server.c
void        start_server();
void        server_loop(t_server *server);
void        init_socket_server(t_server *server);
t_server    *init_struct_server();
void        receiv_data_from_client(int client_fd, char *recvBuff);

// client.c
void        client_loop(t_client *client);
t_client    *init_struct_client();
void        start_client();

#endif