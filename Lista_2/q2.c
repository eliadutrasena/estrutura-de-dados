/*
Por que este programa não poderia ser escrito com um vetor local dentro de uma função que
devolvesse o endereço dele?
    Porque assim que a função termina de ser executada a memória é liberada e o vetor local 
    deixa de existir. O endereço retornado não serve mais, pois armazena lixo.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void){
    int num;
    float *notas, soma = 0.0, maior = 0.0;

    printf("Quantas notas serao inseridas? \n");
    scanf("%d", &num);
    notas = malloc(sizeof(float) * num);

    for (int i = 0; i < num; i++){
        printf("Digite a nota %d: \n", i+1);
        scanf("%f", &notas[i]);

        soma += notas[i];
        if (notas[i] > maior){
            maior = notas[i];
        }
    }

    printf("Media das notas = %.1f\n", soma/num);
    printf("Maior nota = %.1f\n", maior);

    free(notas);
    notas = NULL;

    return 0;
}