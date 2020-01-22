// ARQUIVO : huffnode.c
#include "huff_tree.h"

int is_leaf(node *tree) {
  return !tree->left && !tree->right;
}

void print_tree (node* tree, int h) {
	if(tree ==  NULL) {
		return;
	}
	printf("Caracter: %c, frequencia: %d, altura: %d\n", tree->item, tree->frequency, h);
	print_tree(tree->left, h + 1);
	print_tree(tree->right, h + 1);
}

void print_on_file (FILE *f, node* tree) {
	if (tree == NULL) {
		return;
    }
	if (is_leaf(tree)) {
		if (tree->item == '*' || tree->item == '\\') {
  			fprintf(f, "\\%c", tree->item);
		} else {
  			fprintf(f, "%c", tree->item);
		}
	} else {
  		fprintf(f, "%c", tree->item);
	}
  	print_on_file(f, tree->left);
  	print_on_file(f, tree->right);
}

node *create_node(lli frequency, unsigned char item, queue *queue){
	node *new_node = (node*) malloc(sizeof(node));
    new_node->frequency = frequency;
    new_node->item = item;
	new_node->left = dequeue(queue);
	new_node->right = dequeue(queue);
    new_node->next = NULL;
    return new_node;
}

node* join(queue* queue) { 
  	node* father = NULL; // Cria um nó
    lli frequency = queue->head->frequency + queue->head->next->frequency; // Soma a frequencia dos dois primeiros nós da queuea;
    unsigned char id = '*'; // O item que eu devo salvar pra indicar que é um nó interno
  	father = create_node(frequency, id, queue); // Adiciono tudo ao novo nó;
  	return father;
} 

node* build_tree (queue *myqueue) {
  while(myqueue->size > 1) { 
  	node* father = join(myqueue);
    enqueue(myqueue, father);
  }
  node *huff_tree = myqueue->head;
  return huff_tree;
}