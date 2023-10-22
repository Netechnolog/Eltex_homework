#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(void){
int fd = open("file", O_CREAT | O_WRONLY, 0777);

char str[20] = "Some kind string";
char buffer[20];

write(fd, str, strlen(str));
close(fd);
fd = open("file", O_RDONLY);
read(fd, buffer, strlen(str));
printf("%s\n", buffer);
close(fd);
unlink("file");
return 0;
}