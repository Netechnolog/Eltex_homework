#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>
#include <netinet/in.h> 

int num_client = 0;


void *func_pthread_server(void* cli)
{
    int* current_connection = (int*) cli;

    while(*current_connection == 2)
    {
        sleep(0.01);
    }

    char *buff;
    buff = calloc(sizeof(char), 128);
    
    if(recv(*current_connection, buff, sizeof(buff), 0) == -1)
    {
        perror("Error recv");
        exit(EXIT_FAILURE);
    }

    printf("Was receve message from client %d:%s\n", num_client, buff);

    strcpy(buff, "Hi, client.");
    if(send(*current_connection, buff, sizeof(buff), 0) == -1)
    {
        perror("Error send message");
        exit(EXIT_FAILURE);        
    }
    printf("Message \"%s\" was send to client.\n", buff);

    free(buff);

}

int main(void){
    int new_connect, len, socet_server;
    struct sockaddr_in server, client;
    int ARRAY_CONNECTION[10];
    pthread_t thread[10];
    int sig_go;
    
    for(int i = 0; i < 10; i++)
    {
        ARRAY_CONNECTION[i] = 2;
        pthread_create(&thread[i], NULL, func_pthread_server, (void*) &ARRAY_CONNECTION[i]);        
    }
    
    socet_server = socket(AF_INET, SOCK_STREAM, 0);
    if(socet_server == -1)
    {
        perror("Socket");
        exit(EXIT_FAILURE);
    }
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(7776);

    len = sizeof(server);
    if(bind(socet_server, (struct sockaddr *) &server, len) == -1)
    {   
        perror("Error bind");
        exit(EXIT_FAILURE);
    }

    if(listen(socet_server, 10) == -1)
    {
        perror("Error listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is wait first client...\n");

    for(int i = 0; i < 10; i++)
    {
    ARRAY_CONNECTION[i] = accept(socet_server, (struct sockaddr *) &client, &len);
    if(ARRAY_CONNECTION[i] == -1)
    {
        perror("Error accept");
        exit(EXIT_FAILURE);
    }

    num_client++;
    }

    for(int i = 0; i < 10; i++)
    {
        pthread_join(thread[i], (void **) ARRAY_CONNECTION);
        close(ARRAY_CONNECTION[i]);
        printf("Was close connection: %d\n", i);
    }


    printf("All threads finish work\n");
    return 0;
}