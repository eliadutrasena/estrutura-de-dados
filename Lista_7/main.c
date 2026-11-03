#include <stdio.h>
#include "ListaDinEncadDupla.h"

static struct aluno cria_aluno(int matricula) {
    struct aluno a;
    a.matricula = matricula;
    return a;
}

/* Imprime a lista usando apenas a interface publica, com a notacao
   dos slides: NULL <- [33] <-> [23] -> NULL. */
static void imprime(const char *rotulo, Lista *li) {
    int i, n = tamanho_lista(li);
    struct aluno a;
    printf("  %-26s tam=%d: ", rotulo, n);
    if (n == 0) {
        printf("(vazia)\n");
        return;
    }
    printf("NULL <-");
    for (i = 1; i <= n; i++) {
        busca_lista_pos(li, i, &a);
        printf(" [%d] %s", a.matricula, i < n ? "<->" : "-> NULL");
    }
    printf("\n");
}

/* Monta uma lista com as matriculas dadas, inserindo no final. */
static Lista* monta(const int *mats, int n) {
    Lista *li = cria_lista();
    for (int i = 0; i < n; i++)
        insere_lista_final(li, cria_aluno(mats[i]));
    return li;
}

static void titulo(const char *t) {
    printf("\n%s\n", t);
}

int main(void) {
    Lista *li1, *li2, *li3, *li4, *li5, *li6, *li7, *li8, *li_circ;
    int n1, n2;

    int m1[] = {33, 23, 16};
    li1 = monta(m1, 3);

    int m2[] = {10, 20, 30, 40};
    li2 = monta(m2, 4);

    int m3[] = {7, 3, 7, 7, 5, 7};
    li3 = monta(m3, 6);

    int m4[] = {8, 8, 8, 8, 8};
    li4 = monta(m4, 5);

    int m5[] = {1, 2, 3, 4, 5};
    li5 = monta(m5, 5);

    int m6[] = {1, 2, 3, 2, 1};
    li6 = monta(m6, 5);

    int m7[] = {4, 8, 8, 4};
    li7 = monta(m7, 4);

    int m8[] = {1, 2, 2, 3};
    li8 = monta(m8, 4);

    imprime("Lista: ", li1);

    titulo("Questao 1");
    printf("Lista invertida: \n");
    imprime_lista_inversa(li1);

    titulo("Questao 2");
    printf("Consistente: %d\n", lista_consistente(li1));

    titulo("Questao 3");
    remove_lista_corr(li1, 23);
    imprime("Apos remover 23", li1);
    printf("Consistente: %d\n", lista_consistente(li1));

    titulo("Questao 4");
    remove_lista_pos(li1, 1);
    imprime("Apos remover na posicao 1", li1);
    printf("Consistente: %d\n", lista_consistente(li1));

    titulo("Questao 5");
    imprime("Lista: ", li2);
    move_para_inicio(li2, 30);
    imprime("Apos acessar 30", li2);
    printf("Consistente: %d\n", lista_consistente(li2));

    titulo("Questao 6");
    imprime("Lista: ", li3);
    n1 = remove_todos(li3, 7);
    imprime("Apos remover todos os 7", li3);
    printf("%d elementos removidos\n", n1);
    printf("Consistente: %d\n", lista_consistente(li3));

    imprime("\nLista: ", li4);
    n2 = remove_todos(li4, 8);
    imprime("Apos remover todos os 8", li4);
    printf("%d elementos removidos\n", n2);
    printf("Consistente: %d\n", lista_consistente(li4));

    titulo("Questao 7");
    imprime("Lista: ", li5);
    inverte_lista(li5);
    imprime("Apos inverter a lista", li5);
    printf("Consistente: %d\n", lista_consistente(li5));

    titulo("Questao 8");
    imprime("Lista: ", li6);
    printf("Palindromo: %d\n", eh_palindromo(li6));
    imprime("Lista: ", li7);
    printf("Palindromo: %d\n", eh_palindromo(li7));
    imprime("Lista: ", li8);
    printf("Palindromo: %d\n", eh_palindromo(li8));


    titulo("Desafio");
    li_circ = cria_lista();
    insere_lista_inicio_circ(li_circ, cria_aluno(2));
    printf("Lista (ins. inicio): ");
    imprime_lista_circ(li_circ);
    insere_lista_inicio_circ(li_circ, cria_aluno(5));
    printf("Lista (ins. inicio): ");
    imprime_lista_circ(li_circ);
    insere_lista_final_circ(li_circ, cria_aluno(7));
    printf("Lista (ins. final): ");
    imprime_lista_circ(li_circ);
    insere_lista_final_circ(li_circ, cria_aluno(10));
    printf("Lista (ins. final): ");
    imprime_lista_circ(li_circ);
    remove_lista_inicio_circ(li_circ);
    printf("Lista (rem. inicio): ");
    imprime_lista_circ(li_circ);
    remove_lista_final_circ(li_circ);
    printf("Lista (rem. final): ");
    imprime_lista_circ(li_circ);

    return 0;
}