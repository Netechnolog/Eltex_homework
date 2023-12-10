#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>

#define N 50

void func_sock_create(int *sock, struct sockaddr_in *serv, struct sockaddr_in *cli, int len, int *connect)
{
    *sock = socket(AF_INET, SOCK_STREAM, 0);
    if(*sock == -1)
    {
        perror("Error created socket");
        exit(EXIT_FAILURE);
    }

    serv->sin_family = AF_INET;
    serv->sin_addr.s_addr = htonl(INADDR_ANY);
    serv->sin_port = htons(7777);

    if((bind(*sock, (struct sockaddr *) &(*serv), len)) == -1)
    {
        perror("Error bind");
        exit(EXIT_FAILURE);
    }

    if((listen(*sock, 5)) != 0)
    {
        perror("Error listen");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for the client to connect...\n");
    *connect = accept(*sock, (struct sockaddr *) &(*cli), &len);
    if(*connect == -1)
    {
        perror("Error connect");
        exit(EXIT_FAILURE);
    }
}

void func_send(int connect)
{
    char BUFF[N];
    strcpy(BUFF, "Hellow");

    if((send(connect, BUFF, sizeof(BUFF), 0)) == -1)
    {
        perror("Error send message");
        exit(EXIT_FAILURE);
    }

    printf("Message sent \"%s\"\n", BUFF);
}

void receve_func(int connect)
{
    char BUFF[N];
    printf("Waiting message...\n");
    if((recv(connect, BUFF, sizeof(BUFF), 0)) == -1)
    {
        perror("Error receve message");
        exit(EXIT_FAILURE);
    }

    printf("Receve message \"%s\".\n", BUFF);
}

int main(void){
    int len;
    int sck_fd; 
    int cnct;
    struct sockaddr_in server, client;
    len = sizeof(client);

    /*Create, bind, listen and accept socket*/
    func_sock_create(&sck_fd, &server, &client, len, &cnct);

    /*Sand a message, and print him on display */
    func_send(cnct);
    
    /*Waiting for message, and print him on display*/
    receve_func(cnct);

    close(sck_fd);

    return 0;
}