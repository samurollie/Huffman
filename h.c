#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arq; 
    arq = fopen("a.txt", "r");
    unsigned char inut;
    long long int repeticao[256] = {0};
    int i;
	while (!feof(arq)) { // vai até o EOF.
  		fscanf(arq,"%c",&inut);
        int a = (int) inut;
        // printf ("%d\n", a);
        repeticao[a] += 1;
  	}
//     for(i = 0; i < 256; i++) {
//         if(repeticao[i] != 0) {
//             printf(">>>%lld\n", repeticao[i]);
//         }
//     }
    return 0;
}