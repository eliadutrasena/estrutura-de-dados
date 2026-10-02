/*
Devolver esse ponteiro é seguro, mas devolver o endereço de uma variável local não é.
Qual é a diferença entre os dois casos?
    A variável local é desalocada assim que a função termina. O endereço de memória continua
    sendo válido, mas o conteúdo é lixo. Isso não acontece com esse ponteiro, que aponta pra
    um elemento do vetor da main.
*/

#include <stdio.h>

int *primeiraOcorrencia(int *v, int n, int alvo){

    for (int i = 0; i < n; i++){
        if (*v == alvo)
            return v;
        v++;
    }

    return NULL;
}

int main(void){
    int v[] = {12, 7, 30, 4, 18, 30}, *p, n;

    n = sizeof(v) / sizeof(int);
    p = primeiraOcorrencia(v, n, 30);
    if (p != NULL){
        *p = 0;
        for (int i = 0; i < n; i++) {
            printf("%d ", *(v + i));
        }
        printf("\n");
    } else {
        printf("nao encontrado");
    }

    p = primeiraOcorrencia(v, n, 99);
    if (p != NULL){
        *p = 0;
        for (int i = 0; i < n; i++) {
            printf("%d ", *(v + i));
        }
        printf("\n");
    } else {
        printf("nao encontrado");
    }

    return 0;
}