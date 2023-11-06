#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <mqueue.h>

#define MAX_SIZE 256

int main(void){
    char buff[256];
    mqd_t ma_1;
    mqd_t ma_2;    

    /*Open two messeage queue: first for reseiving, second for sending*/
    if((ma_1 = mq_open("/test_queue1", O_RDWR)) == -1)
        {
            perror("mq_open");
            exit(EXIT_FAILURE);        
        }

    if((ma_2 = mq_open("/test_queue2", O_RDWR)) == -1)
        {
            perror("mq_open");
            exit(EXIT_FAILURE);        
        }
    /*Recive a message from server*/
    if((mq_receive(ma_1, buff, MAX_SIZE, NULL)) == -1)
        {
            perror("mq_receive");
            exit(EXIT_FAILURE);        
        }
    printf("Receive: %s\n", buff);

    /*Send the message to server*/
    strcpy(buff, "Hi");
    if((mq_send(ma_2, buff, MAX_SIZE, 1)) == -1)
        {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }
    printf("Send: %s\n", buff);

return 0;    
}