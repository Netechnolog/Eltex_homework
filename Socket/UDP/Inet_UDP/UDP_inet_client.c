#include <arpa/inet.h>
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>

int main(void){
    int size;
    int recv = 0;
    char buff[128];
    struct sockaddr_in serv, client;

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(7776);
    
    int sck = socket(AF_INET, SOCK_DGRAM, 0);
    if(sck == -1)
    {
        perror("Error socket_1 created");
        exit(EXIT_FAILURE);
    }

    int sck_2 = socket(AF_INET, SOCK_DGRAM, 0);
    if(sck_2 == -1)
    {
        perror("Error socket_2 created");
        exit(EXIT_FAILURE);
    }

    size = sizeof(serv);
    strcpy(buff, "Hellow");

    if((sendto(sck, buff, strlen(buff), 0, (struct sockaddr *) &client, sizeof(client))) == -1)
    {
        perror("Fail sendto");
        exit(EXIT_FAILURE); 
    }
    
    printf("Message was \"%s\" send\n", buff);
    
    memset(&serv, 0, sizeof(serv));
    memset(&client, 0, sizeof(client));

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(7778);
    
    if(bind(sck_2, (struct sockaddr *) &serv, sizeof(serv)) == -1)
    {   
        perror("Error bind");
        exit(EXIT_FAILURE);
    }

    memset(buff, 0, sizeof(buff));
    printf("Waiting message...\n");
    if((recvfrom(sck_2, buff, sizeof(buff), 0, (struct sockaddr *) &client, &size)) == -1)
    {
        perror("Fail recvfrom");
        exit(EXIT_FAILURE);
    }

    printf("Receve message \"%s\".\n", buff);    
    
    close(sck);
    close(sck_2);

    return 0;
}