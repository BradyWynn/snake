#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

__declspec(dllexport) void func(int ***a){
    printf("%d", a[0][0][0]);
}