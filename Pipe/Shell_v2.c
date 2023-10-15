#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

/*Here realized chanel between two process into the shell with help "dab2"*/

int main(void) {

  char COMMAND[100];

  while((strcmp(COMMAND, "exit"))){  
  
  pid_t chaild_pid;
  pid_t chaild_pid1;
  int status;
  char div_1[3] = " ";
  char div_2[4] = "|";
  char arg1[12] = {"/bin/"};
  char *ptr_prt_command[5];
  char *ptr_command[10];
  int fd[2];
  pipe(fd);
  
  fgets(COMMAND, 98, stdin);
  COMMAND[strlen(COMMAND)-1] = 0;

  /*Devidе main command into tokens witch help "|"*/

  ptr_command[0] = strtok(COMMAND, div_2);
  for(int i = 1; ptr_command[i-1] != NULL; i++){
  ptr_command[i] = strtok(NULL, div_2);
  }

  /*Now devide separate command into the tokens witch help "space"*/
  ptr_prt_command[0] = strtok(ptr_command[0], div_1);
  
  for(int i = 1; ptr_prt_command[i-1] != NULL; i++){
  ptr_prt_command[i] = strtok(NULL, div_1);
  }

  /*An additional process is created to execute the first command.
   If there more command, so writing data into the std.thread_write,
   after writing close std_phtread_write in string 63.*/

  chaild_pid = fork();
  if(chaild_pid == 0){

  if(ptr_command[1] != NULL){
  dup2(fd[1], 1);
  }

  strncat(arg1, ptr_prt_command[0], 10);
  execv(arg1, ptr_prt_command);

  if((strcmp(COMMAND, "exit"))){
  printf("%s:Command: not found\n", COMMAND);
  }
  exit(EXIT_SUCCESS);
  }
  else{
  if(ptr_command[1] != NULL){
  close(fd[1]);
  }
  wait(&status);
  }

  /*If exist more command, so we devide them into the token similar to
  the first command, and replace STD_INPUT by 
  fd[0](thrad output of first process)*/

  for(int j = 1; ptr_command[j] != NULL; j++){
  
  ptr_prt_command[0] = strtok(ptr_command[j], div_1);

  for(int i = 1; ptr_prt_command[i-1] != NULL; i++){
  ptr_prt_command[i] = strtok(NULL, div_1);
  }

  chaild_pid1 = fork();

  if(chaild_pid1 == 0){
  dup2(fd[0], 0);
  strncat(arg1, ptr_prt_command[0], 10);
  execv(arg1, ptr_prt_command);

  if((strcmp(COMMAND, "exit"))){
  printf("%s:Command: not found\n", ptr_command[j]);
  }
  exit(EXIT_SUCCESS);
  }
  else{
  close(fd[1]);
  close(fd[0]);
  wait(&status);
  }

  }
  }
  return 0;
}