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

struct mq_attr attr;


int main(void){
    mqd_t mq_1;
    mqd_t mq_2;

    /*Initializing attributs of queue*/
    attr.mq_flags = 0;
    attr.mq_maxmsg = 5;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    char buff[256] = "Hellow";

    /*Creating two queue: first for sending, second for receiving*/
    if((mq_1 = mq_open("/test_queue1", O_RDWR | O_CREAT, 0666, &attr)) == -1)
        {
            perror("mq_1 open");
            exit(EXIT_FAILURE);
        }

    if((mq_2 = mq_open("/test_queue2", O_RDWR | O_CREAT, 0666, &attr)) == -1)
        {
            perror("mq_2 open");
            exit(EXIT_FAILURE);
        }

    /*Send message to client*/
    if((mq_send(mq_1, buff, MAX_SIZE, 1)) == -1)
        {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }
    printf("Send: %s\n", buff);

    /*Receive message from client*/
    if((mq_receive(mq_2, buff, MAX_SIZE, NULL))== -1)
        {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }
    printf("Receive: %s\n", buff);

    /*Close queues*/
    if((mq_close(mq_1)) == -1)
        {
            perror("mq_close_queue1");
            exit(EXIT_FAILURE);
        }   

    if((mq_close(mq_2)) == -1)
        {
            perror("mq_close_queue2");
            exit(EXIT_FAILURE);
        }   

    /*Remove queues*/
    mq_unlink("/test_queue1");

    mq_unlink("/test_queue2");
    
    printf("Message queue was deleted\n");

    return 0;
}