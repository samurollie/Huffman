#include "decompressor/decompressor.h"
#include "compressor/compressor.h"

int main () {
    while (1) {
        printf("Escolha uma das seguintes opções:\n");
        printf("(1) - Comprimir\n(2) - Descomprimir\n(3) - Sair\n");
        int op;
        scanf ("%d", &op);
        getchar();
        switch (op) {
            case 1:
                compress();
                break;
            case 2:
                decompress();
                break;
            case 3:
                return 0;
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    }
}