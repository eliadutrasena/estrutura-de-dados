#include <stdlib.h>
#include <string.h>
#include "ListaProdutos.h"
 
struct lista {
    int qtd;
    struct produto dados[MAX];
};

Lista* cria_lista(){
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if (li != NULL)
        li->qtd = 0;
    return li;
}

void libera_lista(Lista* li){
    free(li);
}

int busca_lista_pos(Lista* li, int pos, struct produto *p){
    if (li == NULL || pos <= 0 || pos > li->qtd)
        return 0;
    
    *p = li->dados[pos-1];
    return 1;
}

int busca_lista_cod(Lista* li, int cod, struct produto *p){
    if (li == NULL)
        return 0;

    int i = 0;
    while (i < li->qtd && li->dados[i].codigo != cod)
        i++;
    if (i == li->qtd)  // não encontrado
        return 0;
    *p = li->dados[i];
    return 1;
}

int insere_lista_final(Lista* li, struct produto p){
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)  // lista cheia
        return 0;

    li->dados[li->qtd] = p;
    li->qtd++;
    return 1;
}

int insere_lista_inicio(Lista* li, struct produto p){
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)  // lista cheia
        return 0;
    
    for (int i = li->qtd-1; i >= 0; i--)
        li->dados[i+1] = li->dados[i];
    li->dados[0] = p;
    li->qtd++;
    return 1;
}

int insere_lista_ordenada(Lista* li, struct produto p){
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)  // lista cheia
        return 0;

    int k, i = 0;
    while (i < li->qtd && li->dados[i].codigo < p.codigo)
        i++;
    for (k = li->qtd-1; k >= i; k--)
        li->dados[k+1] = li->dados[k];
    li->dados[i] = p;
    li->qtd++;
    return 1;
}

int remove_lista(Lista* li, int cod){
    if (li == NULL)
        return 0;
    if (li->qtd == 0)  // lista vazia
        return 0;

    int k, i = 0;
    while (i < li->qtd && li->dados[i].codigo != cod)
        i++;
    if (i == li->qtd)  // não encontrado
        return 0;
    for (k = i; k < li->qtd-1; k++)
        li->dados[k] = li->dados[k+1];
    li->qtd--;
    return 1;
}

int remove_lista_otimizado(Lista* li, int cod){
    if (li == NULL)
        return 0;
    if (li->qtd == 0)  // lista vazia
        return 0;
    
    int i = 0;
    while (i < li->qtd && li->dados[i].codigo != cod)
        i++;
    if (i == li->qtd)  // não encontrado
        return 0;
    li->qtd--;
    li->dados[i] = li->dados[li->qtd];
    return 1;
}

int remove_lista_inicio(Lista* li){
    if (li == NULL)
        return 0;
    if (li->qtd == 0)  // lista vazia
        return 0;
    
    for (int k = 0; k < li->qtd-1; k++)
        li->dados[k] = li->dados[k+1];
    li->qtd--;
    return 1;
}

int remove_lista_final(Lista* li){
    if (li == NULL)
        return 0;
    if (li->qtd == 0)  // lista vazia
        return 0;
    
    li->qtd--;
    return 1;
}

int tamanho_lista(Lista* li){
    if (li == NULL)
        return -1;
    return li->qtd;
}

int lista_cheia(Lista* li){
    if (li == NULL)
        return -1;
    return (li->qtd == MAX);
}

int lista_vazia(Lista* li){
    if (li == NULL)
        return -1;
    return (li->qtd == 0);
}

/* Protótipos abaixo */

// Questão 1
int lista_tem_espaco(Lista* li, int n){
    if (li == NULL)
        return 0;
    if (MAX - (li->qtd) < n)  // lista cheia
        return 0;
    
    return 1;
}

// Questão 2
float soma_precos(Lista* li){
    if (li == NULL)
        return 0;
    
    float soma = 0.0;
    for (int i = 0; i < li->qtd; i++)
        soma += li->dados[i].preco;
    return soma;
}

// Questão 3
int busca_por_nome(Lista* li, char *nome, struct produto *p){
    if (li == NULL)
        return 0;
    
    int i = 0;
    while (i < li->qtd && strcmp(li->dados[i].nome, nome) != 0)
        i++;
    if (i == li->qtd)  // não encontrado
        return 0;
    *p = li->dados[i];
    return 1;
}

// Questão 4
int insere_lista_decrescente(Lista* li, struct produto p){
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)  // lista cheia
        return 0;

    int k, i = 0;
    while (i < li->qtd && li->dados[i].preco > p.preco)
        i++;
    for (k = li->qtd-1; k >= i; k--)
        li->dados[k+1] = li->dados[k];
    li->dados[i] = p;
    li->qtd++;
    return 1;
}

// Questão 5
int remove_mais_caro(Lista* li, struct produto *removido){
    if (li == NULL)
        return 0;
    if (li->qtd == 0)  // lista vazia
        return 0;
    
    int r = 0;
    for (int i = 1; i < li->qtd; i++){
        if (li->dados[i].preco > li->dados[r].preco)
            r = i;
    }
    *removido = li->dados[r];
    li->qtd--;
    li->dados[r] = li->dados[li->qtd];
    return 1;
}

// Questão 6
int conta_faixa_preco(Lista* li, float min, float max){
    if (li == NULL)
        return 0;
    if (li->qtd == 0)  // lista vazia
        return 0;
    
    int cont = 0;
    for (int i = 0; i < li->qtd; i++){
        if (li->dados[i].preco >= min && li->dados[i].preco <= max)
            cont++;
    }
    return cont;
}

// Questão 7
int remove_abaixo_de(Lista* li, float precoMinimo){
    if (li == NULL)
        return 0;
    if (li->qtd == 0)  // lista vazia
        return 0;
    
    int i = 0, cont = 0;
    while(i < li->qtd){
        if (li->dados[i].preco < precoMinimo){
            cont++;
            li->qtd--;
            li->dados[i] = li->dados[li->qtd];
        } else 
            i++;
    }
    return cont;
}

// Questão 8
int mescla_listas(Lista* destino, Lista* origem){
    if (destino == NULL || origem == NULL)
        return 0;
    if (destino->qtd == MAX)  // lista cheia
        return 0;
    
    int cont = 0;
    for (int i = 0; i < origem->qtd; i++){
        int j = 0;
        while (j < destino->qtd && destino->dados[j].codigo != origem->dados[i].codigo)
            j++;
        if (j == destino->qtd){  // não encontrado
            destino->dados[destino->qtd] = origem->dados[i];
            destino->qtd++;
            cont++;
        }
        if (destino->qtd == MAX)  // lista cheia
            return cont;
    }
    return cont;
}