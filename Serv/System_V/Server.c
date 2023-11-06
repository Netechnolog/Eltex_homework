#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

struct magbuf
    {
        long type;
        char text[10];
    } msg;

int main(void){
    int status;
    int msqid;

    msg.type = 1;

    int fd = open("../tmp/tmp1", O_CREAT | O_RDWR, 0666);
    key_t key;
    key = ftok("../tmp/tmp1", 2);
    msqid = msgget(key, IPC_CREAT | 0666);

    strcpy(msg.text, "Hellow");
    if(msgsnd(msqid, &msg, sizeof(msg.text), 0) == -1 )
        {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
    printf("Sent message: %s\n", msg.text);


    if(msgrcv(msqid, &msg, sizeof(msg.text), 2, 0) == -1 )
        {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }   

    printf("Reserve message: %s\n", msg.text);

    if(msgctl(msqid, IPC_RMID, 0) == -1 )
        {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

    msgctl(msqid, IPC_RMID, 0);
    unlink("../tmp/tmp1");
    return 0;
}