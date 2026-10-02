/*
O que acontece se o vetor de destino for menor que a origem? O programa avisa?
    O programa compila e roda sem nenhum erro aparente, mas o que aconteceu foi a escrita além
    do limite do vetor em uma outra região de memória.
*/

#include <stdio.h>

int  meuStrlen(const char *s){
    int c = 0;

    while (*s != '\0'){
        c++;
        s++;
    }

    return c;
}

void meuStrcpy(char *destino, const char *origem){

    while (*origem != '\0'){
        *destino = *origem;
        origem++;
        destino++;
    }
    *destino = '\0';
}

int main(void){
    char v[19] = "Estrutura de Dados", u[19];
    int tam;

    meuStrcpy(u, v);
    tam = meuStrlen(u);
    printf("%s|%d\n", u, tam);

    return 0;
}