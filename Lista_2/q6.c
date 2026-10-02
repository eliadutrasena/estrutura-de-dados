/*
Quantos bytes exatamente a função pede ao malloc para as duas strings do exemplo, e por que
esse número não é a soma dos dois strlen?
    A função pede 19 bytes, o que é diferente da soma dos strlen (que dá 18 bytes) por causa
    do caractere nulo "\0" que é obrigatório ao final de toda cadeia de char.

O que acontece se você esquecer o byte extra e ainda assim imprimir a string com printf("%s")?
    A função ainda vai tentar escrever o caractere nulo mesmo sem espaço, o que resulta em um
    comportamento indefinido.

Dentro da função, sizeof(a) devolve qual número? Por que ele não tem relação nenhuma com o
tamanho do texto?
    Devolve 8, pois "a" é um ponteiro e a função sizeof() retorna o número de bytes do tipo do
    dado. Esse número não tem relação com o tamanho do texto por ser apenas uma informação
    sobre o tipo ponteiro.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenar(const char *a, const char *b){
    size_t tam_a, tam_b, tam_total;

    tam_a = strlen(a);
    tam_b = strlen(b);
    tam_total = tam_a + tam_b + 1;

    char *string = malloc(tam_total * sizeof(char));
    if (string == NULL) return NULL;

    strcpy(string, a);
    strcat(string, b);
    
    return string;
}
 
int main(void) {
    char *t = concatenar("Estrutura de ", "Dados");

    if (t != NULL){
        printf("String: %s \n", t);
        printf("strlen: %zu \n", strlen(t));

        free(t);
        t = NULL;
    }
    
    return 0;
}
