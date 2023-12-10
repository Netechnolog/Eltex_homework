#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<netinet/ip.h>	

#define SOURCE 6222

int main(void){
    int sock;
    int len;
    char mesg[128];
    char mesg2[128];
    char *data;
    
    memset(mesg, 0, strlen(mesg));
    memset(mesg2, 0, strlen(mesg2));

    struct sockaddr_in client;
    struct udphdr *udph = (struct udphdr*) mesg;
    struct udphdr *udph1 = (struct udphdr*) (mesg2 + sizeof(struct iphdr));
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(sock == -1)
    {
        perror("Socket created error");
    }
    
    data = mesg + sizeof(struct iphdr) + sizeof(struct udphdr);
    strcpy(data, "Hi, server");

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = htonl(INADDR_ANY);
    client.sin_port = htons(SOURCE);

    udph->uh_sport = htons(SOURCE);
    udph->uh_dport = htons(7777);
    udph->uh_ulen = htons(sizeof(mesg));
    udph->uh_sum = 0;

    char *mes = "Hi, server\0";
   
    for(int i = 0; mes[i] != '\0'; i++){
        mesg[sizeof(udph) + i] = mes[i];
    }

    if((sendto(sock, &mesg, sizeof(mesg), 0, (struct sockaddr*) &client, sizeof(client))) == -1)
    {
        perror("Send error");
        exit(EXIT_FAILURE);
    }
    printf("Message was send\n");

    memset(mesg, 0, strlen(mesg));
    len = sizeof(client);

    while(1)
    {
    if((recvfrom(sock, (char*) mesg2, sizeof(mesg2), 0, (struct sockaddr*) &client, &len)) == -1)  
    {
        perror("Error reveive");
        exit(EXIT_FAILURE);
    }

    if(ntohs(udph1->uh_dport) == SOURCE)
    {
    printf("Was recive message:\n");
    for(int i = 28; mesg2[i] != '\0'; i++)
    {
        printf("%c", mesg2[i]);
    }
    printf("\n");
    }
    }
    
    close(sock);
    return 0;
}