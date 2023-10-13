#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_once_t once = PTHREAD_ONCE_INIT;
pthread_key_t key;

void dest(void *customer)
{
 free(customer);
}

void key_create(void)
{
 pthread_key_create(&key, dest);
}

void *func_customer(void *SHOP){
 int *SHOPS = (int*)SHOP;
 srand(time(NULL));
 int * customer;
 int number_customer = 1;
 pthread_once(&once, key_create); 
 
 customer = pthread_getspecific(key);
 if(customer == NULL){
 customer = malloc(sizeof(int));
 *customer = 10000;
 pthread_setspecific(key, customer);
 }
 while(*customer > 0){
 int shop = rand()%5;
 
 switch(shop){
 case 0:
 pthread_mutex_lock(&m1);
 if(SHOPS[0] > 0){
 printf("У покупателя было: %d, он купил в магазине %d\n", *customer, shop + 1);
 *customer = *customer - SHOPS[0];
 SHOPS[0] = 0;
 printf("У покупателя осталось: %d\n\n", *customer);
 }
 pthread_mutex_unlock(&m1);
 break; 

 case 1:
 pthread_mutex_lock(&m1);
 if(SHOPS[1] > 0){
  printf("У покупателя было: %d, он купил в магазине %d\n", *customer, shop + 1);
 *customer = *customer - SHOPS[1];
 SHOPS[1] = 0;
 printf("У покупателя осталось: %d\n\n", *customer);
 }
 pthread_mutex_unlock(&m1);
 break;

 case 2:
 pthread_mutex_lock(&m1);
 if(SHOPS[2] > 0){
  printf("У покупателя было: %d, он купил в магазине %d\n", *customer, shop + 1);
 *customer = *customer - SHOPS[2];
 SHOPS[2] = 0;
 printf("У покупателя осталось: %d\n\n", *customer);
 }
 pthread_mutex_unlock(&m1);
 break;

 case 3:
 pthread_mutex_lock(&m1);
 if(SHOPS[3] > 0){
  printf("У покупателя было: %d, он купил в магазине %d\n", *customer, shop + 1);
 *customer = *customer - SHOPS[3];
 SHOPS[3] = 0;
 printf("У покупателя осталось: %d\n\n", *customer);
 }
 pthread_mutex_unlock(&m1);
 break;
   
 case 4:
 pthread_mutex_lock(&m1);
 if(SHOPS[4] > 0){
  printf("У покупателя было: %d, он купил в магазине %d\n", *customer, shop + 1);
 *customer = *customer - SHOPS[4];
 SHOPS[4] = 0;
 printf("У покупателя осталось: %d\n\n", *customer);
 }
 pthread_mutex_unlock(&m1);
 break;
 }
 sleep(1);
 }
 if(*customer <= 0){
  printf("Покупатель %d закончил покупки\n", number_customer);
  number_customer++;
 }
}

/*Create fuction for add point in shops, and create random shop*/
void *func_loader(void *SHOP){
 int *SHOPS = (int*) SHOP;
 int loader = 500;
  
 srand(time(NULL));
 while(1){
 int tmp = (rand()%5);
 pthread_mutex_lock(&m1);
 printf("Погрузчик положил 500 единиц товара в магазин:%d\n", tmp+1);
 *(SHOPS + tmp) += loader;
 printf("Теперь там: %d\n\n", SHOPS[tmp]);
 pthread_mutex_unlock(&m1);
 sleep(2);
 }
}

  int main(){
 printf("Создаем 5 магазинов, и вызваем 4 потока (3 покупателя, и 1 погрузчик");
 pthread_t thread[3];
 int ARR_SHOPS[5] = {1000, 1000, 1000, 1000, 1000};
 int *ptr = ARR_SHOPS;

 for(int i = 0; i < 3; i++)
 {
 pthread_create(&thread[i], NULL, func_customer, (void*) ptr);
 }

 pthread_create(&thread[3], NULL, func_loader, (void*) ptr);
 
 for(int i = 0; i < 3; i++)
 {
 pthread_join(thread[i], (void**) &ptr);
 }
 pthread_join(thread[3], (void**) &ptr);
 printf("Конец работы\n");
return 0;
}
