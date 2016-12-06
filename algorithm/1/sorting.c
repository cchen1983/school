/**
 * algorithm assignment 2015-02-02
 * chao chen <cchen.rough@gmail.com> 
 * Student ID: 21176927
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

//#define DEBUG

#ifdef DEBUG
#define log(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define dump(...) __dump(__VA_ARGS__)
#else
#define log(fmt, ...)
#define dump(...)
#endif


#define RAND_IN_RANGE(min, max) \
    (min + rand() / (RAND_MAX / (max - min + 1) + 1))

#define TEST_COUNT 100
#define ARRAY_LENGTH 50000
#define DATA_MIN 0
#define DATA_MAX 32767
#define RADIX 10
#define RADIX_MAX 5

static int data[ARRAY_LENGTH] = {0};

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

static void selection_sort(int *pdata, int size){
    int i, j;
    log("<%s>\n", __FUNCTION__);
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            int tmp;
            if (pdata[i] > pdata[j]) {
                tmp = pdata[i];
                pdata[i] = pdata[j];
                pdata[j] = tmp;
            }
        }
    }
}

static void insertion_sort(int *pdata, int size){
    int i, j;
    log("<%s>\n", __FUNCTION__);
    for (i = 1; i < size; i++) {
        int tmp = pdata[i];
        for (j = i - 1; j >= 0; j--) {
            if (tmp < pdata[j]) {
                pdata[j + 1] = pdata[j];
            }
            else {
                pdata[j + 1] = tmp;
                break;
            }
        }
    }
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
    __quick_sort(pdata, left, sep - 1);
    __quick_sort(pdata, sep + 1, right);
}

static void quick_sort(int *pdata, int size){
    int left = 0;
    int right = size - 1;
    log("<%s>\n", __FUNCTION__);
    __quick_sort(pdata, left, right);
}

/*
* merge sort
*/
static int merge_sort_space[ARRAY_LENGTH] = {0};

static void merge(int *pdata, int *pwork, int left, int middle, int right){
    int subl = left;
    int subr = middle + 1;
    int i;

    for (i = left; i <= right; i++) {
        if (subl <= middle && (subr > right || pdata[subl] < pdata[subr])) {
            pwork[i] = pdata[subl++];
        }
        else {
            pwork[i] = pdata[subr++];
        }
    }

    for (i = left; i <= right; i++) {
        pdata[i] = pwork[i];
    }   
}

static void __merge_sort(int *pdata, int *pwork, int left, int right){
    int middle;

    if (left >= right){
        return;
    }
    
    /*splitting*/
    middle = (left + right) / 2;
    __merge_sort(pdata, pwork, left, middle);
    __merge_sort(pdata, pwork, middle + 1, right);
    
    merge(pdata, pwork, left, middle, right);
}

static void merge_sort(int *pdata, int size){
    int left = 0;
    int right = size - 1;

    log("<%s>\n", __FUNCTION__);
    __merge_sort(pdata, merge_sort_space, left, right);
}

/*
* heap sort
*/

/*shift down a root-exceptional max heap*/
static inline void shift_down(int *pdata, int root, int size) {
    int bd = size - 1;
    int rep = root;
    int lch = root * 2 + 1;
    int rch = lch + 1;

    while (lch <= bd) {
        if (rch > bd) {
            rep = lch;
        }
        else {
            rep = (pdata[lch] > pdata[rch]) ? lch : rch;
        }

        if (pdata[rep] > pdata[root]) {
            int tmp = pdata[root];
            pdata[root] = pdata[rep];
            pdata[rep] = tmp;
        }
        else {
            return;
        }

        root = rep;
        lch = root * 2 + 1;
        rch = lch + 1;
    }    
}

static inline void heapify(int *pdata, int size) {
    int r;

    for (r = (size - 2) / 2; r >= 0; r--) {
        shift_down(pdata, r, size);        
    }
}

static void heap_sort(int *pdata, int size){
    int heap_size = size;

    log("<%s>\n", __FUNCTION__);
    heapify(pdata, size);
    while (heap_size > 1) {
        int tmp;

        tmp = pdata[0];
        pdata[0] = pdata[heap_size - 1];
        pdata[heap_size - 1] = tmp;
        heap_size--;

        shift_down(pdata, 0, heap_size);
    }
}

