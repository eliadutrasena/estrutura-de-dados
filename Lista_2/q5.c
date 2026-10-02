/*
Erros de memória:
    1. Sizeof(Aluno *) - retorna o tamanho do ponteiro (8 bytes), não o tamanho da struct
    2. Ponteiro pendurado - tenta acessar a memória de um bloco já devolvido
    3. Alocação dupla - causa vazamento de memória do bloco que foi alocado primeiro
    4. Liberação dupla - corrompe o alocador, causando futuros erros
    5. Escrita além do limite - sobrescreve em uma região de memória que não deveria ser usada

Erros acusados pelo compilador: 1, 2 e 4
Erros não acusados: 3 e 5

O compilador é uma rede de segurança suficiente?
    Não é suficiente, pois os erros que não foram percebidos também causam danos.
*/

#include <stdio.h>
#include <stdlib.h>
 
typedef struct {
    int   matricula;
    char  nome[32];
    float media;
} Aluno;
 
int main(void) {
    Aluno *a = malloc(sizeof(Aluno));
    if (a != NULL){
        a->matricula = 20260145;
        a->media = 8.7f;

        printf("%.1f\n", a->media);
        free(a);
    }

    Aluno *b = malloc(sizeof(Aluno)); 
    if (b != NULL){
        b->matricula = 20260200;
 
        free(b);
    }

    int *v = malloc(5 * sizeof(int));
    if (v != NULL){
        for (int i = 0; i < 5; i++) {
            v[i] = i * i;
        }
        free(v);
    }

    return 0;
}