#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/wait.h>

struct mymsg
    {
        long type;
        char text[10];
    } msg;


int main(void){
    int status;
    key_t key;
    int msqid;
    key = ftok("../tmp/tmp1", 2);
    
    msqid = msgget(key, 0);
    
    if (msgrcv(msqid, &msg, sizeof(msg.text), 1, 0) == -1)
        {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
    printf("Got message: %s\n", msg.text);

    strcpy(msg.text, "Hi");
    msg.type = 2;
    
    if (msgsnd(msqid, &msg, sizeof(msg.text), 0) == -1) 
        {
           perror("msgsnd error");
           exit(EXIT_FAILURE);
        }
    printf("Sent message: %s\n", msg.text);

    return 0;
}