#include <stdio.h>

void ordenarPar(int *a, int *b){
    if (*a > *b){
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

int main(void){

    int a = 9, b = 5;
    ordenarPar(&a, &b);
    printf("%d %d\n", a, b);

    a = 2, b = 7;
    ordenarPar(&a, &b);
    printf("%d %d\n", a, b);

    return 0;
}