#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadCirc.h"

/* Definicao do tipo lista: oculta de quem usa a biblioteca. */
struct elemento {
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
    if (li == NULL)
        return;
    if ((*li) != NULL) {
        Elem *aux, *no = *li;
        /* para quando o seguinte ao atual e o inicio: uma volta completa */
        while ((*li) != no->prox) {
            aux = no;
            no = no->prox;   /* avanca antes de liberar */
            free(aux);
        }
        free(no);
    }
    free(li);               /* libera o bloco do inicio */
}

/* --- informacoes de estado --------------------------------- */

int tamanho_lista(Lista* li) {
    if (li == NULL || (*li) == NULL)
        return 0;
    int cont = 0;
    Elem *no = *li;
    do {                    /* do-while: o primeiro elemento tem de ser contado */
        cont++;
        no = no->prox;
    } while (no != (*li));
    return cont;
}

int lista_cheia(Lista* li) {
    (void) li;              /* parametro mantido por simetria com as demais */
    return 0;
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return 1;           /* lista invalida */
    if (*li == NULL)
        return 1;           /* nenhum elemento alocado */
    return 0;
}

/* --- insercao ---------------------------------------------- */

int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;           /* sem memoria: a lista esta cheia */
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia: o no aponta para si mesmo */
        *li = no;
        no->prox = no;
    } else {
        Elem *aux = *li;
        while (aux->prox != (*li)) {   /* procura o ultimo */
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *li;
        *li = no;           /* unica linha que difere da insercao no final */
    }
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia: o no aponta para si mesmo */
        *li = no;
        no->prox = no;
    } else {
        Elem *aux = *li;
        while (aux->prox != (*li)) {   /* procura o ultimo */
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *li;     /* o inicio nao muda */
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia */
        *li = no;
        no->prox = no;
        return 1;
    }
    if ((*li)->dados.matricula > al.matricula) {   /* insercao no inicio */
        Elem *atual = *li;
        while (atual->prox != (*li))               /* procura o ultimo */
            atual = atual->prox;
        no->prox = *li;
        atual->prox = no;
        *li = no;
        return 1;
    }
    /* insercao no meio ou no final: ant acompanha atual uma posicao atras */
    Elem *ant = *li, *atual = (*li)->prox;
    while (atual != (*li) && atual->dados.matricula < al.matricula) {
        ant = atual;
        atual = atual->prox;
    }
    ant->prox = no;
    no->prox = atual;
    return 1;
}

/* --- remocao ----------------------------------------------- */

