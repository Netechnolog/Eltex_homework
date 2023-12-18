#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <string.h>

#define PATCH_SHM_1 "/tmp1.1"
#define PATCH_SHM_2 "/tmp2.1"
#define PATCH_SEM_1 "/tmp1.2"
#define PATCH_SEM_2 "/tmp2.2"

#define MSG_SIZE 128

int main(void){
    int shm_first = shm_open(PATCH_SHM_1, O_RDWR | O_CREAT, S_IRWXU);
    if(shm_first == -1)
    {
        perror("Shm_first, shm_open error");
        exit(EXIT_FAILURE);
    }

    if(ftruncate(shm_first, MSG_SIZE)==-1)
    {
        perror("First Ftruncate Error");
        exit(EXIT_FAILURE);
    }

    char* str_1 = mmap(NULL, MSG_SIZE, PROT_READ, MAP_SHARED, shm_first, 0);
    if(str_1 == MAP_FAILED)
    {
        perror("Error first mmap");
        exit(EXIT_FAILURE);
    }
    sem_t* sem_1 = sem_open(PATCH_SEM_1, O_RDWR | O_CREAT, S_IRWXU, 0);
    if(sem_1 == SEM_FAILED)
    {
        perror("Error sem_1");
        exit(EXIT_FAILURE);
    }

    sem_wait(sem_1);
    printf("%s\n", str_1);
    sem_post(sem_1);



    int shm_second = shm_open(PATCH_SHM_2, O_RDWR | O_CREAT, S_IRWXU);
    if(shm_second == -1)
    {
        perror("Shm_seocnd, shm_open error");
        exit(EXIT_FAILURE);
    }

    if(ftruncate(shm_second, MSG_SIZE) == -1)
    {
        perror("Second Ftruncate Error");
        exit(EXIT_FAILURE);
    }

    char* str_2 = mmap(NULL, MSG_SIZE, PROT_WRITE, MAP_SHARED, shm_second, 0);
    if(str_2 == MAP_FAILED)
    {
        perror("Error second mmap");
        exit(EXIT_FAILURE);
    }

    sem_t* sem_2 = sem_open(PATCH_SEM_2, O_RDWR | O_CREAT, S_IRWXU, 0);
    if(sem_2 == SEM_FAILED)
    {
        perror("Error sem_2");
        exit(EXIT_FAILURE);
    }

    strcpy(str_2, "Hellow, client!");
    sem_post(sem_2);
    sem_close(sem_2);
    sem_unlink(PATCH_SEM_1);
    munmap(str_1, MSG_SIZE);
    munmap(str_2, MSG_SIZE);
    shm_unlink(PATCH_SHM_1);

    return 0;
}