#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
    pid_t child_pid;
    int status;
    char str2[6] = {"ls", "-la"};
    char *ptr[5] = {&str2[0], &str2[1]};
    ptr[4] = NULL;
    child_pid = fork();
    if(child_pid == 0){
      printf("Child_pid = %d\n", getpid());
      execv("/bin/ls", ptr);
      exit(EXIT_FAILURE);
    }

    else{
      printf("parent pid = %d\n", getpid());
      wait(&status);
      printf("status = %d\n", status);
    }

    return 0;
}