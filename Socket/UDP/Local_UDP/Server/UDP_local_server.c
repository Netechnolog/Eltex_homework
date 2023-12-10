#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>


void func_sock_create(int *sock, struct sockaddr_un *server)
{
    server->sun_family = AF_LOCAL;
    strcpy(server->sun_path, "/tmp/stream_serv_udp_1");

    *sock = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if(*sock == -1)
    {
        perror("Error socket_1 created");
        exit(EXIT_FAILURE);
    }

    unlink("/tmp/stream_serv_udp_1");
    if(bind(*sock, (struct sockaddr *) &(*server), sizeof(*server)) == -1)
    {   
        perror("Error bind");
        exit(EXIT_FAILURE);
    }
}


void receve_func(int *socket, struct sockaddr_un *client, int size)
{
    char BUFF[128];
    printf("Waiting for a message...\n");
    if((recvfrom(*socket, BUFF, sizeof(BUFF), 0, (struct sockaddr *) &(*client), &size)) == -1)
    {
        perror("Fail recvfrom");
        exit(EXIT_FAILURE);
    }
    printf("Receve message \"%s\".\n", BUFF);
}


void send_func(int *socket, struct sockaddr_un *client_1)
{
    char BUFF[128];
    client_1->sun_family = AF_LOCAL;
    strcpy(client_1->sun_path, "/tmp/stream_serv_udp_2");
    strcpy(BUFF, "Hi");
    if((sendto(*socket, BUFF, strlen(BUFF), 0, (struct sockaddr *) &(*client_1), sizeof(*client_1))) == -1)
    {
        perror("Fail sendto");
        exit(EXIT_FAILURE); 
    }
    printf("Message was \"%s\" send\n", BUFF);
}


int main(void){
    int rc;
    int fd_1;
    int recv = 0;
    struct sockaddr_un serv, cli;
    int size = sizeof(serv);

    /*Create first socket with argument for transmission format UDP 
    to will receve message from client*/
    func_sock_create(&fd_1, &serv);

    /*Waiting for message, and print him on display*/
    receve_func(&fd_1, &cli, size);

    /*Sand a message, and print him on display */
    send_func(&fd_1, &cli);
   
    close(fd_1);

    return 0;
}