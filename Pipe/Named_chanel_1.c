#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <string.h>
#include <fcntl.h>

int main (void){
  
    int fd_fifo;
    int fd_fifo1;

    char buffer[255] = {0};
    char message_1[8] = {"Hellow"};

    mkfifo("fifo_0001", 0666);
    mkfifo("fifo_0002", 0666);
    
    fd_fifo = open("fifo_0001", O_WRONLY);
    write(fd_fifo, message_1, strlen(message_1));
    close(fd_fifo);

    fd_fifo1 = open("fifo_0002", O_RDONLY);
    read(fd_fifo1, buffer, 8);
    close(fd_fifo1);
    unlink("fifo_0002");

    printf("%s\n", buffer);

    return 0;

} 