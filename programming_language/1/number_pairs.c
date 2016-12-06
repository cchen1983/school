#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define RAND_IN_RANGE(min, max) \
    (min + rand() / (RAND_MAX / (max - min + 1) + 1))

#define ARRAY_LENGTH 30


static void initialize(int *pdata, int size){
    int i;

    printf("Random data: \n");
    for (i = 0; i < size; i++) {
        pdata[i] = RAND_IN_RANGE(0, 100);
        printf("%5d  ", pdata[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

/*check duplication in history*/
static char is_fetched(int *pdata, int last, int num) {
    int i;
    for (i = 0; i <= last; i++) {
        if (pdata[i] == num) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    int data[ARRAY_LENGTH] = {0};
    int i, j;
    int tgt = atoi(argv[1]);
    int proc[ARRAY_LENGTH] = {0};
    int p = 0;

    srand(time(NULL));
    initialize(data, ARRAY_LENGTH);
    printf("\nTarget number: %d\n\nMatched pairs:\n", tgt);
    
    for (i = 0; i < ARRAY_LENGTH - 1; i++) {
        if (i > 0 && is_fetched(data, i - 1, data[i])) {
            continue;
        }

        p = 0;
        for (j = i + 1; j < ARRAY_LENGTH; j++) {
            if (is_fetched(data, i - 1, data[j])) {
                continue;
            }
            else {
                /*check duplication in this loop*/
                int k;
                for (k = 0; k < p; k++) {
                    if (proc[k] == data[j]) {
                        break;
                    }
                }
                if (k < p) {
                    continue;
                }
            }

            if (data[i] + data[j] == tgt) {
                printf("[%d], [%d] : %d, %d\n", i, j, data[i], data[j]);
                proc[p++] = data[j];
            }
        }
    }
    printf("pairs end.\n");
    return 0; 
}
