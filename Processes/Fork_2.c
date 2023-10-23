#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    pid_t two_pid, free_pid, four_pid, fife_pid, six_pid;
    int status;
    printf("One pid = %d\n\n", getpid());
    two_pid = fork();
    if(two_pid == 0){
      printf("Two pid = %d\n", getpid());
      printf("P_two_pid = %d\n\n", getppid());
      four_pid = fork();
      if(four_pid == 0){
        printf("Four_pid = %d\n", getpid());
        printf("P_six_pid = %d\n\n", getppid());
        exit(EXIT_FAILURE);        
      }
      else{
        wait(&status);
      }
      fife_pid = fork();
      if(fife_pid == 0){
        printf("Fife_pid = %d\n", getpid());
        printf("P_fife_pid = %d\n\n", getppid());
        exit(EXIT_FAILURE);        
      }
      else{
        wait(&status);
      }
      exit(EXIT_FAILURE);
    }
    else{
        wait(&status);
    }

    free_pid = fork();
    if(free_pid == 0){
      printf("Free_pid = %d\n", getpid());
      printf("P_free_pid = %d\n\n", getppid());
      six_pid = fork();
      if(six_pid == 0){
        printf("Six_pid = %d\n", getpid());
        printf("P_six_pid = %d\n\n", getppid());
        exit(EXIT_FAILURE);
      }
      else{
        wait(&status);
      }
      exit(EXIT_FAILURE);
    }
    else{
        wait(&status);
        
    }
    return 0;
}