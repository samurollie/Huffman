#include "queue.h"

void print_queue (node *head) {
    node* aux = head;
    while(aux != NULL){
        printf("%c -> %d, ", aux->item, aux->frequency);
        aux = aux -> next;
    }
    printf ("\n");
}

node *dequeue(queue *queue) {
    if (queue->size <= 0) { // Se a fila está vazia
        return NULL;
    } else {
        node* aux = queue->head;
        queue->head = queue->head->next;
        aux->next = NULL;
        queue->size--;
        return aux;
    }
}

void enqueue(queue* queue, node* new_node) {
    if(queue->size == 0 || new_node->frequency < queue->head->frequency) {
        new_node->next = queue->head;
        queue->head = new_node;
    } else {
        node* aux = queue->head;
        while (aux->next != NULL && aux->next->frequency < new_node->frequency) {
            aux = aux->next;
        }
        new_node->next = aux->next;
        aux->next = new_node;
    }
    queue->size++;
}

queue *add (queue *queue, unsigned char item, lli frequency) {
    node *new_node = (node*) malloc(sizeof(node));
    new_node -> item = item; 
    new_node -> frequency = frequency;
    new_node -> right = NULL;
    new_node -> left = NULL;
    enqueue(queue, new_node);
    return queue;
}

queue* create_queue() {
    queue *new_queue = (queue*) malloc(sizeof(queue));
    new_queue->head = NULL;
    new_queue->size = 0;
    return new_queue;
}