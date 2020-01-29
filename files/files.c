#include "files.h"

FILE *open_file(char* path) {
    FILE *f = fopen(path, "rb");
    return f;
}

unsigned char set_bit(unsigned char c, int i) { // essa função transforma o zero em um.
    unsigned char mask = 1 << i;	
    return mask | c;
}

int is_bit_i_set(unsigned short c, int i) { // verifica se o int i é igual a um.
    unsigned char mask = 1 << i;
    return mask & c;
}
