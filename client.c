#include "socket.h"

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
            printf("Server message : %s\n", buffer);
    }
    close(sid);
}

void start_client()
{
    client_loop();
}
