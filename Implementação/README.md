# Huffman

* Suite é basicamente uma fila;
* Em vez da posição ser numero será um nome;
* CU_add_on_queue_suite = Seria, respectivamente, a função create_queue;
* CU_add_on_queue_test = Enfileira a função criada;
* CU_ASSERT = Testa;
* CU_basic_run_tests() =  Roda os testes;
* CU_cleanup_registry() = Limpa o suite de testes quando terminar para evitar lixo de memoria.
* CUE_SUCCESS = CU_initialize_registry retorna essa  variável se ela conseguir inicializar

* É importante verificar se o teste foi realmente enfileirado:

```c
if(NULL == CU_add_on_queue_test(pSuite, "p_queue_tests", p_queue_tests)) { // se a função falha, ela retorna NULL
	CU_cleanup_registry(); // limpa os registros
	return CU_get_error(); // retorna o erro
} 
```
