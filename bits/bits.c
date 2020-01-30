#include "bits.h"

unsigned char set_bit(unsigned char c, int i) {
    unsigned char mask = 1 << i;	
    return mask | c;
}

int is_bit_i_set(unsigned short c, int i) {
    unsigned char mask = 1 << i;
    return mask & c;
}
