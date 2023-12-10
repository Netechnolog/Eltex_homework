#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(void){
    int new_connect, len, socet_server;
    struct sockaddr_un server, client;
    server.sun_family = AF_LOCAL;
    strcpy(server.sun_path, "/tmp/stream_serv");
    char buff[10];
    strcpy(buff, "Hellow");
    socet_server = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(socet_server == -1)
    {
        perror("Socket");
        exit(EXIT_FAILURE);
    }

    len = sizeof(server) - 1;
    unlink("/tmp/stream_serv");
    if(bind(socet_server, (struct sockaddr *) &server, len) == -1)
    {   
        perror("Error bind");
        exit(EXIT_FAILURE);
    }

    if(listen(socet_server, 10) == -1)
    {
        perror("Error listen");
        exit(EXIT_FAILURE);
    }

    new_connect = accept(socet_server, (struct sockaddr *) &client, &len);
    if(new_connect == -1)
    {
        perror("Error accept");
        exit(EXIT_FAILURE);
    }

    if(send(new_connect, buff, sizeof(buff), 0) == -1)
    {
        perror("Error send message");
        exit(EXIT_FAILURE);
    }
    printf("Message \"%s\" was send\n", buff);

    if((recv(new_connect, buff, sizeof(buff), 0)) == -1)
    {
        perror("Error receve message");
        exit(EXIT_FAILURE);
    }
    printf("Was receve message \"%s\"\n", buff);

    close(new_connect);
    
    return 0;
}