/*
    Escrever v = realloc(v, ...) diretamente funciona nos testes e mesmo assim é errado porque o
realloc() primeiramente copia o bloco, libera a memória e só depois tenta encontrar espaço para
armazenar o novo bloco com o tamanho desejado. Caso isso não seja possível, o ponteiro é perdido
e há vazamento de memória.

Para ler 1000 números, quantas chamadas a realloc o seu programa faz? 
    9 chamadas.

E se a capacidade crescesse de um em um, quantas seriam? 
    998 chamadas.
    
Quantos elementos seriam copiados em cada estratégia?
    Dobrando: cerca de 1000.
    Somando 1: cerca de 500000.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void){
    int *vetor, *maior;
    int entrada, tam = 0, cap = 2, reallocs = 0, soma = 0;

    vetor = malloc(sizeof(int) * 2);

    printf("Entrada: \n");
    scanf("%d", &entrada);
    while (entrada != -1){
        if (tam < cap){
            vetor[tam] = entrada;
            tam ++;
            soma += entrada;
        } else {
            maior = realloc(vetor, sizeof(vetor) * 2);
            if (maior == NULL){
                free(vetor);
                vetor = NULL;
                printf("Nao foi possivel realocar o vetor. Memoria liberada.");
                return 1;
            } else {
                vetor = maior;
                reallocs ++;
                cap *= 2;
            }

            vetor[tam] = entrada;
            tam ++;
            soma += entrada;
        }
        
        scanf("%d", &entrada);
    }

    printf("Tam: %d | Cap: %d | Reallocs: %d | Soma: %d \n", tam, cap, reallocs, soma);

    free(vetor);
    vetor = NULL;

    return 0;
}