#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h>	
#include <netpacket/packet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <net/ethernet.h>

#define SOURCE          6333
#define DEFAULT_IF      "enp0s3"

unsigned short csum(unsigned short *buf, int nwords)
{
    unsigned long sum;
    for(sum = 0; nwords > 0; nwords--)
    sum += *buf++;
    sum = (sum >> 16) + (sum &0xffff);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}

int main(int argc, char *argv[]){
    int sock;
    int len;
    char mesg1[128];
    char mesg2[128];
    int flag = 1;
    char *data;

    struct ifreq if_idx;
	struct ifreq if_mac;
    struct ether_header *ethhdr = (struct ether_header*) mesg1;
    struct iphdr *iphd = (struct iphdr*) (mesg1 + sizeof(struct ether_header));
    struct udphdr *udph = (struct udphdr*) (mesg1 + sizeof(struct iphdr) + sizeof(struct ether_header));
    struct udphdr *udph1 = (struct udphdr*) (mesg2 + sizeof(struct iphdr));
    char ifname[IFNAMSIZ];
    
    memset(mesg1, 0, 128);
    memset(mesg2, 0, 128);

    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(sock == -1)
    {
        perror("Socket created error");
    }

    if (argc > 1)
    {
        strcpy(ifname, argv[1]);
    }
    else
    {
        strcpy(ifname, DEFAULT_IF);
    }

    strncpy(if_idx.ifr_name, ifname, IFNAMSIZ-1);
	if (ioctl(sock, SIOCGIFINDEX, &if_idx) < 0)
    {
	    perror("SIOCGIFINDEX");
    }

	strncpy(if_mac.ifr_name, ifname, IFNAMSIZ-1);
	if (ioctl(sock, SIOCGIFHWADDR, &if_mac) < 0)
    {
	    perror("SIOCGIFHWADDR");
    }

    ethhdr->ether_dhost[0] = 0x08;
    ethhdr->ether_dhost[1] = 0x00;
    ethhdr->ether_dhost[2] = 0x27;
    ethhdr->ether_dhost[3] = 0x6d;
    ethhdr->ether_dhost[4] = 0xeb;
    ethhdr->ether_dhost[5] = 0xb5;


    ethhdr->ether_shost[0] = ((uint8_t*)&if_mac.ifr_hwaddr.sa_data)[0];
    ethhdr->ether_shost[1] = ((uint8_t*)&if_mac.ifr_hwaddr.sa_data)[1];
    ethhdr->ether_shost[2] = ((uint8_t*)&if_mac.ifr_hwaddr.sa_data)[2];
    ethhdr->ether_shost[3] = ((uint8_t*)&if_mac.ifr_hwaddr.sa_data)[3];
    ethhdr->ether_shost[4] = ((uint8_t*)&if_mac.ifr_hwaddr.sa_data)[4];
    ethhdr->ether_shost[5] = ((uint8_t*)&if_mac.ifr_hwaddr.sa_data)[5];
    ethhdr->ether_type = htons(ETH_P_IP);

    struct sockaddr_ll server;
    server.sll_addr[0] = 0x08;
    server.sll_addr[1] = 0x00; 
    server.sll_addr[2] = 0x27; 
    server.sll_addr[3] = 0x6d; 
    server.sll_addr[4] = 0xeb; 
    server.sll_addr[5] = 0xb5;
    server.sll_halen = ETH_ALEN;
    server.sll_ifindex = if_idx.ifr_ifindex;

    iphd->version = 4;
    iphd->ihl = 5;
    iphd->tos = 0;
    iphd->id = htonl(2021);
    iphd->frag_off = 0;
    iphd->protocol = 17;
    iphd->ttl = 127;
    iphd->tot_len = htons(sizeof(mesg1) - sizeof(struct ether_header));
    iphd->daddr = inet_addr("10.0.2.15");
    iphd->saddr = inet_addr("192.168.0.16");
    iphd->check = 0;

    udph->uh_sport = htons(SOURCE);
    udph->uh_dport = htons(7777);
    udph->uh_ulen = htons(sizeof(mesg1)-sizeof(struct iphdr) - sizeof(struct ether_header));
    udph->uh_sum = 0;

    iphd->check = csum((unsigned short *)mesg1, + sizeof(struct iphdr) + sizeof(struct udphdr));

    data = sizeof(struct ether_header)+ sizeof(struct iphdr) + sizeof(struct udphdr) + mesg1;
    strcpy(data, "Hi");

    if((sendto(sock, mesg1, sizeof(mesg1), 0, (struct sockaddr*) &server, sizeof(struct sockaddr_ll))) == -1)
    {
        perror("Send error");
        exit(EXIT_FAILURE);
    }
    printf("Message was send\n");

    len = sizeof(server);

    while(1)
    {
    if((recvfrom(sock, mesg2, sizeof(mesg2), 0, (struct sockaddr*) &server, &len)) == -1)  
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