#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CNT 5
#if 1
static unsigned int map[CNT][CNT] = {
    {0, 2, -1, 3, 6},
    {2, 0, 4, 3, -1},
    {-1, 4, 0, 7, 3},
    {3, 3, 7, 0, 3},
    {6, -1, 3, 3, 0}
};
#else
static unsigned int map[CNT][CNT] = {
    {0, 8, 4, 5, 6},
    {8, 0, 4, 3, -1},
    {4, 4, 0, 7, 3},
    {5, 3, 7, 0, 3},
    {6, -1, 3, 3, 0}
};
#endif

#define SUM(x, y) (((x) == -1 || (y == -1)) ? -1 : (x) + (y))
#define MIN(x, y) ((x) <= (y) ? (x) : (y))

/* universal set : {0, 1, 2, 3 ... n - 1}, 0 is start point */
#define COMB 16  // Combinations (except site 0): {1, 2, ..., n - 1} total:2^(n - 1)

/* 2015-04-29 @ cchen
 *
 * Dynamical Programming Solution of TSP is hart to understand,
 * so I comment it here as a hint in case I forget it someday.
 *
 * cost[j][comb] means the minmal cost of path which
 * pass through the subset 'comb' and end at site 'j', 
 * comb is start from 0  and each site only passed by once
 * j != 0
 *
 * let's say cost[i][comb-{j}] means the minmal cost of path
 * pass through 'comb-{j}' and end at site 'i', 
 * 'comb-{j}' means the subset of 'comb' not include site j
 *
 * all combs can't end at site 0
 *
 * We can infer the optimal formula here:
 * 
 *  cost[j][comb] = min { cost[i][comb-{j}] + distance(i, j) }
 *
 *  Initially:
 *      cost[j][{}] = distance(0, j)
 *
 *  comb is from {} to {2^(n - 1)} since site 0 is already selected
 * */

static unsigned int cost[CNT][COMB];

int main (int argc, char **argv) {
    int i, j, c;
    //int sz;
    unsigned int result = -1;

    memset(cost, -1, sizeof(cost));

    /*Init cost[j][{}]*/
    for (j = 0; j < CNT; j++) {
        cost[j][0] = map[0][j];
    }

    /*Denote combs by bits mask, eg:
    *   0           comb {}
    *   00000001    comb {1}
    *   00000101    comb {1, 3}
    *   COMB - 1     comb {1, 2, 3, ..., n - 1}
    * */

    /* 1 << (i - 1)  means bits mask of site i*/
    /*combs start from 1, because cost[j][0] have been initialized*/
    for (c = 1; c < COMB; c++) {
        for (j = 1; j < CNT; j++) { /*try all ends j*/
            for (i = 1; i < CNT; i++) { /*try all internal ends i*/
                if ( (1 << (i - 1)) & c ) { 
                    /*only if site i is in current comb c*/

                    /* For both of 'j is in c' and i == j: 
                    * cost[j][c] = min { cost[i][c - {j}] + map[i][j] } will perform a 
                    * invalid update to cost[j][c], but it's necessary
                    * for passing the optimal value
                    * to next dimension combs [c + 1] for minimal reference. */

                    /* For j is not in c:
                    * cost[j][c] = min { cost[i][c] + map[i][j] }
                    * cost[i][c] == cost[i][c - {i}] + map[i][i] (map[i][i] is zero)
                    * c - {i} ==> bits mask: c - (1 << (i - 1))
                    * cost[i][c - {i}] has been set by previous iterations
                    * */
                    cost[j][c] = MIN( cost[j][c], SUM(cost[i][c - (1 << (i - 1))], map[i][j]) );
                }
            }
        }
    }

    /*cost[j][COMB - 1] means the minimal path cost for comb{1, 2, ..., n - 2} to (n - 1)th end j */
    for (j = 1; j < CNT; j++) {
        result = MIN(result, SUM( cost[j][COMB - 1], map[j][0]) );
    }

    printf("Shortest path cost: %d\n", result);

    /*
    for (sz = 2; sz <= CNT; sz++) { //size 2 ~ n
        for (c) {  // all subsets in each size
            for (j = 1; j < CNT; j++) {  //try all possible ends j
                for (i = 1; i < CNT; i++) {
                    cost[j][c] = MIN(cost[j][c], cost[i][c - {i}] + map[i][j]);
                }
            }
        }
    }
    */

    return 0;
}
