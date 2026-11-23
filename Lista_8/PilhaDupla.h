#ifndef PILHA_DUPLA_H
#define PILHA_DUPLA_H

#ifndef STRUCT_ALUNO_DEFINIDA
#define STRUCT_ALUNO_DEFINIDA

/* Tipo do elemento armazenado na pilha. */
struct aluno {
    int   matricula;
    char  nome[30];
    float n1, n2, n3;
};

#endif

/* Tipo opaco: o usuario da biblioteca so pode declarar Pilha *pi. */
typedef struct pilha_dupla PilhaDupla;

/* --- criacao e destruicao ---------------------------------- */

PilhaDupla* cria_PilhaDupla(int capacidade);

void libera_PilhaDupla(PilhaDupla* pd);

/* --- informacoes de estado --------------------------------- */

int  tamanho_PilhaDupla(PilhaDupla* pd, int p);

int  PilhaDupla_cheia(PilhaDupla* pd);

/* --- operacoes da pilha ------------------------------------ */

int  insere_PilhaDupla(PilhaDupla* pd, int p, struct aluno al);

int  remove_PilhaDupla(PilhaDupla* pd, int p);

int  consulta_topo_PilhaDupla(PilhaDupla* pd, int p, struct aluno *al);

#endif /* PILHA_DUPLA_H */