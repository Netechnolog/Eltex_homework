#include <arpa/inet.h>
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>

#define N 50

void func_sock_create(int *sock, struct sockaddr_in *serv, int *conct)
{
    int len = sizeof(*serv);
    *sock = socket(AF_INET, SOCK_STREAM, 0);
    if(*sock == -1)
    {
        perror("Error created socket");
        exit(EXIT_FAILURE);
    }

    serv->sin_family = AF_INET;
    serv->sin_addr.s_addr = inet_addr("127.0.0.1");
    serv->sin_port = htons(7777);
    
    *conct = connect(*sock, (struct sockaddr *) &(*serv), len);
    if(*conct == -1)
    {
        perror("Error connect");
        exit(EXIT_FAILURE);
    }

}

void func_send(int socket)
{
    char BUFF[N];
    strcpy(BUFF, "Hi");

    if((send(socket, BUFF, sizeof(BUFF), 0)) == -1)
    {
        perror("Error send message");
        exit(EXIT_FAILURE);
    }

    printf("Message sent \"%s\"\n", BUFF);
}

void receve_func(int socket)
{
    char BUFF[N];
    printf("Waiting message...\n");
    if((recv(socket, BUFF, sizeof(BUFF), 0)) == -1)
    {
        perror("Error receve message");
        exit(EXIT_FAILURE);
    }

    printf("Receve message \"%s\".\n", BUFF);
}

int main(void){
    int sck_fd;
    char BUFF[N];
    int cnct;
    int len;
    struct sockaddr_in server;
    
    func_sock_create(&sck_fd, &server, &cnct);

   /*Waiting for message, and print him on display*/
    receve_func(sck_fd);

    /*Sand a message, and print him on display */
    func_send(sck_fd);

    close(sck_fd);
    return 0;
}