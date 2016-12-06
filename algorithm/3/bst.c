#include "utils.h"

#if 1
#define CNT 10

/*Probabilites of searching numbers from 0 to 9*/
static double pb[CNT] = {0.05, 0.1, 0.1, 0.15, 0.4, 0.05, 0.05, 0.03, 0.04, 0.03};

#else

#define CNT 4
static double pb[CNT] = {0.1, 0.2, 0.3, 0.4};

#endif

/*average costs*/
static double cost[CNT][CNT];
/*optimal binary search tree map*/
static int bst[CNT][CNT];

static void dump_bst(int root, int start, int end) {
    int l = (root == start) ? INF : root - 1;
    int r = (root == end) ? INF : root + 1;
    int lch = (l == INF) ? INF : bst[start][l];
    int rch = (r == INF) ? INF : bst[r][end];
    
    printf("[%d] : left=[%d]  right=[%d]\n", root, lch, rch); 

    if (lch != INF) {
        dump_bst(lch, start, l);
    }
    if (rch != INF) {
        dump_bst(rch, r, end);
    }
}

int main(int argc, char **argv) {
    int start, end;
    int i, j;
    int size;

    memset(cost, 0, sizeof(cost));
    memset(bst, INF, sizeof(bst));
    printf("[key : freq] sequence: \n");
    for (i = 0; i < CNT; i++) {
        cost[i][i] = pb[i];
        bst[i][i] = i;  //root of i to i
        printf("[%d : %f] ", i, pb[i]);
    }
    printf("\n");

    for (size = 2; size <= CNT; size++) {
        for (start = 0; start <= CNT - size; start++) {
            double base = 0;
            
            end = start + size - 1;
            for (j = start; j <= end; j++) {
                base += pb[j];
            }

            for (i = start; i <= end; i++) { //iteratively choosing root
                double lcost = (i == start) ? 0 : cost[start][i - 1]; 
                double rcost = (i == end) ? 0 : cost[i + 1][end];
                double c = base  + lcost + rcost;

                //printf("l, r = %f, %f  : %d, %d, %d\n", lcost, rcost, start, end, i);
                if (cost[start][end] == 0 || cost[start][end] > c) {
                    bst[start][end] = i;    //Record the root of start to end
                    cost[start][end] = c;
                }
            }
        } 
    }

    printf("Optimal Binary Search Tree: \n");
    printf("Average cost: %f\n", cost[0][CNT - 1]);
    printf("Tree Map: \n");
    for (i = 0; i < CNT; i++) {
        for (j = 0; j < CNT; j++) {
            printf("[%d]  ", bst[i][j]);
        }
        printf("\n");
    }

    printf("Cost Map: \n");
    for (i = 0; i < CNT; i++) {
        for (j = 0; j < CNT; j++) {
            printf("[%f]  ", cost[i][j]);
        }
        printf("\n");
    }

    printf("Relatives:\n");
    dump_bst(bst[0][CNT - 1], 0, CNT - 1); 
    return 0;
}
