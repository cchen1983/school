#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define threads 8

static long steps;
static double step;
static double sums[threads] = {0};

static void *thread_callback(void * arg) {
    long i;
    int id = *(int *)arg;
    double x;

    for (i = id; i < steps; i += threads) {
        x = (i - 0.5) * step;
        sums[id] += 4.0 / (1.0 + x * x);
    }
    
    return NULL;
}

int main(int argc, char **argv) {
    int i;
    double pi = 0.0;
    pthread_t th[threads];
    int id[threads];

    steps = atol(argv[1]);
    step = 1.0 / (double)steps;

    for (i = 0; i < threads; i++) {
        id[i] = i;
        pthread_create(&th[i], NULL, thread_callback, &id[i]);
    }

    for (i = 0; i < threads; i++) {
        pthread_join(th[i], NULL);
        pi += sums[i];
    }
    pi = pi * step;

    printf("iter count : %lu\n", steps);
    printf("pthread (%d) pi calc = %f\n", threads, pi);
    return 0;    
}
