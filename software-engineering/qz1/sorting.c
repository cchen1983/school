#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define DEBUG

#ifdef DEBUG
#define log(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define dump(...) __dump(__VA_ARGS__)
#else
#define log(fmt, ...)
#define dump(...)
#endif


#define RAND_IN_RANGE(min, max) \
    (min + rand() / (RAND_MAX / (max - min + 1) + 1))

#define ARRAY_LENGTH 8
#define DATA_MIN 0
#define DATA_MAX 100

static int data[ARRAY_LENGTH] = {85,24,63,45,17,31,96,50};

static void initialize(int *pdata, int size){
    int i;

    log("Random data: \n");
    for (i = 0; i < size; i++) {
        pdata[i] = RAND_IN_RANGE(DATA_MIN, DATA_MAX);
        log("%5d  ", pdata[i]);
        if ((i + 1) % 10 == 0) {
            log("\n");
        }
    }
    log("\n");
}

static void __dump(int *pdata, int size){
    int i;
    for (i = 0; i < size; i++) {
        log("%5d  ", pdata[i]);
        if ((i + 1) % 10 == 0) {
            log("\n");
        }
    }
    log("\n");
}

/*
* quick sort
*/
static inline int partition(int *pdata, int left, int right, int pivot){
    int tmp;
    while (left < right) {
        if (pivot <= pdata[right]) {
            right--;
            continue;
        }
        else {
            tmp = pdata[left];
            pdata[left] = pdata[right];
            pdata[right] = tmp;
            left++;
        }
        
        while (left < right) {
            if (pivot >= pdata[left]) {
                left++;
                continue;
            }
            else {
                tmp = pdata[right];
                pdata[right] = pdata[left];
                pdata[left] = tmp;
                right--;
                break;
            }
        }
    }
    
    return left;
}

static void __quick_sort(int *pdata, int left, int right){
    int pivot;
    int sep;

    if (left >= right) {
        return;
    }

    pivot = pdata[left];
    sep = partition(pdata, left, right, pivot);
    dump(data, ARRAY_LENGTH);
    __quick_sort(pdata, left, sep - 1);
    __quick_sort(pdata, sep + 1, right);
}

static void quick_sort(int *pdata, int size){
    int left = 0;
    int right = size - 1;
    log("<%s>\n", __FUNCTION__);
    __quick_sort(pdata, left, right);
}


int main(int argc, char **argv){
    srand(time(NULL));

    //initialize(data, ARRAY_LENGTH);
    quick_sort(data, ARRAY_LENGTH);
    dump(data, ARRAY_LENGTH);

    return 0;    
}
