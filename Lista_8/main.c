#include <stdio.h>
#include <string.h>
#include "FilaEstatica.h"
#include "PilhaSequencial.h"
#include "PilhaChar.h"
#include "PilhaDupla.h"

static struct aluno mk(int matricula) {
    struct aluno al;
    al.matricula = matricula;
    return al;
}

// Questão 3
int josefo(int n, int k){
    if (n < 1 || k < 1)
        return -1;
    
    Fila *fi = cria_Fila(n);
    if (fi == NULL) return 0;
    for (int i = 1; i <= n; i++){
        insere_Fila(fi, mk(i));
    }

    struct aluno al;
    while(tamanho_Fila(fi) > 1){
        for (int j = 1; j < k; j++){
            consulta_Fila(fi, &al);
            remove_Fila(fi);
            insere_Fila(fi, al);
        }
        consulta_Fila(fi, &al);
        printf("Saiu: %d\n", al.matricula);
        remove_Fila(fi);
    }

    consulta_Fila(fi, &al);
    libera_Fila(fi);
    return al.matricula;
}

// Questão 4c
int sequencia_valida(const char *s){
    if (s == NULL) return 0;
    int pilha = 0, tam = strlen(s);
    for (int i = 0; i < tam; i++){
        switch (s[i]){
        case 'I':
            pilha++;
            break;
        case 'R':
            if (pilha == 0) return 0;
            pilha--;
            break;
        default:
            break;
        }
    }
    if (pilha != 0) return 0;

    return 1;
}

// Questão 5b
int verifica_delimitadores(const char *expr){
    if (expr == NULL) return 0;
    int tam = strlen(expr);
    PilhaChar *pi = cria_Pilha_char(tam);
    if (pi == NULL){
        printf("Nao foi possivel verificar\n");
        return 0;
    }
    
    char ch;
    for (int i = 0; i < tam; i++){
        switch (expr[i]){
            case '(':
                insere_Pilha_char(pi, expr[i]);
                break;
            case '[':
                insere_Pilha_char(pi, expr[i]);
                break;
            case '{':
                insere_Pilha_char(pi, expr[i]);
                break;
            case ')':
                if (Pilha_vazia_char(pi)){
                    libera_Pilha_char(pi);
                    return 0;
                }
                consulta_topo_Pilha_char(pi, &ch);
                if (ch == '('){
                    remove_Pilha_char(pi);
                } else {
                    libera_Pilha_char(pi);
                    return 0;
                }
                break;
            case ']':
                if (Pilha_vazia_char(pi)){
                    libera_Pilha_char(pi);
                    return 0;
                }
                consulta_topo_Pilha_char(pi, &ch);
                if (ch == '['){
                    remove_Pilha_char(pi);
                } else {
                    libera_Pilha_char(pi);
                    return 0;
                }
                break;
            case '}':
                if (Pilha_vazia_char(pi)){
                    libera_Pilha_char(pi);
                    return 0;
                }
                consulta_topo_Pilha_char(pi, &ch);
                if (ch == '{'){
                    remove_Pilha_char(pi);
                } else {
                    libera_Pilha_char(pi);
                    return 0;
                }
                break;
            default:
                break;
        }
    }
    if (!Pilha_vazia_char(pi)){
        libera_Pilha_char(pi);
        return 0;
    }

    libera_Pilha_char(pi);
    return 1;
}


int main(void){
    struct aluno al;

    // Questão 2
    Fila *fi = cria_Fila(2);
    printf("Testando fura_Fila(), da questao 2:\n");
    printf("Sequencia de insercao: 10, 20, 30 (capacidade da fila = 2)\n");

    printf("Fila vazia: %d\n", fura_Fila(fi, mk(10)));
    consulta_Fila(fi, &al);
    printf("Consulta inicio: %d\n", al.matricula);

    printf("Inicio valendo 0: %d\n", fura_Fila(fi, mk(20)));
    consulta_Fila(fi, &al);
    printf("Consulta inicio: %d\n", al.matricula);

    printf("Fila cheia: %d\n", fura_Fila(fi, mk(30)));
    libera_Fila(fi);

    printf("\n");

    // Questão 3
    printf("Testando josefo(), da questao 3:\n");
    printf("(n, k) = (7, 3):\n");
    printf("Sobrevivente: %d\n", josefo(7, 3)); printf("\n");
    printf("(n, k) = (5, 2):\n");
    printf("Sobrevivente: %d\n", josefo(5, 2)); printf("\n");
    printf("(n, k) = (1, 4):\n");
    printf("Sobrevivente: %d\n", josefo(1, 4)); printf("\n");
    printf("(n, k) = (6, 1):\n");
    printf("Sobrevivente: %d\n", josefo(6, 1));

    printf("\n");

    // Questão 4
    printf("Testando sequencia_valida(), da questao 4: \n1. IRIIRR \n2. IRRI\n");
    printf("Valida: %d\n", sequencia_valida("IRIIRR"));
    printf("Valida: %d\n", sequencia_valida("IRRI"));

    printf("\n");

    // Questao 5
    printf("Testando verifica_delimitadores(), da questao 5:\n");
    printf("1. (()) \n2. ()() \n3. {a[b(c)d]e} \n4. )( \n5. (()( \n6. ([)]\n");
    printf("Correto: %d\n", verifica_delimitadores("(())"));
    printf("Correto: %d\n", verifica_delimitadores("()()"));
    printf("Correto: %d\n", verifica_delimitadores("{a[b(c)d]e}"));
    printf("Correto: %d\n", verifica_delimitadores(")("));
    printf("Correto: %d\n", verifica_delimitadores("(()("));
    printf("Correto: %d\n", verifica_delimitadores("([)]"));

    return 0;
}