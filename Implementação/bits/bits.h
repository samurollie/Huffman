#ifndef BITS_H
#define BITS_H

#include <stdio.h>
#include <stdlib.h>

/** @param c: o bit a ser setado*/
/** @param i: a posição do bit que deve ser setada*/
/** @return retorna o bit setado na poição i*/
unsigned char set_bit(unsigned char c, int i);

/** @param c: o bit para verificação*/
/** @param i: a posição a ser verificada*/
/** @return retorna se o bit está setado na posição i ou não*/
int is_bit_i_set(unsigned short c, int i);

#endif
