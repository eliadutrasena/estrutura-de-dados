/*
Para n = 100, quantas chamadas a malloc e quantas a free o programa executa?
    101 chamadas.

Por que somaDiagonal precisa receber n e não consegue descobri-lo sozinha a partir de m?
    Porque m é apenas um ponteiro que guarda o endereço do vetor de ponteiros (matriz). 
    A função somaDiagonal não recebe a matriz em si com todas as informações sobre ela 
    (como a dimensão), recebe apenas a cópia do endereço dessa matriz.
*/

#include <stdio.h>
#include <stdlib.h>

int **criarMatriz(int lin, int col){
    int **m;
    
    m = calloc(lin, sizeof(int *));
    if (m == NULL) return NULL;
   
    for (int i = 0; i < lin; i++) {
        m[i] = malloc(col * sizeof(int));
        if (m[i] == NULL){
            for (int k = 0; k < i; k++) {
                free(m[k]);
                m[k] = NULL;
            }

            free(m);
            m = NULL;
        }
          
    }

    return m;
}

void  destruirMatriz(int **m, int lin){

    for (int i = 0; i < lin; i++) {
        free(m[i]);
        m[i] = NULL;
    }

    free(m);
}

long  somaDiagonal(int **m, int n){
    long soma = 0;

    for (int i = 0; i < n; i++){
        soma += (long)m[i][i];
    }
    
    return soma;
}

int main(void){
    int **matriz, n;

    printf("Informe a dimensao da matriz: ");
    scanf("%d", &n);
    matriz = criarMatriz(n, n);
    if (matriz == NULL){
        printf("Nao foi possivel alocar a matriz.");
        return 1;
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            matriz[i][j] = i * n + j;
        }
    }

    printf("Soma da diagonal principal: %ld\n", somaDiagonal(matriz, n));
    destruirMatriz(matriz, n);
    matriz = NULL;

    return 0;
}