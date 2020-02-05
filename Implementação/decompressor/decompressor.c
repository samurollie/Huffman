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

void the_walking_tree (FILE *compressed_file, FILE *file, tree *mytree, int trash_size) {
    unsigned char unit, current;
    tree* root = mytree;
    fscanf(file, "%c", &unit);
    for(;;) {
        if (fscanf(file, "%c", &current) == EOF) {
            for(int i = 7; i >= trash_size; i--) { // faz até o tamanho do lixo pq não é preciso percorrer o byte inteiro.
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
            break;
        } else {
            for (int i = 7; i >= 0; i--) { // vai percorrer todo o byte.
            /* Deve começar do 7 pois o byte foi preenchido da direita para esquerda,
            mas na hora de ser utilizado, usa-se da esqueda para direita. */
                if (is_leaf_temp(mytree)) {
                    fprintf (compressed_file, "%c", mytree->item);
                    mytree = root; // voltam a arvore do começo.
                    i++;
                } else if (is_bit_i_set(unit, i) == 0){ // deve ir para esquerda.
                    mytree = mytree->left;
                } else {
                    mytree = mytree->right;
                }
            }
        }
        unit = current;
    }
    fprintf (compressed_file, "%c", mytree->item); // para printar o ultimo item.
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

    unsigned char byte1, byte2; // byte1 = tamanho do lixo // byte2 = tamanho da arvore. 
    int trash_size = 0, tree_size = 0;
    fscanf(arq, "%c%c", &byte1, &byte2);
    for(int i = 0; i < 16; i++) {
        if (i < 8) {
            int n = (is_bit_i_set(byte1, 7 - i) != 0) ? 1 : 0; // se o bit estiver setado, n = 1;
            // printf ("n = %d, i = %d\n", n, 7 - i);
            if (i < 3) { // apenas os 3 primeiros bites do primeiro byte são destinados ao lixo.
                trash_size += pow(2, 2 - i) * n; // transforma de binario para decimal.
            } else { // os outros 5 do primeiro byte e o segundo byte inteiro são para p tamanho da arvore.
                tree_size += pow(2, 15 - i) * n;
                /*Deve-se fazer 15-i pois na hora de transformar de binario para decimal as posições 
                são numeradas ao contrario, logo, o correto dos indices é: 0 1 2  12 11 10 9... */
            }
        } else {
            int n = (is_bit_i_set(byte2, 15 - i) != 0) ? 1 : 0;
            // printf ("n2 = %d, i = %d\n", n, 15 - i);
            tree_size += pow(2, 15 - i) * n;
        }
    }
    printf ("Tamanho do lixo: %d Tamanho da arvore: %d\n", trash_size, tree_size);
    
    printf("Arvore: ");
    tree *huff_tree = NULL;
    huff_tree  = create_tree_from_file(arq, huff_tree);

    print_tree_again(huff_tree);
    printf("\n"); 

    char original_file[strlen(file_path)]; // serve para retornar ao nome original do arquivo, ou seja, retirar o .huff.
    for (int x = 0; x < strlen(file_path); x++) {
        original_file[x] = file_path[x];
    }
    original_file[strlen(file_path) - 5] = '\0';
    printf ("arquivo original: %s\n", original_file);
    
    FILE *original = fopen(original_file, "w");
    if (original == NULL) {
        printf("Não foi possível descompactar o arquivo.\n");
        return;
    }

    the_walking_tree(original, arq, huff_tree, trash_size); // percorre a árvore printando o texto original.
    fclose(original);
    fclose(arq);
    return;
}