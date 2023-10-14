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

    fd_fifo = open("fifo_0001", O_RDONLY);
    read(fd_fifo, buffer, 8);
    close(fd_fifo);
    printf("%s\n", buffer);

    unlink("fifo_0001");
 
    char message_2[4] = {"Hi"};
    fd_fifo1 = open("fifo_0002", O_WRONLY);
    write(fd_fifo1, message_2, strlen(message_2));
    close(fd_fifo1);

    return 0;

} 