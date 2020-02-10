#include "huff_tree.h"

int is_leaf(node *tree) {
  return !tree->left && !tree->right;
}

void print_tree (node* tree) {
	if(tree ==  NULL) {
		return;
	}
	printf("%c", tree->item);
	print_tree(tree->left);
	print_tree(tree->right);
}

void print_tree_on_file (FILE *f, node* tree) {
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
  	print_tree_on_file(f, tree->left);
  	print_tree_on_file(f, tree->right);
}

node* join(queue* queue) { 
  	node* father = NULL;
	lli frequency = queue->head->frequency + queue->head->next->frequency; // Soma a frequencia dos dois primeiros nós da queuea;
	unsigned char id = '*';
	node* left = dequeue(queue);
	node* right = dequeue(queue);

  	father = create_node(frequency, id, queue, left, right); // Adiciono tudo ao novo nó;
  	return father;
}

node* build_tree (queue *myqueue) {
	int i = 0;
	while(myqueue->size > 1) { 
		node* father = join(myqueue);
		enqueue(myqueue, father);
		i++;
	}
	node *huff_tree;
	if(i == 0) { // tratamento de erro.
		node *father = NULL;
		unsigned char id = '*';
		node* left = myqueue->head;
		node* right = NULL;
		father = create_node(myqueue->head->frequency, id, myqueue, left, right);
		huff_tree = father;
	} else {
		huff_tree = myqueue->head;
	}
	return huff_tree;
}