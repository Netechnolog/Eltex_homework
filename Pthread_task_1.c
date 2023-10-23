#include <stdio.h>
#include <pthread.h>

int j = 0;

void *func_pthread(void *number){
int *arg = (int*) number;
for(int i = 0; i <= 100000; i++){
j++;
}
return NULL;
}

int main(void) {
int number = 0;
pthread_t thread[1000];
for(int i = 0; i < 1000; i++){
pthread_create(&thread[i], NULL, func_pthread, (void*) &number);
}
for(int i = 0; i < 1000; i++){
pthread_join(thread[i], (void**) &number);
}
printf("%d\n", j);
return 0;
}
