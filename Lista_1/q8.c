/*
Defeitos:
    Linha 4 - sizeof(v) retorna o tamanho de um ponteiro e não do vetor inteiro.
    Linha 6 - i <= n ultrapassa o tamanho do vetor e acessa memória indevida.
    Linha 11 - o endereço retornado por uma variável local é um ponteiro que aponta pra lixo.
    Linha 17 - o ponteiro não inicializado aponta pra lixo.
*/

#include <stdio.h>
 
int *maiorValor(int v[], int n) {
    int *maior = v;
    for (int i = 1; i < n; i++) {
        if (v[i] > *maior) {
            maior = v + i;
        }
    }
    return maior;
}
 
int main(void) {
    int v[5] = {12, 7, 30, 4, 18};
    int *p = maiorValor(v, 5);
    printf("%d\n", *p);
    return 0;
}