#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

int main(){
    int a = 1;
    int *p_a = &a;
    int *b;
    memcpy(b, p_a, sizeof(int)); 
    printf("%d", *b);
    return 0;
}