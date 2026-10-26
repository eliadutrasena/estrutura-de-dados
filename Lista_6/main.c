#include <stdio.h>
#include "ListaDinEncadCirc.h"

static struct aluno cria_aluno(int matricula, float n1, float n2, float n3) {
    struct aluno a;
    a.matricula = matricula;
    a.n1 = n1; a.n2 = n2; a.n3 = n3;
    return a;
}

static void titulo(const char *t) {
    printf("\n%s\n", t);
}

int main(void){
    Lista *li, *li1, *li2, *li_o;
    struct aluno a;
    int maior_mat, aprovados, sobrevivente;

    li = cria_lista();
    insere_lista_ordenada(li, cria_aluno(40, 3, 5, 10));
    insere_lista_ordenada(li, cria_aluno(12, 6, 8, 8));
    insere_lista_ordenada(li, cria_aluno(16, 5, 6, 8));
    insere_lista_ordenada(li, cria_aluno(23, 8, 6, 7));

    li1 = cria_lista();
    insere_lista_final(li1, cria_aluno(1, 5, 5, 5));
    insere_lista_final(li1, cria_aluno(2, 8, 8, 8));

    li2 = cria_lista();
    insere_lista_final(li2, cria_aluno(3, 7, 7, 7));
    insere_lista_final(li2, cria_aluno(4, 1, 1, 1));

    titulo("Questao 1");
    printf("Lista: ");
    imprime_lista(li);

    titulo("Questao 2");
    maior_matricula(li, &maior_mat);
    printf("Maior matricula: %d \n", maior_mat);

    titulo("Questao 3");
    aprovados = conta_aprovados(li);
    printf("Numero de alunos aprovados: %d \n", aprovados);

    titulo("Questao 4");
    busca_ciclica(li, 1, &a);
    printf("k = 1  ->  %d \n", a.matricula);
    busca_ciclica(li, 4, &a);
    printf("k = 4  ->  %d \n", a.matricula);
    busca_ciclica(li, 5, &a);
    printf("k = 5  ->  %d \n", a.matricula);
    busca_ciclica(li, 7, &a);
    printf("k = 7  ->  %d \n", a.matricula);

    titulo("Questao 5");
    remove_lista_pos(li, 2);
    printf("Lista: ");
    imprime_lista(li);
    remove_lista_pos(li, 1);
    printf("Lista: ");
    imprime_lista(li);

    insere_lista_ordenada(li, cria_aluno(12, 6, 8, 8));
    insere_lista_ordenada(li, cria_aluno(16, 5, 6, 8));

    titulo("Questao 6");
    rotaciona_lista(li, 1);
    printf("Lista: ");
    imprime_lista(li);
    rotaciona_lista(li, 4);
    printf("Lista: ");
    imprime_lista(li);

    titulo("Questao 7");
    concatena_listas(li1, li2);
    printf("Lista 1: ");
    imprime_lista(li1);

    insere_lista_final(li2, cria_aluno(1, 7, 7, 7));
    insere_lista_final(li2, cria_aluno(2, 7, 7, 7));
    insere_lista_final(li2, cria_aluno(3, 7, 7, 7));
    insere_lista_final(li2, cria_aluno(4, 7, 7, 7));
    insere_lista_final(li2, cria_aluno(5, 7, 7, 7));
    insere_lista_final(li2, cria_aluno(6, 7, 7, 7));
    insere_lista_final(li2, cria_aluno(7, 7, 7, 7));

    titulo("Questao 8");
    josephus(li2, 3, &sobrevivente);
    printf("Sobrevivente: %d \n", sobrevivente);


    titulo("Desafio");
    li_o = cria_lista();
    insere_lista_inicio_otim(li_o, cria_aluno(5, 7, 7, 7));
    printf("Lista (ins. inicio): "); 
    imprime_lista_otim(li_o);
    insere_lista_inicio_otim(li_o, cria_aluno(10, 7, 7, 7));
    printf("Lista (ins. inicio): "); 
    imprime_lista_otim(li_o);
    insere_lista_inicio_otim(li_o, cria_aluno(45, 7, 7, 7));
    printf("Lista (ins. inicio): "); 
    imprime_lista_otim(li_o);
    insere_lista_inicio_otim(li_o, cria_aluno(12, 7, 7, 7));
    printf("Lista (ins. inicio): "); 
    imprime_lista_otim(li_o);
    insere_lista_inicio_otim(li_o, cria_aluno(34, 7, 7, 7));
    printf("Lista (ins. inicio): "); 
    imprime_lista_otim(li_o);
    insere_lista_final_otim(li_o, cria_aluno(76, 7, 7, 7));
    printf("Lista (ins. final): "); 
    imprime_lista_otim(li_o);
    insere_lista_final_otim(li_o, cria_aluno(19, 7, 7, 7));
    printf("Lista (ins. final): "); 
    imprime_lista_otim(li_o);
    insere_lista_final_otim(li_o, cria_aluno(11, 7, 7, 7));
    printf("Lista (ins. final): "); 
    imprime_lista_otim(li_o);
    insere_lista_final_otim(li_o, cria_aluno(42, 7, 7, 7));
    printf("Lista (ins. final): "); 
    imprime_lista_otim(li_o);
    insere_lista_final_otim(li_o, cria_aluno(50, 7, 7, 7));
    printf("Lista (ins. final): "); 
    imprime_lista_otim(li_o);

    return 0;
}