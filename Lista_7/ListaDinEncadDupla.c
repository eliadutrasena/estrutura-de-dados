#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"

/* Definicao do tipo lista: oculta de quem usa a biblioteca. */
struct elemento {
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

/* --- criacao e destruicao ---------------------------------- */

Lista* cria_lista(void) {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li) {
    if (li != NULL) {
        Elem* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;   /* avanca antes de liberar */
            free(no);
        }
        free(li);                /* libera o bloco do inicio */
    }
}

/* --- informacoes de estado --------------------------------- */

int tamanho_lista(Lista* li) {
    if (li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while (no != NULL) {
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li) {
    (void) li;               /* parametro mantido por simetria com as demais */
    return 0;
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return 1;            /* lista invalida */
    if (*li == NULL)
        return 1;            /* nenhum elemento alocado */
    return 0;
}

/* --- insercao ---------------------------------------------- */

int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;    /* sem memoria: a lista esta cheia */
    no->dados = al;
    no->prox = (*li);
    no->ant = NULL;
    if (*li != NULL)             /* lista nao vazia */
        (*li)->ant = no;         /* o antigo primeiro ganha antecessor */
    *li = no;
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    no->prox = NULL;
    if ((*li) == NULL) {         /* lista vazia: insere inicio */
        no->ant = NULL;
        *li = no;
    } else {
        Elem* aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    if ((*li) == NULL) {         /* lista vazia: insere inicio */
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
        return 1;
    }
    else {
        /* O livro declara ante sem valor inicial. A inicializacao com
           NULL nao altera o comportamento e elimina o aviso
           "may be used uninitialized" do gcc com -O2. */
        Elem *ante = NULL, *atual = *li;
        while (atual != NULL &&
               atual->dados.matricula < al.matricula) {
            ante = atual;
            atual = atual->prox;
        }
        if (atual == *li) {      /* insere inicio */
            no->ant = NULL;
            (*li)->ant = no;
            no->prox = (*li);
            *li = no;
        } else {                 /* insere no meio ou no final */
            no->prox = ante->prox;
            no->ant = ante;
            ante->prox = no;
            if (atual != NULL)   /* nao e o ultimo */
                atual->ant = no;
        }
        return 1;
    }
}

/* --- remocao ----------------------------------------------- */

int remove_lista_inicio(Lista* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    *li = no->prox;
    if (no->prox != NULL)          /* existe um seguinte */
        no->prox->ant = NULL;      /* ele passa a ser o primeiro */
    free(no);
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    while (no->prox != NULL)
        no = no->prox;
    if (no->ant == NULL)           /* primeiro e unico */
        *li = no->prox;
    else
        no->ant->prox = NULL;      /* penultimo obtido pelo proprio no */
    free(no);
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if (no == NULL)                /* chave ausente */
        return 0;
    if (no->ant == NULL)           /* remove o primeiro */
        *li = no->prox;
    else
        no->ant->prox = no->prox;
    if (no->prox != NULL)          /* nao e o ultimo */
        no->prox->ant = no->ant;
    free(no);
    return 1;
}

/* --- busca ------------------------------------------------- */

int busca_lista_pos(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while (no != NULL && i < pos) {
        no = no->prox;
        i++;
    }
    if (no == NULL)
        return 0;
    else {
        *al = no->dados;
        return 1;
    }
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al) {
    if (li == NULL)
        return 0;
    Elem *no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if (no == NULL)
        return 0;
    else {
        *al = no->dados;
        return 1;
    }
}

/* --- Prototipos da lista ----------------------------------- */

// Questão 1
/*
A função tem custo de aproximadamente 2n e por isso é O(N), pois é preciso percorrer a lista por
completo 2 vezes.
*/
void imprime_lista_inversa(Lista* li){
    if (li == NULL || (*li) == NULL){
        printf("Lista vazia\n");
        return;
    }

    Elem *no = *li;
    while (no->prox != NULL) // no para no último elemento
        no = no->prox;
    do {
        printf("%d ", no->dados.matricula);
        no = no->ant;
    } while (no != NULL);

    printf("\n");
}

// Questão 2
int lista_consistente(Lista* li){
    if (li == NULL) return 0;
    if ((*li) == NULL) return 1;

    Elem *no = *li;
    if (no->ant != NULL) return 0;
    while (no->prox != NULL){
        if (no->prox->ant != no) return 0;
        no = no->prox;
    }
    return 1;
}

// Questão 3
/*
int remove_lista(Lista* li, int mat){
    if(li == NULL) return 0;
    if((*li) == NULL) return 0;
    Elem* no = *li;
    while(no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if(no == NULL) return 0;
    no->ant->prox = no->prox;
    free(no);
    return 1;
}

A) Descreva o que ocorre na chamada remove_lista(li, 33) sobre a lista 33 ⇄ 23 ⇄ 16.

    A função gera uma falha de segmentação ao tentar religar os ponteiros, pois tenta acessar o
    campo próximo do "elemento" no->ant, que nesse caso aponta pra NULL já que a matrícula
    desejada se encontra na primeira posição da lista. Além disso, após a liberação *li continua 
    apontando pro elemento removido, que agora é lixo.

B) Partindo novamente de 33 ⇄ 23 ⇄ 16, desenhe a lista após remove_lista(li, 23), indicando os 
campos ant e prox de cada nó restante. Explique por que tamanho_lista devolve o valor esperado e 
por que lista_consistente (questão 2) devolve 0.
    
    NULL ← [33] → [16] → NULL       33->prox aponta pra 16
              [✕] ↩                16->ant aponta pra lixo pois a religação não foi feita

    tamanho_lista percorre usando apenas os ponteiros prox, que estão corretos, mas 
    lista_consistente falha quando "no" aponta para 33 e (no->prox->ant != no).

C) Reescreva a função corrigida.
*/
int remove_lista_corr(Lista* li, int mat){
    if(li == NULL) return 0;
    if((*li) == NULL) return 0;
    Elem* no = *li;
    while(no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if(no == NULL) return 0;

    if (no == (*li)){   // se for o primeiro elemento
        no->prox->ant = NULL;
        *li = no->prox;
    } else if (no->prox == NULL){   // se for o último
        no->ant->prox = NULL;
    } else {    // se for um intermediário
        no->ant->prox = no->prox;
        no->prox->ant = no->ant;
    }
    free(no);
    return 1;
}

// Questão 4
/*
A função tem custo O(N) pela necessidade de percorrer a lista buscando a posição a ser removida,
que no pior caso é o último elemento.
*/
int remove_lista_pos(Lista* li, int pos){
    if (li == NULL || (*li) == NULL || pos <= 0) 
        return 0;
    
    Elem* no = *li;
    int i = 1;
    while (no != NULL && i < pos) {
        no = no->prox;
        i++;
    }
    if (no == NULL)
        return 0;
    else {
        if (no == (*li)){   // se for o primeiro elemento
            no->prox->ant = NULL;
            *li = no->prox;
        } else if (no->prox == NULL){   // se for o último
            no->ant->prox = NULL;
        } else {    // se for um intermediário
            no->ant->prox = no->prox;
            no->prox->ant = no->ant;
        }
    }
    free(no);
    return 1;
}

// Questão 5
/*
Quantos campos de ponteiro são escritos quando o elemento está no meio da lista? 
    6 campos
E quando é o último?
    5 campos
*/
int move_para_inicio(Lista* li, int mat){
    if (li == NULL || (*li) == NULL)
        return 0;
    
    Elem* no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if (no == NULL) return 0;
    if (no == (*li)) return 1;   // se for o primeiro elemento
    if (no->prox == NULL){   // se for o último
        no->ant->prox = NULL;
        no->ant = NULL;
        no->prox = *li;
        (*li)->ant = no;
        *li = no;
    } else {    // se for um intermediário
        no->ant->prox = no->prox;
        no->prox->ant = no->ant;
        no->ant = NULL;
        no->prox = *li;
        (*li)->ant = no;
        *li = no;
    }
    return 1;
}

// Questão 6
int remove_todos(Lista* li, int mat){
    if (li == NULL || (*li) == NULL)
        return 0;
    
    int cont = 0;
    Elem *no = *li, *aux = NULL;
    while (no != NULL){
        aux = no->prox;
        if (no->dados.matricula == mat){
            if (no == (*li)){
                if (aux != NULL){
                    no->prox->ant = NULL;
                    *li = no->prox;
                } else{
                    *li = NULL;
                }
            } else if (aux == NULL){
                no->ant->prox = NULL;
            } else {
                no->ant->prox = no->prox;
                no->prox->ant = no->ant;
            }
            free(no);
            cont++;
        }
        no = aux;
    }
    return cont;
}

// Questão 7
/*
Justifique por que, em uma lista duplamente encadeada, trocar os campos ant e prox de cada nó e 
atualizar o início é suficiente. 
    Porque simplesmente inverte o sentido que percorremos a lista, além de ajustar as extremidades,
    incluindo o novo início.
Indique o custo da função.
    É O(N), pois precisa obrigatoriamente percorrer a lista até o último elemento.
*/
void inverte_lista(Lista* li){
    if (li == NULL || (*li) == NULL || (*li)->prox == NULL)
        return;
    
    Elem *no = *li, *aux = NULL;
    while (no != NULL){
        aux = no->prox;
        no->prox = no->ant;
        no->ant = aux;
        if (aux == NULL)
            *li = no;
        no = aux;
    }
}

// Questão 8
/*
Indique o custo da função e explique por que a mesma estratégia não se aplica diretamente à lista 
encadeada simples.
    O custo é O(N) a a estratégia não se aplica à lista encadeada simples por causa da ausência do
    ponteiro ant, impossibilitando percorrer a lista do fim para o início comparando os elementos.
*/
int eh_palindromo(Lista* li){
    if (li == NULL) return 0;
    if ((*li) == NULL || (*li)->prox == NULL) 
        return 1;
    
    Elem *pri = *li, *ult = *li;
    while (ult->prox != NULL)
        ult = ult->prox;

    int tam = tamanho_lista(li);
    for (int i = 0; i < (tam / 2); i++){
        if (pri->dados.matricula != ult->dados.matricula)
            return 0;
        pri = pri->prox;
        ult = ult->ant;
    }
    return 1;
}

/* --- Desafio: Lista circular duplamente encadeada ---------- */
/*
As funcoes abaixo consideram que o prox do último aponta para o primeiro e o ant do primeiro 
aponta para o último. Mantendo *li como o endereço do primeiro elemento, o último passa a ser 
(*li)->ant.

Nessa representação, todas essas funções são O(1), diferente da lista circular encadeada simples, 
em que todas são O(N).
*/

/* --- insercao ---------------------------------------------- */

int insere_lista_inicio_circ(Lista* li, struct aluno al){
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;           /* sem memoria: a lista esta cheia */
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia: o no aponta para si mesmo */
        *li = no;
        no->prox = no;
        no->ant = no;
    } else {
        no->prox = *li;
        no->ant = (*li)->ant;
        (*li)->ant->prox = no;
        (*li)->ant = no;
        *li = no;           /* unica linha que difere da insercao no final */
    }
    return 1;
}

int insere_lista_final_circ(Lista* li, struct aluno al){
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia: o no aponta para si mesmo */
        *li = no;
        no->prox = no;
        no->ant = no;
    } else {
        no->prox = *li;
        no->ant = (*li)->ant;
        (*li)->ant->prox = no;
        (*li)->ant = no;     /* o inicio nao muda */
    }
    return 1;
}

/* --- remocao ----------------------------------------------- */

int remove_lista_inicio_circ(Lista* li){
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    if ((*li) == (*li)->prox) {   /* elemento unico: a lista fica vazia */
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *no = *li;
    no->ant->prox = no->prox;       /* o ultimo passa a apontar para o segundo */
    no->prox->ant = no->ant;       /* o segundo passa a apontar para o ultimo */
    *li = no->prox;               /* o segundo passa a ser o inicio */
    free(no);
    return 1;
}

int remove_lista_final_circ(Lista* li){
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    if ((*li) == (*li)->prox) {   /* elemento unico: a lista fica vazia */
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *no = (*li)->ant;
    no->ant->prox = no->prox;       /* o penultimo passa a apontar para o primeiro */
    no->prox->ant = no->ant;       /* o primeiro passa a apontar para o penultimo */
    free(no);
    return 1;
}

/* --- impressao (para testes) ------------------------------- */
void imprime_lista_circ(Lista* li){
    if (li == NULL || (*li) == NULL)
        return;

    Elem *no = *li;
    do {                    /* do-while: o primeiro elemento tem de ser impresso */
        printf("%d ", no->dados.matricula);
        no = no->prox;
    } while (no != (*li));

    printf("\n");
}