#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*Create struct for keep the contact*/
struct value {
  char NAME[11];
  char SURNAME[11];
  char NUMBER[16];
};

/*Initillaze varriable "val" for input values, array "Name" for search the contact, varriable "n" contact number*/
int main(void) {
  char val = '1', Name[11] = {0};
  int n = 1, size = sizeof(struct value);
  struct value *p;

/*It requesting number command from the user, if number command outside 1-4, then repit*/
  
  while(val != '0'){
  puts("1.Add the contact\n");
  puts("2.Search the contact\n");
  puts("3.Remove the contact\n");
  puts("4.Display all contacts\n");
  puts("0.Exit\n");
  puts("Please, enter the request:");
  val = getchar();
  if(val > 52 || val < 48){
    while(val > 52 || val < 48){
      puts("Please, enter corect request:");
    while((getchar()) != '\n');
    val = getchar();
    }
  }

/*If value val == 1, then allocate memory when it's fierst contact, otherwise expand betraid memory*/
    
    switch(val){
     case '1':
  if(n == 1){
  p = calloc(n, size);
  while((getchar()) != '\n');
  puts("Enter the name:");
  fgets(p->NAME, 11, stdin);
  puts("Enter the surname:");
  fgets(p->SURNAME, 11, stdin);
  puts("Enter the phone number:");
  fgets(p->NUMBER, 16, stdin);
  fflush(stdin);
  n++;
  }
  else{
  p = realloc(p, size * n);
  while((getchar()) != '\n');
  puts("Enter the name:");
  fgets((p + size * n)->NAME, 11, stdin);
  puts("Enter the surname:");
  fgets((p + size * n)->SURNAME, 11, stdin);
  puts("Enter the phone number:");
  fgets((p + size * n)->NUMBER, 16, stdin);
  fflush(stdin);
  n++;
  }
  break;

/*If val == 2, then requesting the desired name and save its in arr[Name],
compare arr[Name] with each 'NAME'.
If they match, then display on screen contact*/
      
    case '2':
      while((getchar()) != '\n');
      puts("Enter the name:");
      fgets(Name, 11, stdin);
      fflush(stdin);
      for(int i = 0; i <= n; i++){
      if(!(strcmp(Name, (p + size*i)->NAME))){
      puts("Contacts:");
      printf("%s%s%s\n", (p + size * i)->NAME, (p + size * i)->SURNAME, (p + size * i)->NUMBER);
      }
      }
      break;
/*implement algoritm comparsion as in 'case 3', but in case match, after n shift each contact to the left, and reduce size by 'size'*/
      
      case '3':
      puts("Enter the name:");
      while((getchar()) != '\n');
      fgets(Name, 11, stdin);
      fflush(stdin);
      for(int i = 0; i <= n; i++){
      if(!(strcmp(Name, ((p + size * i)->NAME)))){
        if(n > 1){
        for(int j = i; j < n; j++){
        *(p + size * j) =  *(p + size * (j + 1));
        }
        }
      n--;
      p = realloc(p, size * n);
      }
      }
      break;

/*Deduce everyone contact, if contacts were't found deduce "Contacts not found"*/
      
      case '4':
      //puts("Contacts:");
      if(n > 1){
      for(int i = 0; i <= n; i++){
      printf("%s%s%s\n", (p + size * i)->NAME, (p + size * i)->SURNAME, (p + size * i)->NUMBER);
      }
      }
      else{
      puts("Contacts not found");
      }
      while((getchar()) != '\n');
      break;
      default:
      break;
  }
  }
  free(p);
  return 0;
}