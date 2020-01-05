#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list/list.h"

typedef long long int lli;

lli *get_frequency(FILE *file) {
    lli *repeticao = (lli*) malloc(sizeof(lli) * 256);
    memset(repeticao, 0, 256);
    unsigned char unit;
	while (fscanf(file,"%c",&unit) != EOF) { // vai até o EOF.
		int a = (int) unit;
		repeticao[a] += 1;
  	}
    return repeticao;
}

FILE *open_file(char* path) {
    FILE *f = fopen(path, "r");
    return f;
}

int main() {
    FILE *arq; 
    arq = open_file("a.txt");
    lli *frequency = get_frequency(arq);
    
    node *head = NULL;
    int i, size_list = 0;
    for (i = 0; i < 256; i++) {
        if (frequency[i] != 0) {
            head = add(head, frequency[i]);
            size_list++;
        }
    }
    print_list(head);
    
    return 0;
}