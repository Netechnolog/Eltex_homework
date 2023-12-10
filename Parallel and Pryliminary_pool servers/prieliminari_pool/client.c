#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h> 

int main(void){
    int serv_connect, socet_server, len;
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr =inet_addr("127.0.0.1");
    server.sin_port = htons(7776);

    char buff[20];
    len = sizeof(server);
    socet_server = socket(AF_INET, SOCK_STREAM, 0);
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
    strcpy(buff, "Hellow, server");
    if(send(socet_server, buff, sizeof(buff), 0) == -1)
    {
        perror("Error send message");
        exit(EXIT_FAILURE);
    }
    printf("Message \"%s\" was send\n", buff);

    if((recv(socet_server, buff, sizeof(buff), 0)) == -1)
    {
        perror("Error receve message");
        exit(EXIT_FAILURE);
    }
    printf("Was receve message \"%s\"\n", buff);

    close(socet_server);
    return 0;
}