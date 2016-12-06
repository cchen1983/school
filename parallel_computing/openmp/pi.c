#include <stdio.h>
#include <omp.h>
#include <time.h>

#define SEQ 1
#define SPMD 2
#define SHARE 3

#define MODE SHARE
#define threads 32

static double exec_time() {
    double value;
#if 0//(MODE == SEQ)
    value = (double) clock () / (double) CLOCKS_PER_SEC;
#else
    value = omp_get_wtime();
#endif
    return value;
}

int main(int argc, char **argv) {

    int i, per_steps;
    long steps = atol(argv[1]);
    double step, pi = 0.0;
    double sums[threads] = {0};
    double t;
    double x, sum;

    step = (double)1.0 / (double)steps;
    t = exec_time();


#if (MODE == SEQ)
    printf("Sequential Mode\n");
    for (i = 1; i <= steps; i++) {
        x = (i - 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    pi = step * sum;

#elif (MODE == SPMD) 
    printf("SPMD MODE\n");
    #pragma omp parallel reduction(+:sum) num_threads(threads)
    {
        int i, id = omp_get_thread_num();
        double x;
        for (i = id; i <= steps; i += threads) {
            x = (i - 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
    }
    
    pi = sum * step;

#elif (MODE == SHARE)
    printf("WORKING SHARE MODE\n");
    #pragma omp parallel reduction(+:sum) num_threads(threads)
    {
        double x;
        int i, id = omp_get_thread_num();
        #pragma omp for //schedule(dynamic)
        for(i = 1; i <= steps; i++) {
            x = (i - 0.5) * step;
            sum += 4.0 / (1.0 + x * x); 
        }
    }
    
    pi = sum * step;
#endif

    t = exec_time() - t;
#if (MODE != SEQ)
    printf("omp threads: %d\n", threads);
#endif
    printf("iter: %lu pi: %f\n", steps, pi);
    printf("Excution time: %f\n", t);
    return 0;
}
