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
    char s[10]={}, s1[10]={};
    struct sockaddr_in server_sock;

    sid = socket(AF_INET,SOCK_STREAM,0);
    server_sock.sin_family = AF_INET;
    server_sock.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_sock.sin_port = htons(PORT);

    connect(sid,(struct sockaddr *)&server_sock,sizeof(server_sock));
    while(1)
    {
        printf("\n Enter the string:");
        scanf("%s",s);
        write(sid,(void*)s,strlen(s));
        if(strlen(s)==0)
            break;
        sleep(1);
        read(sid,(void*)s1,sizeof(s1));
        printf("\n The received string is:%s\n",s1);
    }
    close(sid);
}
