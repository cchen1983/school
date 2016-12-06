all: pi pi_pthread prime_pairs

pi: pi.c
	gcc -fopenmp pi.c -o pi

pi_pthread: pi_pthread.c
	gcc -lpthread pi_pthread.c -o pi_pthread

prime_pairs: prime_pairs.c
	gcc -fopenmp -lm prime_pairs.c -o prime_pairs

clean:
	rm -rf pi prime_pairs pi_pthread
