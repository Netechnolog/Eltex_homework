#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(void){
    int serv_connect, socet_server, len;
    struct sockaddr_un server;
    server.sun_family = AF_LOCAL;
    strcpy(server.sun_path, "/tmp/stream_serv");
    char buff[10];
    len = sizeof(server);
    socet_server = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(socet_server == -1)
    {
        perror("Error socket");
        exit(EXIT_FAILURE);
    }

    serv_connect = connect(socet_server, (struct sockaddr *) &server, len);
    if(serv_connect == -1)
    {
        perror("Failled connect to server");
        exit(EXIT_FAILURE);
    }

    if((recv(socet_server, buff, sizeof(buff), 0)) == -1)
    {
        perror("Error receve message");
        exit(EXIT_FAILURE);
    }
    printf("Was receve message \"%s\"\n", buff);

    strcpy(buff, "Hi");
    if(send(socet_server, buff, sizeof(buff), 0) == -1)
    {
        perror("Error send message");
        exit(EXIT_FAILURE);
    }
    printf("Message \"%s\" was send\n", buff);
    close(socet_server);
    return 0;
}