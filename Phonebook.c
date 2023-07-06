#include <stdio.h>
#include <string.h>

int main() {
int val = 1;
char Name[9] = {0}, next;
struct value {
    char NAME[11];
    char SURNAME[11];
    char PHONE_NUMBER[16];
};
struct value person[99];
for(int j = 0; j < 100; j++){
  for(int i = 0; i <= 10; i++){
    person[j].NAME[i] ='0';
    person[j].SURNAME[i] ='0';
    person[j].PHONE_NUMBER[i] = '0';
  }
}

while(val != 0){
  printf("1.Add the contact\n");
  printf("2.Search the contact\n");
  printf("3.Remove the contact\n");
  printf("4.Display all contacts\n");
  printf("0.Exit\n");
  printf("Please, enter the request:\n");
  scanf("%d", &val);
  if(val > 4)
    while(val > 4){
      printf("Please, enter corect request:");
      scanf("%d", &val);
    }
    switch(val){
     case 1:
     printf("Enter the name:");
       for(int i = 0; i < 100; i++){
         if(person[i].NAME[0] == '0'){
         scanf("%s", person[i].NAME);
         printf("Enter the surname:");
         scanf("%s", person[i].SURNAME);
         printf("Enter the number:");
         scanf("%s", person[i].PHONE_NUMBER);
         break;
         }
       }
    printf("\n\n");
     break;
     case 2:
     printf("Enter the name:");
     scanf("%s", Name);
       for(int j = 0; j < 100; j++){
         if(!(strcmp(person[j].NAME, Name))){
           printf("%s %s %s\n", person[j].NAME, person[j].SURNAME, person[j].PHONE_NUMBER);
         }
       }  
     printf("\n\n");
     break;
     case 3:
     printf("Please enter the contact you want to delete:");
     scanf("%s", Name);
     for(int j = 0; j < 100; j++){
       if(!(strcmp(person[j].NAME, Name))){
         for(int i = 0; i <= 10; i++){
           person[j].NAME[i] = '0';
           person[j].SURNAME[i] = '0';
           person[j].PHONE_NUMBER[i] = '0';
         }
       }
     }
     printf("\n\n");
     break;
     case 4:
       for(int k = 0; k < 100; k++){
         if(person[k].NAME[0] != '0'){
           printf("%s %s %s\n", person[k].NAME, person[k].SURNAME, person[k].PHONE_NUMBER);
         }
       }
     printf("\n\n");
     break;
     default:
     printf("Please, enter corect request:");
     break;
    }
}
return 0;
}