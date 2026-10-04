#include <stdlib.h>
#include <string.h>
#include "ListaTarefas.h"

struct elemento{
    struct tarefa dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

ListaTarefas* cria_lista(void){
    ListaTarefas* li = (ListaTarefas*) malloc(sizeof(ListaTarefas));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(ListaTarefas* li){
    if (li != NULL){
        Elem* no;
        while ((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int tamanho_lista(ListaTarefas* li){
    if (li == NULL)
        return 0;
    
    int cont = 0;
    Elem* no = *li;
    while (no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_vazia(ListaTarefas* li){
    if (li == NULL)
        return 1;
    if (*li == NULL)
        return 1;
    return 0;
}

int lista_cheia(ListaTarefas* li){
    (void) li;   // parâmetro não utilizado
    return 0;
}

int insere_tarefa_inicio(ListaTarefas* li, struct tarefa t){
    if (li == NULL) return 0;

    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = t;
    no->prox = (*li);
    *li = no;
    return 1;
}

int insere_tarefa_final(ListaTarefas* li, struct tarefa t){
    if (li == NULL) return 0;

    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = t;
    no->prox = NULL;

    if ((*li) == NULL){   // lista vazia: insere início
        *li = no;
    }
    else {
        Elem* aux = *li;
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int insere_tarefa_ordenada(ListaTarefas* li, struct tarefa t){
    if (li == NULL) return 0;

    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = t;

    if ((*li) == NULL){   // lista vazia: insere início
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else {
        Elem *ant = NULL, *atual = *li;
        while (atual != NULL && atual->dados.codigo < t.codigo){
            ant = atual;
            atual = atual->prox;
        }
        if (atual == *li){   // insere início
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_tarefa_inicio(ListaTarefas* li){
    if (li == NULL) return 0;
    if ((*li) == NULL)   // lista vazia
        return 0;
    
    Elem *no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_tarefa_final(ListaTarefas* li){
    if (li == NULL) return 0;
    if ((*li) == NULL)   // lista vazia
        return 0;
    
    Elem *ant = NULL, *no = *li;
    while (no->prox != NULL){
        ant = no;
        no = no->prox;
    }
    if (no == (*li))     // único elemento
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int remove_tarefa(ListaTarefas* li, int codigo){
    if (li == NULL) return 0;
    if ((*li) == NULL)   // lista vazia
        return 0;
    
    Elem *ant = NULL, *no = *li;
    while (no != NULL && no->dados.codigo != codigo){
        ant = no;
        no = no->prox;
    }
    if (no == NULL)      // chave ausente
        return 0;
    if (no == *li)       // remove o primeiro
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int busca_tarefa_pos(ListaTarefas* li, int pos, struct tarefa *t){
    if (li == NULL || pos <= 0)
        return 0;

    Elem *no = *li;
    int i = 1;
    while (no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if (no == NULL)
        return 0;
    else {
        *t = no->dados;
        return 1;
    }
}

int busca_tarefa_cod(ListaTarefas* li, int codigo, struct tarefa *t){
    if (li == NULL)
        return 0;
    
    Elem *no = *li;
    while (no != NULL && no->dados.codigo != codigo){
        no = no->prox;
    }
    if (no == NULL)
        return 0;
    else {
        *t = no->dados;
        return 1;
    }
}

/* Protótipos abaixo */

// Questão 1
int conta_tarefas_prioridade(ListaTarefas* li, int prioridade){
    if (li == NULL)
        return -1;
    
    int cont = 0;
    Elem* no = *li;
    while (no != NULL){
        if (no->dados.prioridade == prioridade)
            cont++;
        no = no->prox;
    }
    return cont;
}

// Questão 2
int tarefa_mais_urgente(ListaTarefas* li, struct tarefa *t){
    if (li == NULL) return 0;
    if ((*li) == NULL)   // lista vazia
        return 0;
    
    Elem *aux = *li;
    Elem *no = aux->prox;
    while (no != NULL && aux->dados.prioridade != 1){   // 1 já é a maior prioridade possível
        if (no->dados.prioridade < aux->dados.prioridade)
            aux = no;
        no = no->prox;
    }
    *t = aux->dados;
    return 1;
}

// Questão 3
int busca_tarefa_desc(ListaTarefas* li, char *texto, struct tarefa *t){
    if (li == NULL)
        return 0;
    
    Elem *no = *li;
    while (no != NULL && strstr(no->dados.descricao, texto) == NULL){
        no = no->prox;
    }
    if (no == NULL)   // não encontrado
        return 0;
    else {
        *t = no->dados;
        return 1;
    }
}

// Questão 4
int insere_tarefa_final_prioridade(ListaTarefas* li, struct tarefa t){
    if (li == NULL)
        return 0;
    
    Elem* novo = (Elem*) malloc(sizeof(Elem));
    if (novo == NULL) return 0;
    novo->dados = t;

    Elem *aux = NULL, *ant = NULL, *no = *li;
    while (no != NULL){
        if (no->dados.prioridade == t.prioridade)
            aux = no;
        ant = no;
        no = no->prox;
    }

    if (aux == NULL){   // insere no final da lista
        novo->prox = NULL;
        if ((*li) == NULL)   // lista vazia
            *li = novo;
        else
            ant->prox = novo;
    } else {   // insere após a última de mesma prioridade
        novo->prox = aux->prox;
        aux->prox = novo;
    }
    return 1;
}

// Questão 5
int remove_tarefas_prioridade(ListaTarefas* li, int prioridade){
    if (li == NULL) 
        return -1;
    
    Elem *ant = NULL, *no = *li;
    int cont = 0;
    while (no != NULL){
        if (no->dados.prioridade == prioridade){
            if (no == *li){       // remove o primeiro
                *li = no->prox;
                free(no);
                no = *li;
            } else {       // remove no meio ou final
                ant->prox = no->prox;
                free(no);
                no = ant->prox;
            }
            cont++;
        } else {
            ant = no;
            no = no->prox;
        }
    }
    return cont;
}

// Questão 6
int inverte_lista(ListaTarefas* li){
    if (li == NULL) return 0;
    if ((*li) == NULL || (*li)->prox == NULL)   // lista vazia ou unitária
        return 1;
    
    Elem *ant = NULL, *no = *li, *post = no->prox;
    no->prox = NULL;
    while (post != NULL){
        ant = no;
        no = post;
        post = post->prox;
        no->prox = ant;
    }
    *li = no;
    return 1;
}

// Questão 7
int remove_tarefa_pos(ListaTarefas* li, int pos){
    if (li == NULL || (*li) == NULL || pos <= 0)   // lista vazia, lista ou posição inválidas
        return 0;
    
    Elem *ant = NULL, *no = *li;
    int i = 1;
    while (no != NULL && i < pos){
        ant = no;
        no = no->prox;
        i++;
    }
    if (no == NULL)   // posição inválida
        return 0;
    else {
        if (pos == 1){
            *li = no->prox;
            free(no);
        } else {
            ant->prox = no->prox;
            free(no);
        }
        return 1;
    }  
}

// Questão 8
int mescla_tarefas(ListaTarefas* dst, ListaTarefas* src){
    if (dst == NULL || src == NULL)
        return -1;
    
    if ((*src) == NULL)   // lista src vazia
        return 0;
    
    int cont = 0;
    Elem *no = *src;
    while (no != NULL) {
        cont++;
        no = no->prox;
    }
    if ((*dst) == NULL){   // lista dst vazia
        *dst = *src;
    } else {
        Elem* aux = *dst;
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = *src;
    }
    *src = NULL;
    return cont;
}