/*
* radix sort
*/
#if 0
typedef struct node_s {
    int value;
    char used;
    struct node_s *pnext;
} node_t;

static node_t *heads[RADIX] = {NULL};
static node_t *tails[RADIX] = {NULL};

static node_t workspace[ARRAY_LENGTH] = {{0, 0, NULL}};

static node_t * node_alloc(int value) {
    int i;
    for (i = 0; i < ARRAY_LENGTH; i++){
        if (workspace[i].used == 0) {
            workspace[i].used = 1;
            workspace[i].value = value;
            return &workspace[i];
        }
    }
    printf("error: node alloc fails!\n");
    return NULL;
}

static void node_free(node_t *pnode) {
    if (pnode) {
        pnode->used = 0;
        pnode->pnext = NULL;
    }
}

static void append(node_t **heads, node_t **tails, int value, int index){
    node_t *pnew = node_alloc(value);
    if (!pnew) {
        return;
    }

    if (!heads[index]) {
        heads[index] = pnew;
        tails[index] = pnew;
    }
    else {
        tails[index]->pnext = pnew;
        tails[index] = pnew;
    }
}

static int head_remove(node_t **heads, node_t **tails, int index){
    node_t *pnext = heads[index]->pnext;
    int value = heads[index]->value;
    
    node_free(heads[index]);
    heads[index] = pnext;
    if (!heads[index]) {
        tails[index] = NULL;
    }
    return value;
}

static void collect(int *pdata, int size, node_t **heads, node_t **tails){
    int i = 0;
    int index = 0;

    while (index < RADIX && i < size) {
        while (heads[index]) {
            pdata[i++] = head_remove(heads, tails, index);
        }
        index++;
    }
    //log("collect debug: index, i = %d, %d\n", index, i);
}

static void distribute(int *pdata, int size, node_t **heads, node_t **tails, int base){
    int i;
    int r = pow(10, base);
    int rval;

    for (i = 0; i < size; i++) {
        rval = (pdata[i] / r) % 10;
        append(heads, tails, pdata[i], rval);   
    }    
}
#endif

static void radix_sort(int *pdata, int size){
    int i, j;
    int r = 1;
    int work[ARRAY_LENGTH] = {0};
    int index[RADIX] = {0};

    log("<%s>\n", __FUNCTION__);
    #if 0
    for (i = 1; i <= RADIX_MAX; i++) {
        distribute(pdata, size, heads, tails, i - 1);
        collect(pdata, size, heads, tails);
    }
    #endif
    for (i = 1; i <= RADIX_MAX; i++) {
        /*count for each digit*/
        for (j = 0; j < size; j++) {
            index[(pdata[j] / r) % 10]++;
        }
        /*caculate the tail positions for each digit list*/
        for (j = 1; j < RADIX; j++) {
            index[j] += index[j - 1];
        }

        /*distribute*/
        for (j = size - 1; j >= 0; j--) {
            work[--index[(pdata[j] / r) % 10]] = pdata[j];
        }

        memset(index, 0, RADIX * sizeof(int));

        /*collect back*/
        for (j = 0; j < size; j++) {
            pdata[j] = work[j];
        }
        
        r *= RADIX;
    }    
}


typedef void (*sort_method)(int *, int);

static sort_method sortings[] = {
    //selection_sort,
    //insertion_sort,
    quick_sort,
    merge_sort,
    heap_sort,
    radix_sort,
};

static const char *sort_type[] = {
    //"selection sort",
    //"insertion sort",
    "quick sort",
    "merge sort",
    "heap sort",
    "radix sort",
};

int main(int argc, char **argv){
    int i;
    int tp;
    int tp_cnt = sizeof(sortings) / sizeof(sortings[0]);
    
    srand(time(NULL));

    for (tp = 0; tp < tp_cnt; tp++) {
        sort_method psort = sortings[tp];
        const char *pname = sort_type[tp];
        clock_t c = clock();
        for (i = 0; i < TEST_COUNT; i++) {
            initialize(data, ARRAY_LENGTH);
            psort(data, ARRAY_LENGTH);
            dump(data, ARRAY_LENGTH);
        }
        c = clock() - c;
        printf("<%s> --- duration for %d data & %d times: %f\n\n", pname, ARRAY_LENGTH, TEST_COUNT, (double)c / (double)(CLOCKS_PER_SEC));
    }

    return 0;    
}
