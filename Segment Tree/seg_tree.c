#include <stdio.h>
#include <stdlib.h>

typedef struct seg_tree SEG_TREE;

struct seg_tree
{
    int left, right;
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
    if(current->left > index || current->right < index) //completamente fora
    {
        return current->sum;
    }
    else if(current->left >= index && current->right <= index) //completamente dentro
    {
        current->sum = new_value;
        return current->sum;
    }
    else //parcialmete contido
    {
        current->sum = update(current->pointer_left, index, new_value) + update(current->pointer_right, index, new_value);
        return current->sum;
    }
    
}

int query(SEG_TREE* current, int start, int end)
{
    if(current->right < start || current->left > end) //completamente fora
    {
        return 0;
    }
    else if(current->left >= start && current->right <= end) //completamente dentro
    {
        // entramos num nó  o qual os elementos que ele cobre são do interesse da consulta
        return current->sum;
    }
    else //parcialmete contido
    {
        /*
        Esse é o caso mais delicado. Se entramos em um nó que cobre apenas alguns elementos da consulta, 
        então não podemos ignorar e retornar 0, assim como não podemos retornar a soma de todos os elementos
        abaixo. O resultado é um meio termo. Chamamos recursivamente ambos os filhos do nó em questão, 
        os quais vão reagir de acordo com alguma dessas situações acima e nos dizer com precisão qual 
        a soma que buscamos.
        */
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
    printf("[%d, %d] -> %d\n", st->left, st->right, st->sum);
}

SEG_TREE* construct_segtree(int array[], int left, int right)
{
    SEG_TREE* current = (SEG_TREE*) malloc(sizeof(SEG_TREE));

    current->left = left;
    current->right = right;

    if(left == right) //no caso de ser uma folha
    {
        current->pointer_left = NULL;
        current->pointer_right = NULL;
        current->sum = array[left];
    }
    else //nó NÃO folha
    {
        int middle = (left + right) / 2;
        current->pointer_left = construct_segtree(array, left, middle);
        current->pointer_right = construct_segtree(array, middle + 1, right);
        current->sum = current->pointer_left->sum + current->pointer_right->sum;
    }

    return current;   
}

void create_segtree_from_array(SEG_TREE* st, int array[], int size)
{
    st = construct_segtree(array, 0, size - 1);
}


int main()
{
    int array[7] = {0, 1, 3, 5, 7, 9, 11};
    //1 3 5 7 9 11
    SEG_TREE* segtree = create_empty_segtree();
    int n = 7;
    //create_segtree_from_array(segtree, array, n);

    //a segtree vai começar de 1, pois segundo o jaquesom tem que fazer uma gambiarra 
    //muito grande pra começar do 0 e na maioria dos lugares comça com 1 mesmo
    segtree = construct_segtree(array, 1, n - 1);
    print_segtree(segtree);
    //printf("query = %d\n", query(segtree, 8, 8));
    update(segtree, 1, -1);
    printf("\n\n");
    print_segtree(segtree);

    return 0;
}