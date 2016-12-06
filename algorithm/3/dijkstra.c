#include "utils.h"

#define CNT 6

#if 1
static unsigned int G[CNT][CNT] = {
    {0, 10, 10, INF, 30, 100},
    {10, 0, 5, INF, INF, INF},
    {10, 5, 0, 50, INF, INF},
    {INF, INF, 50, 0, 20, 10},
    {30, INF, INF, 20, 0, 60},
    {100, INF, INF, 10, 60, 0}
};
#else
/*for separated case (illegal graph)*/
static unsigned int G[CNT][CNT] = {
    {0, 1, 4, INF, INF, INF},
    {1, 0, 2, INF, INF, INF},
    {4, 2, 0, INF, INF, INF},
    {INF, INF, INF, 0, INF, INF},
    {INF, INF, INF, INF, 0, INF},
    {INF, INF, INF, INF, INF, 0}
};
#endif

static void dijkstra(unsigned int g[][CNT], unsigned int weights[], unsigned int path[], unsigned int src) {
    char found[CNT] = {0};
    unsigned int i, j, from, to;
    unsigned int w;

    /*pick up the start point*/
    found[src] = 1;

    for (i = 0; i < CNT - 1; i++) {
        w = INF;

        for (j = 0; j < CNT; j++) { /*searching for the lightest path in neighborhood*/
            if (!found[j] && w > weights[j]) {
                w = weights[j];
                from = j;
            }
        }

        if (w == INF) { /*no neighbor any more*/
            return;
        }

        found[from] = 1; /*get and pick up the lightest path*/
        
        for (to = 0; to < CNT; to++) {
            if (!found[to] && g[from][to] < INF 
                && weights[to] > weights[from] + g[from][to]) {
                /*Update it to a lighter path*/
                weights[to] = weights[from] + g[from][to];
                path[to] = from;
            }
        }
    }
}

int main(int argc, char **argv) {
    unsigned int src;
    unsigned int i;
    unsigned int weights[CNT];
    unsigned int from[CNT];

    if (argc != 2) {
        printf("Please specify the source point!\n");
        return -1;
    }

    src = atoi(argv[1]);
    memset(weights, INF, sizeof(weights));
    memset(from, INF, sizeof(from));
    
    for (i = 0; i < CNT; i++) {
        if (G[src][i] < INF) {
            weights[i] = G[src][i];
            from[i] = src;
        }
    }

    dijkstra(G, weights, from, src);

    printf("#Dijkstra Best Solution: \n");
    for (i = 0; i < CNT; i++) {
        if (i != src) {
            printf("From [%d] to [%d] : total = %d\n", src, i, weights[i]);
            if (weights[i] != INF) {
                int p = i;
                printf("[%d]", p);
                while (from[p] < INF && p != src) {
                    printf("<---[%d]", from[p]);
                    p = from[p];
                }  
            }
            printf("\n");
        }
    }

    return 0;
}
