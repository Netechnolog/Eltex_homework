#include <stdio.h>
#define N 6

int main(){
//Task 1
    int arr_1[N][N] = {0}, count = 1;
    for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){
          arr_1[i][j] = count;
          count++;
        }
    }
    for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){
          printf("%2d ", arr_1[i][j]);
        }
    printf("\n");
    }
    printf("\n");

//Task 2
    int arr_2[N] = {0}, arr_temp[N] = {0};
    for(int i = 0; i < N; i++){
      arr_2[i] = i+1;
    }
    for(int i = 0, j = N-1; i < N; i++, j--){
      arr_temp[j] = arr_2[i];
    }
    for(int i = 0; i < N; i++){
      arr_2[i] = arr_temp[i];
      printf("%2d", arr_2[i]);
    }
printf("\n\n");

//Task 3
    int arr_3[N][N] = {0};
    for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){
        arr_3[i][j] = j + i >= (N-1) ? 1 : 0;
        printf("%2d ", arr_3[i][j]);
        }
    printf("\n");
    }
printf("\n\n");

//Task 4
    int Garry[N][N] = {0};
    int i = 1, B = N;
    while(i <= N*N){
    for(int j = N-B; j < B && i <= N*N; j++, i++){
        Garry[N-B][j] = i;
    }
    for(int j = (N+1)-B; j < B && i <= N*N; j++, i++){
        Garry[j][B-1] = i;
    }
    for(int j = B - 2; j >= N-B && i <= N*N; j--, i++){
        Garry[B-1][j] = i;
    }
    for(int j = B - 2; j >= (N+1)-B && i <= N*N; j--, i++){
        Garry[j][N-B] = i;
    }
    B--;
}
    for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){
        printf("%2d ", Garry[i][j]);
      }
    printf("\n");
    }
return 0;
}