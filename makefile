HEADERS := hash/hash.h queue/queue.h huff_tree/huff_tree.h files/files.h compressor/compressor.h decompressor/decompressor.h
SRC := hash/hash.c queue/queue.c huff_tree/huff_tree.c files/files.c compressor/compressor.c decompressor/decompressor.c

huff:
	gcc $(HEADERS) $(SRC) main.c -o huffman -lm

test:
	gcc $(HEADERS) $(SRC) test/test.c -o tests -lm -lcunit
