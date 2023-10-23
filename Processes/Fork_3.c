#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(void) {
  char COMMAND[100];
  while((strcmp(COMMAND, "exit"))){  
  pid_t chaild_pid;
  int status;
  char div[3] = " ";
  char arg1[12] = {"/bin/"};
  char *ptr[5], *token;
  fgets(COMMAND, 98, stdin);
  COMMAND[strlen(COMMAND)-1] = 0;
  ptr[0] = strtok(COMMAND, div);
  strncat(arg1, ptr[0], 10);
  for(int i = 1; ptr[i-1] != NULL; i++){
  ptr[i] = strtok(NULL, div);
  }
  chaild_pid = fork();
  if(chaild_pid == 0){
  execv(arg1, ptr);
  if((strcmp(COMMAND, "exit"))){
  printf("%s:Command: not found\n", COMMAND);
  }
  exit(EXIT_SUCCESS);
  }
  else{
  wait(&status);
  }
  }
  return 0;
}