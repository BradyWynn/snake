#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
	struct node *p;
}node;

int main(){
    // node **arr = malloc(sizeof(node *));
    node a = {NULL};
    printf("%p", &a);
    printf("\n");
    node *b = {&a};
    printf("%p", b);
    printf("\n");
    b = (*b).p;
    printf("%p", b);
    return 0;
}
// void func(int arr[10][10]){
//     printf("%d", *arr[0]);
// }