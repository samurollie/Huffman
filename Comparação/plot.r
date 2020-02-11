graf <- read.table("C:\\Users\\Samuel\\Documents\\UFAL\\p2\\Huffman\\Comparação\\out", header=TRUE, sep=" ")
View(graf)
plot(graf$Lista~graf$Valor, main="lista x arvore", xlab="valores", ylab="comp", col="blue")
lines(graf$Arvore~graf$Valor, col="RED")
