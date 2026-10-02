/*
Quantos bytes o ponteiro avança a cada p++ ? E se o vetor fosse de double ?
    Avança 4 bytes, o equivalente a um inteiro. No caso do double seriam 8 bytes.
*/

#include <stdio.h>

int somaVetor(const int *v, int n){
    int soma = 0;
    
    for (int i = 0; i < n; i++){
        soma += *v;
        v++;
    }

    return soma;
}

int main(void){
    int v[] = {12, 7, 30, 4, 18}, n, soma;

    n = sizeof(v) / sizeof(int);
    soma = somaVetor(v, n);
    printf("%d\n", soma);

    return 0;
}