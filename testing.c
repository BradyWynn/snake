#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

int main(){
    int *arr = (int *)malloc(sizeof(int) * 5);
    for(int i = 0; i < 5; i++){
        arr[i] = i;
    }
    for(int i = 0; i < 5; i++){
        printf("%d", arr[i]);
        printf("\n");
    }
    for(int i = 0; i < 4; i++){
        arr[i] = arr[i + 1];
    }
    printf("\n");
    for(int i = 0; i < 5; i++){
        printf("%d", arr[i]);
        printf("\n");
    }
   
    return 0;
}
// void func(int arr[10][10]){
//     printf("%d", *arr[0]);
// }