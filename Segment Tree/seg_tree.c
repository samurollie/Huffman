#include <stdio.h>
#include <stdlib.h>

typedef struct seg_tree SEG_TREE;

struct seg_tree
{
    int begin, end;
    //filhos da direita e esquerda
    SEG_TREE* pointer_left;
    SEG_TREE* pointer_right;
    //soma daquele intervalo
    int sum;
};

SEG_TREE* create_empty_segtree()
{
    return NULL;
}

int update(SEG_TREE* current, int index, int new_value) //a ideia é semelhante a query
{
    if(index < current->begin || index > current->end) // Caso eu saia do intervalo
    {
        return current->sum;
    }
    else if(index <= current->begin && index >= current->end) // Achei o intervalo que estou procurando
    {
        current->sum = new_value;
        return current->sum;
    }
    else // Continua a procura pelo indice desejado
    {
        current->sum = update(current->pointer_left, index, new_value) + update(current->pointer_right, index, new_value);
        return current->sum;
    }
    
}

int query(SEG_TREE* current, int start, int end) // função que realiza uma consulta.
{
    if(start > current->end || end < current->begin) //completamente fora : retorna um valor neutro
    {
        return 0;
    }
    else if(start <= current->begin && end >= current->end) //completamente dentro
    {
        // entramos num nó  o qual os elementos que ele cobre são do interesse da consulta
        return current->sum;
    }
    else //parcialmete contido. Tem que continuar a chamada até chegar em um intervalo totalmente incluso.
    {
        return query(current->pointer_left, start, end) + query(current->pointer_right, start, end);
    }
    
}

void print_segtree(SEG_TREE* st)
{
    if(st == NULL){
        return;
    }
    print_segtree(st->pointer_left);
    print_segtree(st->pointer_right);
    printf("[%d, %d] -> %d\n", st->begin, st->end, st->sum);
}

SEG_TREE* construct_segtree(int array[], int begin, int end)
{
    SEG_TREE* current = (SEG_TREE*) malloc(sizeof(SEG_TREE));
    printf("%d %d\n", begin, end);

    current->begin = begin;
    current->end = end;

    if(begin == end) //no caso de ser uma folha
    {
        current->pointer_left = NULL;
        current->pointer_right = NULL;
        current->sum = array[begin];
    }
    else //nó NÃO folha
    {
        int middle = (begin + end) / 2;
        current->pointer_left = construct_segtree(array, begin, middle);
        current->pointer_right = construct_segtree(array, middle + 1, end);
        current->sum = current->pointer_left->sum + current->pointer_right->sum;
    }
    return current;   
}


int main()
{
    int array[7] = {0, 1, 3, 5, 7, 9, 11};
    //1 3 5 7 9 11
    SEG_TREE* segtree = create_empty_segtree();
    int n = 7;
    segtree = construct_segtree(array, 0, n - 1);

    print_segtree(segtree);
    update(segtree, 1, -1);
    printf("\n\n");
    print_segtree(segtree);
    
    printf("query[2;5] = %d\n", query(segtree, 2, 5));
    return 0;
}