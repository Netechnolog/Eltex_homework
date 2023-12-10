#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

void func_sock_create(int *sock_1, int* sock_2, struct sockaddr_un *server, struct sockaddr_un *client)
{
    client->sun_family = AF_LOCAL;
    strcpy(client->sun_path, "/tmp/stream_serv_udp_1");

    server->sun_family = AF_LOCAL;
    strcpy(server->sun_path, "/tmp/stream_serv_udp_2");

    *sock_1 = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if(*sock_1 == -1)
    {
        perror("Error socket_1 created");
        exit(EXIT_FAILURE);
    }

    *sock_2 = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if(*sock_2 == -1)
    {
        perror("Error socket_2 created");
        exit(EXIT_FAILURE);
    }
}

void func_send(int *socket, struct sockaddr_un *client)
{
    char BUFF[128];
    strcpy(BUFF, "Hellow");

    if((sendto(*socket, BUFF, strlen(BUFF), 0, (struct sockaddr *) &(*client), sizeof(*client))) == -1)
    {
        perror("Fail sendto");
        exit(EXIT_FAILURE); 
    }
    
    printf("Message was \"%s\" send\n", BUFF);
}

void func_recev(int *socket, struct sockaddr_un *server)
{
    int size = sizeof(*server);
    char BUFF[128];

    unlink("/tmp/stream_serv_udp_2");
    if(bind(*socket, (struct sockaddr *) &(*server), sizeof(*server)) == -1)
    {   
        perror("Error bind");
        exit(EXIT_FAILURE);
    }
    
    memset(BUFF, 0, sizeof(BUFF));
    printf("Waiting message...\n");
    if((recvfrom(*socket, BUFF, sizeof(BUFF), 0, (struct sockaddr *) &(*server), &size)) == -1)
    {
        perror("Fail recvfrom");
        exit(EXIT_FAILURE);
    }

    printf("Receve message \"%s\".\n", BUFF);  
}

int main(void){
    int recv = 0;
    char buff[128];
    struct sockaddr_un serv, cli;
    int sck_1, sck_2;
    
    /*Create sock, and initiallizete structs "sockaddr_un"*/
    func_sock_create(&sck_1 , &sck_2, &serv, &cli);

    /*Send message to client*/
    func_send(&sck_1, &cli);

    /*Receve message from server*/
    func_recev(&sck_2, &serv);
    
    close(sck_1);
    close(sck_2);

    return 0;
}