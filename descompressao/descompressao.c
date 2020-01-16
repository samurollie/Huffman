#include "../list/list.h"
#include "../files/files.h"
#include "../huff_tree/huff_tree.h"
#include <string.h>
#include <math.h>

typedef struct tree tree;
struct tree {
    unsigned char item;
    tree *left;
    tree * right;
};

void print_tree_again(tree* tree) {
    if (tree == NULL) return;
    printf ("%c", tree->item);
    print_tree_again(tree->left);
    print_tree_again(tree->right);
}

int is_leaf_temp (tree *tree) {
    return (tree->left == NULL && tree->right == NULL);
}

void the_walking_tree (FILE *compressed_file, FILE *file, tree *mytree, int trash_size) {
    unsigned char unit, temp;
    tree* root = mytree;
    // printf("aq\n");
    fscanf(file, "%c", &unit);
    for(;;) {
        if (fscanf(file, "%c", &temp) == EOF) {
            // printf("%c : ", unit);
            
            for(int i = 7; i >= trash_size; i--) {
                // printf("%d", (is_bit_i_set(unit, i) == 0) ? 0 : 1);
                if (is_leaf_temp(mytree)) {
                    // printf("%c\n", mytree->item);
                    
                    fprintf (compressed_file, "%c", mytree->item);
                    mytree = root;
                    i++;
                } else if (is_bit_i_set(unit, i) == 0){
                    mytree = mytree->left;
                    // printf("esquerda\n");
                } else {
                    mytree = mytree->right;
                    // printf("direita\n");
                }
            }
            
            // printf("\n");
            break;
        } else {
            // printf("%c : ", unit);
            for (int i = 7; i >= 0; i--) {
                // printf("%d", (is_bit_i_set(unit, i) == 0) ? 0 : 1);
                if (is_leaf_temp(mytree)) {
                    // printf("%c\n", mytree->item);
                    fprintf (compressed_file, "%c", mytree->item);
                    mytree = root;
                    i++;
                } else if (is_bit_i_set(unit, i) == 0){
                    mytree = mytree->left;
                    // printf("esquerda\n");
                } else {
                    mytree = mytree->right;
                    // printf("direita\n");
                }
            }
            // printf("\n");
        }
        unit = temp;
    }
    fprintf (compressed_file, "%c", mytree->item);
}

tree* create_child (unsigned char item, tree* left, tree* right) {
    tree* new_tree = (tree*) malloc(sizeof(tree));
    new_tree->item = item;
    new_tree->left = left;
    new_tree->right = right;
    return new_tree;
}

tree* create_tree_from_file(FILE* file, tree* tree) {
    unsigned char unit;
    fscanf (file, "%c", &unit);
    if (unit != '*') {
        if (unit == '\\') {
            fscanf (file, "%c", &unit);
        }
        tree = create_child(unit, NULL, NULL);
    } else {
        tree = create_child(unit, NULL, NULL);
        tree->left = create_tree_from_file(file, tree->left);
        tree->right = create_tree_from_file(file, tree->right);
    }
    return tree;
}

int main () {
    printf("Insira o caminho para o arquivo que deseja descompactar: ");
    char file_path[5000];
    scanf ("%[^\n]s", file_path);
    FILE *arq = open_file(file_path);   
    if (arq == NULL) {
        printf("Arquivo nao encontrado!\n");
        return 0;
    }

    unsigned char byte1, byte2;
    int trash_size = 0, tree_size = 0;
    fscanf(arq, "%c%c", &byte1, &byte2);
    for(int i = 0; i < 16; i++) {
        if (i < 8) {
            int n = (is_bit_i_set(byte1, 7 - i) != 0) ? 1 : 0;
            printf ("n = %d, i = %d\n", n, 7 - i);
            if (i < 3) {
                trash_size += pow(2, i) * n;
            } else {
                tree_size += pow(2, 15 - i) * n;
            }
        } else {
            int n = (is_bit_i_set(byte2, 15 - i) != 0) ? 1 : 0;
            printf ("n2 = %d, i = %d\n", n, 15 - i);
            tree_size += pow(2, 15 - i) * n;
        }
    }
    printf ("Tamanho do lixo: %d Tamanho da arvore: %d\n", trash_size, tree_size);
    
    tree *huff_tree = NULL;
    huff_tree  = create_tree_from_file(arq, huff_tree);

    print_tree_again(huff_tree);
    printf("\n"); 

    char original_file[strlen(file_path)];
    for (int x = 0; x < strlen(file_path); x++) {
        original_file[x] = file_path[x];
    }
    original_file[strlen(file_path) - 5] = '\0';
    printf ("arquivo original: %s\n", original_file);
    
    FILE *original = fopen(original_file, "w");
    if (original == NULL) {
        printf("ai\n");
    }

    the_walking_tree(original, arq, huff_tree, trash_size);
    return 0;
}