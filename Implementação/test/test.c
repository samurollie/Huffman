#include <CUnit/CUnit.h>
#include "../hash/hash.h"
#include "../huff_tree/huff_tree.h"
#include "../queue/queue.h"

int init_suite(void) {
    return 0; 
}

int clean_suite(void) { 
    return 0; 
}

void test_hash(void) {
    hash_table *hash = create_hash_table();
    CU_ASSERT_PTR_NOT_NULL(hash);
    for (int i = 0; i < HASH_SIZE; i++) {
        CU_ASSERT_PTR_NULL(hash->table[i]);
    }

    put(hash, 'A', 6);
    put(hash, 'B', 5);
    put(hash, 'C', 4);
    put(hash, 'D', 3);
    put(hash, 'E', 2);
    put(hash, 'F', 1);

    CU_ASSERT(hash->table['A']->key == 'A');
    CU_ASSERT(hash->table['A']->frequency == 6);
    CU_ASSERT(hash->table['B']->key == 'B');
    CU_ASSERT(hash->table['B']->frequency == 5);
    CU_ASSERT(hash->table['C']->key == 'C');
    CU_ASSERT(hash->table['C']->frequency == 4);
    CU_ASSERT(hash->table['D']->key == 'D');
    CU_ASSERT(hash->table['D']->frequency == 3);
    CU_ASSERT(hash->table['E']->key == 'E');
    CU_ASSERT(hash->table['E']->frequency == 2);
    CU_ASSERT(hash->table['F']->key == 'F');
    CU_ASSERT(hash->table['F']->frequency == 1);
    CU_ASSERT(hash->table['G'] == NULL);

        
}

void test_tree(void) {
    queue *queue = create_queue();
    add(queue, 'A', 6);
    // add(queue, 'B', 5);
    // add(queue, 'C', 4);
    // add(queue, 'D', 3);
    // add(queue, 'E', 2);
    // add(queue, 'F', 1);
    // node *tree = create_node(6, 'A', queue);
    // node *tree = create_node(5, 'B', queue);
    // node *tree = create_node(4, 'C', queue);
    // node *tree = create_node(3, 'D', queue);
    // node *tree = create_node(2, 'E', queue);
    // node *tree = create_node(1, 'F', queue);
    // CU_ASSERT_PTR_NOT_NULL(tree);
}

void test_queue(void) {
    queue *queue = create_queue();
    CU_ASSERT_PTR_NOT_NULL(queue); // verifica se a queue não é NULL.
    CU_ASSERT(queue->size == 0); // verifica se o tamanho é zero.

    add(queue, 'A', 6); // nessa função criamos um nó e enfileiramos ordenadamente.
    CU_ASSERT(queue->head->item == 'A');
    add(queue, 'B', 5);
    CU_ASSERT(queue->head->item == 'B');
    add(queue, 'C', 4);
    CU_ASSERT(queue->head->item == 'C');
    add(queue, 'D', 3);
    CU_ASSERT(queue->head->item == 'D');
    add(queue, 'E', 2);
    CU_ASSERT(queue->head->item == 'E');
    add(queue, 'F', 1);
    CU_ASSERT(queue->head->item == 'F');

    CU_ASSERT(queue->head == dequeue(queue));
    CU_ASSERT(queue->head == dequeue(queue));
    CU_ASSERT(queue->head == dequeue(queue));
    CU_ASSERT(queue->head == dequeue(queue));
    CU_ASSERT(queue->head == dequeue(queue));
    CU_ASSERT(queue->head == dequeue(queue));
    CU_ASSERT(NULL == dequeue(queue));
}

int main () {
    CU_pSuite pSuite = NULL; // cria a variavel do tipo CU_pSuite.

    /* Se essa função não conseguir inicializar, retorna um erro.
    Caso consiga ela retorna a variavel CUE_SUCCESS. */
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    pSuite = CU_add_suite("Basic_Test_Suite1", init_suite, clean_suite); // cria a suite.
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Se suite fosse uma fila, poderia dizer que a função
    CU_add_test enfileira um caso de teste */
    if((CU_add_test(pSuite, "\n\nTesting Queue Functions...\n\n", test_queue) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if((CU_add_test(pSuite, "\n\nTesting Tree...\n\n", test_tree) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if((CU_add_test(pSuite, "\n\nTesting Hash...\n\n", test_hash) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

// Para compilar : make -B test
// o "-B" força a compilação.