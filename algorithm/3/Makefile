all: dijkstra kruskal huffman knapsack bst

dijkstra: dijkstra.o
	gcc -o dijkstra dijkstra.o -I.

kruskal: kruskal.o
	gcc -o kruskal kruskal.o -I.

huffman: huffman.o
	gcc -o huffman huffman.o -I.

knapsack: knapsack.o
	gcc -o knapsack knapsack.o -I.

bst: bst.o
	gcc -o bst bst.o -I.

.PHONY: clean

clean:
	rm -rf *.o dijkstra kruskal huffman knapsack bst