int remove_lista_inicio(Lista* li) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    if ((*li) == (*li)->prox) {   /* elemento unico: a lista fica vazia */
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *atual = *li;
    while (atual->prox != (*li))  /* procura o ultimo */
        atual = atual->prox;
    Elem *no = *li;
    atual->prox = no->prox;       /* o ultimo passa a apontar para o segundo */
    *li = no->prox;               /* o segundo passa a ser o inicio */
    free(no);
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    if ((*li) == (*li)->prox) {   /* elemento unico: a lista fica vazia */
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *ant = NULL, *no = *li;
    while (no->prox != (*li)) {   /* procura o ultimo, guardando o anterior */
        ant = no;
        no = no->prox;
    }
    ant->prox = no->prox;         /* o penultimo passa a apontar para o inicio */
    free(no);
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    Elem *no = *li;
    if (no->dados.matricula == mat) {      /* remocao do inicio */
        if (no == no->prox) {              /* a lista fica vazia */
            free(no);
            *li = NULL;
            return 1;
        } else {
            Elem *ult = *li;
            while (ult->prox != (*li))     /* procura o ultimo */
                ult = ult->prox;
            ult->prox = (*li)->prox;
            *li = (*li)->prox;
            free(no);
            return 1;
        }
    }
    Elem *ant = no;
    no = no->prox;
    /* para ao encontrar a matricula ou ao completar uma volta */
    while (no != (*li) && no->dados.matricula != mat) {
        ant = no;
        no = no->prox;
    }
    if (no == (*li))
        return 0;           /* chave ausente */
    ant->prox = no->prox;
    free(no);
    return 1;
}

/* --- busca ------------------------------------------------- */

int busca_lista_pos(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || (*li) == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    /* para no ultimo elemento ou ao alcancar a posicao desejada */
    while (no->prox != (*li) && i < pos) {
        no = no->prox;
        i++;
    }
    if (i != pos)
        return 0;           /* posicao inexistente */
    else {
        *al = no->dados;
        return 1;
    }
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al) {
    if (li == NULL || (*li) == NULL)
        return 0;
    Elem *no = *li;
    /* para no ultimo elemento ou ao encontrar a matricula */
    while (no->prox != (*li) && no->dados.matricula != mat)
        no = no->prox;
    if (no->dados.matricula != mat)
        return 0;           /* chave ausente */
    else {
        *al = no->dados;
        return 1;
    }
}

/* --- Prototipos da lista ----------------------------------- */

// Questão 1
void imprime_lista(Lista* li){
    if (li == NULL || (*li) == NULL)
        return;

    Elem *no = *li;
    do {                    /* do-while: o primeiro elemento tem de ser impresso */
        printf("%d ", no->dados.matricula);
        no = no->prox;
    } while (no != (*li));

    printf("\n");
}

// Questão 2
int maior_matricula(Lista* li, int *mat){
    if (li == NULL || (*li) == NULL)
        return 0;
    
    Elem *no = *li;
    *mat = (*li)->dados.matricula;
    
    while (no->prox != (*li)){
        no = no->prox;
        if (no->dados.matricula > *mat)
            *mat = no->dados.matricula;
    }
    return 1;
}

// Questão 3
/*
int conta_aprovados(Lista* li){
    int cont = 0;
    Elem *no = *li;
    while(no != NULL){
        float media = (no->dados.n1 + no->dados.n2 + no->dados.n3) / 3;
        if(media >= 7.0)
            cont++;
        no = no->prox;
    }
    return cont;
}
Erros:
    1. Se a lista for inválida ou estiver vazia a função gera falha de segmentação por tentar
    acessar campos internos do ponteiro "no" com "no" valendo NULL;
    2. Se a lista tiver pelo menos um elemento o while gera um laço infinito, pois "no" sempre
    será diferente de NULL.
*/
int conta_aprovados(Lista* li){
    if (li == NULL || (*li) == NULL)
        return 0;
    
    int cont = 0;
    Elem *no = *li;
    do {
        float media = (no->dados.n1 + no->dados.n2 + no->dados.n3) / 3;
        if(media >= 7.0)
            cont++;
        no = no->prox;
    } while (no != (*li));
    return cont;
}

// Questão 4
int busca_ciclica(Lista* li, int k, struct aluno *al){
    if (li == NULL || (*li) == NULL || k <= 0)
        return 0;
    
    int tam = tamanho_lista(li);

    Elem *no = *li;
    if (k == 1 || tam == 1){
        *al = no->dados;
    } else {
        int pos = ((k - 1) % tam) + 1;
        int i = 1;
        /* so para ao alcancar a posicao desejada */
        while (i < pos) {
            no = no->prox;
            i++;
        }
        *al = no->dados;
    }
    return 1;
}

// Questão 5
int remove_lista_pos(Lista* li, int pos){
    if (li == NULL || (*li) == NULL || pos <= 0)
        return 0;
    
    if (pos == 1){
        remove_lista_inicio(li);   /* trata remocao do primeiro e do elemento unico */
        return 1;
    }
    
    Elem *ant = NULL, *no = *li;
    int i = 1;
    /* para no ultimo elemento ou ao alcancar a posicao desejada */
    while (no->prox != (*li) && i < pos){
        ant = no;
        no = no->prox;
        i++;
    }
    if (i != pos)
        return 0;           /* posicao inexistente */
    else {
        ant->prox = no->prox;   /* remocao no meio ou no final */
        free(no);
        return 1;
    }
}

// Questão 6
/*
Pergunta 1: Qual é o custo da função, e por que ela não precisa ser O(N) para k pequeno?
    É O(N) no pior caso pela necessidade de percorrer a lista, mas se k for igual a 0 ou 1 a
    operação pode ser feita diretamente e por isso tem custo O(1).

Pergunta 2: O que seria necessário para obter o mesmo efeito em uma lista dinâmica encadeada 
não circular, e qual seria o custo?
    Seria necessário percorrer a lista até a posição k, marcando o elemento com um ponteiro, 
    continuar até o final com outro ponteiro para fazer com que o último elemento aponte para 
    o início, fazer *li (início) apontar para k + 1 (novo início) e k apontar para NULL.
    Tudo isso tem operação O(N).

*/
int rotaciona_lista(Lista* li, int k){
    if (li == NULL || (*li) == NULL || k < 0)
        return 0;
    
    if (k == 0)
        return 1;
    
    Elem *no = *li;
    for (int i = 0; i < k; i++)
        no = no->prox;
    *li = no;
    return 1;
}

// Questão 7
/*
Qual seria o custo desta mesma operação na representação que guarda o final da lista em (*li), 
apresentada no fim da aula?
    Seria constante O(1), pois já teríamos os endereços necessários sem precisar percorrer a lista.
*/
int concatena_listas(Lista* li1, Lista* li2){
    if (li1 == NULL || li2 == NULL)
        return 0;
    
    /* trata lista 1 ou 2 vazias */
    if ((*li2) == NULL)
        return 1;
    if ((*li1) == NULL){
        *li1 = *li2;
        *li2 = NULL;
        return 1;
    }
    
    Elem *no = *li1;
    while (no->prox != (*li1))
        no = no->prox;
    no->prox = *li2;

    no = *li2;
    while (no->prox != (*li2))
        no = no->prox;
    no->prox = *li1;

    *li2 = NULL;
    return 1;
}

// Questão 8
int josephus(Lista* li, int k, int *sobrevivente){
    if (li == NULL || (*li) == NULL || k < 0)
        return 0;
    
    Elem *ant = NULL, *no = *li;
    while (no != no->prox){   /* repete ate restar uma unica pessoa */
        for (int i = 1; i < k; i++){
            ant = no;
            no = no->prox;
        }
        ant->prox = no->prox;
        ant = no;
        no = no->prox;
        free(ant);
        ant = NULL;
    }
    *sobrevivente = no->dados.matricula;
    return 1;
}

/* --- Desafio de otimizacao --------------------------------- */
// As funcoes abaixo consideram que *li guarda o final da lista

/*
Pergunta: Por que a remoção do final permanece O(N) mesmo nessa representação?
    Porque ainda é necessário percorrer a lista para encontrar o penúltimo elemento, o antecessor
    do ponteiro li, para fazê-lo apontar para o início da lista e só então fazer a remoção.
*/


/* --- insercao ---------------------------------------------- */

int insere_lista_inicio_otim(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;           /* sem memoria: a lista esta cheia */
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia: o no aponta para si mesmo */
        *li = no;
        no->prox = no;
    } else {
        no->prox = (*li)->prox;
        (*li)->prox = no;
    }
    return 1;
}

