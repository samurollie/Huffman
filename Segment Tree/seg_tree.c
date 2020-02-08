#include <stdio.h>
#include <stdlib.h>

typedef struct seg_tree SEG_TREE;

struct seg_tree
{
    int left, right;
    //filhos da direita e esquerda
    SEG_TREE* pointer_left, pointer_right;
    //soma daquele intervalo
    int sum;
};

SEG_TREE* create_empty_segtree()
{
    return NULL;
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


int main()
{
    return 0;
}