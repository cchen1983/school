#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MODE 1  // 0: Sequential, 1: Parallel
#define threads 8

#define RANGE 50000000
//#define RANGE 20

static double exec_time() {
    double value;
#if 0//(MODE == SEQ)
    value = (double) clock () / (double) CLOCKS_PER_SEC;
#else
    value = omp_get_wtime();
#endif
    return value;
}

static char prime_marker[RANGE + 1];

static char is_prime(unsigned int n) {
    int opt = sqrt(n) + 1;
    int i;

    if (prime_marker[n] != -1) {
        return prime_marker[n];
    }

    for (i = 2; i <= opt; i++) {
        if ((n % i) == 0) {
            prime_marker[n] == 0;  //non-prime
            return 0;
        }
    }
    prime_marker[n] = 1;
    return 1;    
}

int main(int argc, char **argv) {
    unsigned int i, cnt = 0;
    double t;
    int cnts[threads];

    memset(cnts, 0, sizeof(cnts));    
    memset(prime_marker, 0xff, sizeof(prime_marker));

    t = exec_time();    

#if (MODE == 0)

    for (i = 2; i <= RANGE - 2; i++) {
        if (is_prime(i) && is_prime(i + 2)) {
            cnt++;
        }
    }

#else

    #pragma omp parallel reduction(+:cnt) num_threads(threads)
    {
        int i, id = omp_get_thread_num();
        for (i = 2 + id; i <= RANGE - 2; i += threads) {
            if (is_prime(i) && is_prime(i + 2)) {
                //cnts[id]++;
                cnt++;
            }
        }    
    }        

    /*for (i = 0; i < threads; i++) {
        cnt += cnts[i];
    }*/
#endif

    printf("Execution time: %f sec.\n", exec_time() - t);
    #if (MODE != 0) 
    printf("Numb of omp threads: %d\n", threads);
    #endif
    printf("There are %u prime pairs in range %u.\n", cnt, RANGE);
    return 0;    
}
