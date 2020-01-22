HEADERS := hash/hash.h queue/queue.h huff_tree/huff_tree.h files/files.h
SRC := hash/hash.c queue/queue.c huff_tree/huff_tree.c files/files.c

compile:
	gcc $(HEADERS) $(SRC) test/compressao.c -o huffman -lm

test:
	gcc $(HEADERS) $(SRC) test/test.c -o tests -lm -lcunit
