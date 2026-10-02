/*
Quantas trocas a função executa para n = 6 e para n = 7?
    3 trocas para cada. 
Escreva a expressão geral em função de n e explique o que acontece com o elemento central
quando n é ímpar.
    Nº de trocas = (int)(n / 2)
    Quando n é ímpar o elemento central continua sempre no mesmo lugar e pode ser desconsiderado.
*/

#include <stdio.h>

void inverter(int *v, int n){
    int tmp, *a = v, *b = v + (n - 1);

    for (int i = 0; i < n/2; i++){
        tmp = *a;
        *a = *b;
        *b = tmp;

        a++;
        b--;
    }
}

int main(void){
    int v[6] = {12, 7, 30, 4, 18, 9};
    int u[7] = {1, 2, 3, 4, 5, 6, 7};

    inverter(v, 6);
    for (int i = 0; i < 6; i++) {
            printf("%d ", *(v + i));
        }
        printf("\n");
    
    inverter(u, 7);
    for (int i = 0; i < 7; i++) {
            printf("%d ", *(u + i));
        }
        printf("\n");

    return 0;
}