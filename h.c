#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arq;
    arq = fopen("a.JPG", "r");
    fseek(arq, 0, SEEK_END);
    /* A função fseek percorre todo o arq até o final (seek_end) partindo
    de um contador que se inicia como ZERO. */
    long tam = ftell(arq); 
    /* ftell informa a posição atual do ponteiro interno, como a função fseek
    vai até o final do arquivo, quando acabar, o ponteiro estará
    apontando para a ultima posição do arquivo, ou seja, o ponteiro estará
    representando o tamanho do arquivo. */ 
    printf("O tamanho do arquivo é: %ld bytes.\n", tam);
    fclose(arq); // fecha o arquivo.
    return 0;
}