#include "decompressor.h"

void print_tree_again(tree* tree) {
    if (tree == NULL) return;
    printf ("%c", tree->item);
    print_tree_again(tree->left);
    print_tree_again(tree->right);
}

int is_leaf_temp (tree *tree) {
    return (tree->left == NULL && tree->right == NULL);
}

void print_original_file (FILE *compressed_file, FILE *file, tree *mytree, int trash_size) {
    unsigned char unit, current;
    tree* root = mytree;
    fscanf(file, "%c", &unit);
    int n;
    for(;;) {
        if (fscanf(file, "%c", &current) == EOF) {
            n = trash_size;
        } else {
            n = 0;
        }

        for (int i = 7; i >= n; i--) {
            if (is_leaf_temp(mytree)) {
                fprintf (compressed_file, "%c", mytree->item);
                mytree = root;
                i++;
            } else if (is_bit_i_set(unit, i) == 0){
                mytree = mytree->left;
            } else {
                mytree = mytree->right;
            }
        }
        
        unit = current;
        if (n == trash_size) 
            break;
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

void decompress () {
    printf("Insira o caminho para o arquivo que deseja descompactar: ");
    char file_path[5000];
    scanf ("%[^\n]s", file_path);
    FILE *arq = fopen(file_path, "rb");   
    if (arq == NULL) {
        printf("Arquivo nao encontrado!\n");
        return;
    }

    unsigned char byte1, byte2;
    int trash_size = 0, tree_size = 0;
    fscanf(arq, "%c%c", &byte1, &byte2);
    for(int i = 0; i < 16; i++) {
        if (i < 8) {
            int n = (is_bit_i_set(byte1, 7 - i) != 0) ? 1 : 0;
            if (i < 3) {
                trash_size += pow(2, 2 - i) * n;
            } else {
                tree_size += pow(2, 15 - i) * n;
            }
        } else {
            int n = (is_bit_i_set(byte2, 15 - i) != 0) ? 1 : 0;
            tree_size += pow(2, 15 - i) * n;
        }
    }
    
    tree *huff_tree = NULL;
    huff_tree  = create_tree_from_file(arq, huff_tree);

    char original_file[strlen(file_path)];
    for (int x = 0; x < strlen(file_path); x++) {
        original_file[x] = file_path[x];
    }
    original_file[strlen(file_path) - 5] = '\0';
    printf ("arquivo original: %s\n", original_file);
    
    FILE *original = fopen(original_file, "wb");
    if (original == NULL) {
        printf("Não foi possível descompactar o arquivo.\n");
        return;
    }

    print_original_file(original, arq, huff_tree, trash_size);
    fclose(original);
    fclose(arq);
    return;
}