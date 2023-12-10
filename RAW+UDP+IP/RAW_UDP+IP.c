#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h>	

#define SOURCE 6333

int main(void){
    int sock;
    int len;
    char mesg1[128];
    char mesg2[128];
    int flag = 1;
    char *data;
    
    memset(mesg1, 0, 128);
    memset(mesg2, 0, 128);

    struct sockaddr_in client;
    struct iphdr *iphdr = (struct iphdr*) mesg1;
    struct udphdr *udph = (struct udphdr*) (mesg1 + sizeof(struct iphdr));
    struct udphdr *udph1 = (struct udphdr*) (mesg2 + sizeof(struct iphdr));
    
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(sock == -1)
    {
        perror("Socket created error");
    }

    if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag)) == -1)
    {
        perror("Error setsockopt!");
        exit(EXIT_FAILURE);
    }

    data = mesg1 + sizeof(struct iphdr) + sizeof(struct udphdr);
    strcpy(data, "Hi");

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(SOURCE);

    iphdr->version = 4;
    iphdr->ihl = 5;
    iphdr->tos = 0;
    iphdr->id = htonl(2021);
    iphdr->frag_off = 0;
    iphdr->protocol = 17;
    iphdr->ttl = 127;
    iphdr->check = 0;
    iphdr->tot_len = htons(sizeof(mesg1));
    iphdr->daddr = inet_addr("127.0.0.1");
    iphdr->saddr = inet_addr("127.0.0.1");

    udph->uh_sport = htons(SOURCE);
    udph->uh_dport = htons(7777);
    udph->uh_ulen = htons(sizeof(mesg1));
    udph->uh_sum = 0;

    if((sendto(sock, mesg1, sizeof(mesg1), 0, (struct sockaddr*) &client, sizeof(client))) == -1)
    {
        perror("Send error");
        exit(EXIT_FAILURE);
    }
    printf("Message was send\n");

    len = sizeof(client);

    while(1)
    {
    if((recvfrom(sock, mesg2, sizeof(mesg2), 0, (struct sockaddr*) &client, &len)) == -1)  
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