int insere_lista_final_otim(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia: o no aponta para si mesmo */
        *li = no;
        no->prox = no;
    } else {
        no->prox = (*li)->prox;
        (*li)->prox = no;
        *li = no;
    }
    return 1;
}

/* --- remocao ----------------------------------------------- */

int remove_lista_inicio_otim(Lista* li) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    if ((*li) == (*li)->prox) {   /* elemento unico: a lista fica vazia */
        free(*li);
        *li = NULL;
        return 1;
    }

    Elem *no = (*li)->prox;
    (*li)->prox = no->prox;
    free(no);
    return 1;
}

/* --- outras ------------------------------------------------ */

int tamanho_lista_otim(Lista* li) {
    if (li == NULL || (*li) == NULL)
        return 0;
    int cont = 0;
    Elem *no = (*li)->prox;
    do {                    /* do-while: o primeiro elemento tem de ser contado */
        cont++;
        no = no->prox;
    } while (no != (*li)->prox);
    return cont;
}

void imprime_lista_otim(Lista* li){
    if (li == NULL || (*li) == NULL)
        return;
        
    Elem *no = (*li)->prox;
    do {                    /* do-while: o primeiro elemento tem de ser impresso */
        printf("%d ", no->dados.matricula);
        no = no->prox;
    } while (no != (*li)->prox);

    printf("\n");
}