#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(){
    unsigned int a = 5, b = 9, c = 3;
    int * ptr_a = &a;
    int * ptr_b = &b;
    int *ptr_c = &c;
    uintptr_t link_b = (uintptr_t)ptr_a^(uintptr_t)ptr_c;
    printf("%d", *(int *)(link_b ^ (uintptr_t)ptr_a));
    return 0;
}