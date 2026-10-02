/*
Por que a assinatura void dobrar(int n) não resolveria o problema?
    Porque C usa passagem por valor, ou seja, a variável da função recebe apenas uma cópia do 
    valor original e não o altera de fato. O ponteiro recebe o endereço da variável original e
    consegue modificá-lo.
*/

#include <stdio.h>

void dobrar(int *p){
    *p *= 2;
}
 
int main(void) {

    int n = 21;
    dobrar(&n);
    printf("%d\n", n);
    
    return 0;
}