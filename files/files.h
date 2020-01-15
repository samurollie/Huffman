#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <stdlib.h>

FILE *open_file(char* path);
unsigned char set_bit(unsigned char c, int i);
int is_bit_i_set(unsigned char c, int i);

#endif