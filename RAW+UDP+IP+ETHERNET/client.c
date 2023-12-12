#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h>

int main(void){
int size;
int rc;
int recv = 0;
char buff[128];
struct sockaddr_in serv, client;

serv.sin_family = AF_INET;
serv.sin_addr.s_addr = inet_addr("10.0.2.15");
serv.sin_port = htons(7777);

int sck = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
if(sck == -1)
{
perror("Error created socket_1");
exit(EXIT_FAILURE);
}

if(bind(sck, (struct sockaddr *) &serv, sizeof(serv)) == -1)
{
perror("Error bind");
exit(EXIT_FAILURE);
}

size = sizeof(serv);
printf("Waiting message...\n");
if((recvfrom(sck, buff, sizeof(buff), 0, (struct sockaddr *) &client, &size)) == -1)
{
perror("Fail recvfrom");
exit(EXIT_FAILURE);
}

printf("Receve message \"%s\".\n", buff);
memset(&serv, 0, sizeof(serv));
memset(&client, 0, sizeof(client));

client.sin_family = AF_INET;
client.sin_addr.s_addr = inet_addr("192.168.0.16");
client.sin_port = htons(6333);

memset(buff, 0, sizeof(buff));
strcpy(buff, "Hellow\0");

if((sendto(sck, buff, sizeof(buff), 0, (struct sockaddr *) &client, sizeof(client))) == -1)
{
perror("Fail sendto");
exit(EXIT_FAILURE);
}

printf("Message was \"%s\" send\n", buff);

close(sck);

return 0;
}