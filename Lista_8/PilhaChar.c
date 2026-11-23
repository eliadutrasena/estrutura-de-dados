#include <stdio.h>
#include <stdlib.h>
#include "PilhaChar.h"

/* qtd:        quantos elementos estao na pilha.
   capacidade: tamanho do vetor dados, escolhido em cria_Pilha.
   dados:      vetor alocado com malloc em cria_Pilha.

   A base da pilha e dados[0] e o topo e dados[qtd - 1]. A proxima
   insercao grava em dados[qtd], que e a primeira posicao livre.
   Assim, empilhar e desempilhar nunca deslocam elementos: e a
   insercao e a remocao no final da lista sequencial estatica. */
struct pilha_char {
    int qtd;
    int capacidade;
    char *dados;    // struct aluno -> char
};

/* ------------------------------------------------------------
   Criacao e destruicao
   ------------------------------------------------------------ */

PilhaChar* cria_Pilha_char(int capacidade) {
    PilhaChar *pi;
    if (capacidade <= 0)
        return NULL;
    pi = (PilhaChar*) malloc(sizeof(struct pilha_char));          /* 1a alocacao */
    if (pi == NULL)
        return NULL;
    pi->dados = (char*) malloc(capacidade * sizeof(char));      // struct aluno -> char
    if (pi->dados == NULL) {                             /* 2a alocacao falhou */
        free(pi);       /* sem este free, a struct ficaria perdida */
        return NULL;
    }
    pi->capacidade = capacidade;
    pi->qtd = 0;
    return pi;
}

void libera_Pilha_char(PilhaChar* pi) {
    if (pi == NULL)
        return;
    free(pi->dados);    /* primeiro o vetor: pi ainda e valido aqui */
    free(pi);           /* depois a estrutura que guardava o vetor */
}

/* ------------------------------------------------------------
   Informacoes de estado
   ------------------------------------------------------------ */

int tamanho_Pilha_char(PilhaChar* pi) {
    if (pi == NULL)
        return -1;
    return pi->qtd;
}

int Pilha_cheia_char(PilhaChar* pi) {
    if (pi == NULL)
        return -1;
    return (pi->qtd == pi->capacidade);  /* no livro: qtd == MAX */
}

int Pilha_vazia_char(PilhaChar* pi) {
    if (pi == NULL)
        return -1;
    return (pi->qtd == 0);
}

/* ------------------------------------------------------------
   Operacoes da pilha (sempre no topo)
   ------------------------------------------------------------ */

int insere_Pilha_char(PilhaChar* pi, char ch) {      // struct aluno al -> char ch
    if (pi == NULL)
        return 0;
    if (Pilha_cheia_char(pi))                  /* teste de estouro */
        return 0;
    pi->dados[pi->qtd] = ch;    // al -> ch     /* qtd e a primeira posicao livre */
    pi->qtd++;                            /* o novo elemento passa a ser o topo */
    return 1;
}

int remove_Pilha_char(PilhaChar* pi) {
    if (pi == NULL || Pilha_vazia_char(pi))
        return 0;
    pi->qtd--;          /* o topo desce uma posicao; nada e apagado */
    return 1;
}

int consulta_topo_Pilha_char(PilhaChar* pi, char *ch) {      // struct aluno *al -> char *ch
    if (pi == NULL || ch == NULL || Pilha_vazia_char(pi))    // al -> ch 
        return 0;
    *ch = pi->dados[pi->qtd - 1];   // *al -> *ch         /* topo: ultima posicao ocupada */
    return 1;
}
