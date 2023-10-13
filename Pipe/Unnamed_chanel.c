#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main (void){
    int status;
    int fd[2], fd_1[2];
    char buff[16] = {0};

    /*Create two chanel (or pipe), ferst for reading, second for recording*/

    pipe(fd);
    pipe(fd_1);

    pid_t child_pid;

    child_pid = fork();
    if(child_pid == 0){
        char str2[4] = "Hi";

    /*Close unused chanel, for the first case "write" for the two case "read" */

        close(fd[1]);
        close(fd_1[0]);

        read(fd[0], buff, 16);
        printf("%s\n", buff);
        write(fd_1[1], str2, strlen(str2));
        }
    else{
        char str1[8] = "Hellow";

        close(fd[0]);
        close(fd_1[1]);

        write(fd[1], str1, strlen(str1));
        wait(&status);
        read(fd_1[0], buff, 16);
        printf("%s\n", buff);
        }
    return 0;
    
}