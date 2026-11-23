#include <stdio.h>
#include <stdlib.h>
#include "PilhaDupla.h"

/* qtd_1:        quantos elementos estao na pilha 1.
   qtd_2:        quantos elementos estao na pilha 2.
   capacidade: tamanho do vetor dados, escolhido em cria_Pilha.
   dados:      vetor alocado com malloc em cria_Pilha.

   A base da pilha 1 e dados[0] e o topo e dados[qtd_1 - 1]. A proxima insercao 
   grava em dados[qtd_1], que e a primeira posicao livre. A base da pilha 2 e 
   dados[capacidade - 1] e o topo e dados[capacidade - qtd_2]. A proxima insercao 
   grava em dados[capacidade - 1 - qtd_2], que e a primeira posicao livre. */
struct pilha_dupla {
    int qtd_1;
    int qtd_2;
    int capacidade;
    struct aluno *dados;
};

/* ------------------------------------------------------------
   Criacao e destruicao
   ------------------------------------------------------------ */

PilhaDupla* cria_PilhaDupla(int capacidade){
    PilhaDupla *pd;
    if (capacidade <= 0)
        return NULL;
    pd = (PilhaDupla*) malloc(sizeof(struct pilha_dupla));      /* 1a alocacao */
    if (pd == NULL)
        return NULL;
    pd->dados = (struct aluno*) malloc(capacidade * sizeof(struct aluno));
    if (pd->dados == NULL) {            /* 2a alocacao falhou */
        free(pd);       /* sem este free, a struct ficaria perdida */
        return NULL;
    }
    pd->capacidade = capacidade;
    pd->qtd_1 = 0;
    pd->qtd_2 = 0;
    return pd;
}

void libera_PilhaDupla(PilhaDupla* pd){
    if (pd == NULL)
        return;
    free(pd->dados);    /* primeiro o vetor: pd ainda e valido aqui */
    free(pd);           /* depois a estrutura que guardava o vetor */
}

/* ------------------------------------------------------------
   Informacoes de estado
   ------------------------------------------------------------ */

int  tamanho_PilhaDupla(PilhaDupla* pd, int p){
    if (pd == NULL)
        return -1;
    
    if (p == 1)
        return pd->qtd_1;
    else if (p == 2)
        return pd->qtd_2;
    else
        return -1;      /* parametro invalido */
}

int  PilhaDupla_cheia(PilhaDupla* pd){
    if (pd == NULL)
        return -1;
    return (pd->qtd_1 + pd->qtd_2 == pd->capacidade);
}

/* ------------------------------------------------------------
   Operacoes da pilha
   ------------------------------------------------------------ */

int  insere_PilhaDupla(PilhaDupla* pd, int p, struct aluno al){
    if (pd == NULL)
        return 0;
    if (PilhaDupla_cheia(pd))               /* teste de estouro */
        return 0;
    
    if (p == 1){
        pd->dados[pd->qtd_1] = al;
        pd->qtd_1++;
        return 1;
    } else if (p == 2) {
        pd->dados[pd->capacidade - 1 - pd->qtd_2] = al;
        pd->qtd_2++;
        return 1;
    } else
        return 0;      /* parametro invalido */
}

int  remove_PilhaDupla(PilhaDupla* pd, int p){
    if (pd == NULL)
        return 0;

    if (p == 1 && pd->qtd_1 != 0){
        pd->qtd_1--;
        return 1;
    } else if (p == 2 && pd->qtd_2 != 0) {
        pd->qtd_2--;
        return 1;
    } else
        return 0;      /* parametro invalido */
}

int  consulta_topo_PilhaDupla(PilhaDupla* pd, int p, struct aluno *al){
    if (pd == NULL || al == NULL)
        return 0;
    
    if (p == 1 && pd->qtd_1 != 0){
        *al = pd->dados[pd->qtd_1 - 1];         /* topo 1: ultima posicao ocupada */
        return 1;
    } else if (p == 2 && pd->qtd_2 != 0) {
        *al = pd->dados[pd->capacidade - pd->qtd_2];         /* topo 2: ultima posicao ocupada */
        return 1;
    } else
        return 0;      /* parametro invalido */
}
