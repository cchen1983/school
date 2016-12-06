#include "utils.h"

#define CNT 5
#define WHT 6

static int val[CNT] = {25, 20, 15, 40, 50}; 
static int wht[CNT] = {3, 2, 1, 4, 5};

static int K[CNT + 1][WHT + 1];  //knapsack solutions

/*divide and conquer*/
static int knapsack_dc(int v[], int w[], int cnt, int mw) {
    if (cnt == 0 || mw == 0) {
        return 0;
    }

    if (mw < w[cnt]) {
        return knapsack_dc(v, w, cnt - 1, mw);
    }
    else {
        int v1 = knapsack_dc(v, w, cnt - 1, mw);
        int v2 = knapsack_dc(v, w, cnt - 1, mw - w[cnt]) + v[cnt];

        return (v1 > v2) ? v1 : v2;
    }
}

/*dynamic recursion*/
static int knapsack_memo(int k[][WHT + 1], int v[], int w[], int cnt, int mw) {
    if (k[cnt][mw] == INF) {
        if (mw < w[cnt]) {
            k[cnt][mw] = knapsack_dc(v, w, cnt - 1, mw);
        }
        else {
            int v1 = knapsack_dc(v, w, cnt - 1, mw);
            int v2 = knapsack_dc(v, w, cnt - 1, mw - w[cnt]) + v[cnt];

            k[cnt][mw] = (v1 > v2) ? v1 : v2;
        }
    }
    return k[cnt][mw];
}

/*dynamic iteration*/
static int knapsack_iter(int k[][WHT + 1], int v[], int w[], int cnt, int mw) {
    int i, j;    
    
    for (i = 1; i <= cnt; i++) {
        for (j = 1; j <= mw; j++) {
            if (j < w[i]) {
                k[i][j] = k[i - 1][j];
            }
            else {
                int v1 = k[i - 1][j];
                int v2 = k[i - 1][j - w[i]] + v[i];
                k[i][j] = (v1 > v2) ? v1 : v2;
            }
        }
    }
    
    return k[cnt][mw];
}

int main(int argc, char **argv) {
    int i, j;

    printf("#Divide and Conquer:\n");
    printf("Max revenue : %d\n", knapsack_dc(val, wht, CNT, WHT)); 

    memset(K, INF, sizeof(K));  
    memset(K, 0, sizeof(K[0]));
    for (i = 1; i <= CNT; i++) {
        K[i][0] = 0;
    }
    printf("\n#Dynamical recursion:\n");
    printf("Max revenue : %d\n", knapsack_memo(K, val, wht, CNT, WHT));

    memset(K, 0, sizeof(K[0]));
    for (i = 1; i <= CNT; i++) {
        K[i][0] = 0;
    }
    printf("\n#Dynamical iteration:\n");
    printf("Max revenue : %d\n", knapsack_iter(K, val, wht, CNT, WHT));
    for (i = 0; i < CNT + 1; i++) {
        for (j = 0; j < WHT + 1; j++) {
            printf("[%d]  ", K[i][j]);
        }
        printf("\n");
    }

    return 0;
}
