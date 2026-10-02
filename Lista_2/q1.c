/*
Por que void destruirAluno(Aluno *a) não conseguiria zerar o ponteiro do chamador?
    Porque nesse caso a função recebe apenas uma cópia do endereço guardado no ponteiro 
    (o endereço da struct). É possível manipular a struct e liberar a memória, pois tanto
    o ponteiro original como a cópia apontam pro mesmo endereço, mas tentar zerar o
    ponteiro dentro da função zera apenas a cópia.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int   matricula;
    char  nome[32];
    float media;
} Aluno;
 
Aluno *criarAluno(int matricula, const char *nome, float media){

    Aluno *a = malloc(sizeof(Aluno));
    if (a == NULL) return NULL;

    a->matricula = matricula;
    strcpy(a->nome, nome);
    a->media = media;

    return a;
}

void   imprimirAluno(const Aluno *a){

    printf("Matricula: %d | Nome: %s | Media: %.1f \n", a->matricula, a->nome, a->media);
}

void   destruirAluno(Aluno **pa){
    Aluno *a = *pa;

    free(a);
    *pa = NULL;
}

int main(void){
    Aluno *aluno;

    aluno = criarAluno(18717, "Elia", 9.5);
    if (aluno == NULL){
        printf("Nao foi possivel registrar o aluno.");
        return 1;
    }

    imprimirAluno(aluno);
    destruirAluno(&aluno);

    printf("Ponteiro = %p \n", aluno);

    return 0;
}