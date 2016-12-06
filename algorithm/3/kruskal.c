#include "utils.h"

#define CNT 6

typedef struct edge_s {
    unsigned int v1;
    unsigned int v2;
    unsigned int weight;
} edge_t;

static edge_t edges[(CNT - 1) * (CNT - 1)];
static int edge_idx[(CNT - 1) * (CNT - 1)] = {0};  //Cursor : Put sorted edges' index here

static unsigned int G[CNT][CNT] = {
    {0, 10, 10, INF, 30, 100},
    {10, 0, 5, INF, INF, INF},
    {10, 5, 0, 50, INF, INF},
    {INF, INF, 50, 0, 20, 10},
    {30, INF, INF, 20, 0, 60},
    {100, INF, INF, 10, 60, 0}
};

/*
 * heap sort
 */
/*shift down a root-exceptional max heap*/
static void shift_down(int *pdata, int root, int size, edge_t e[]) {
    int bd = size - 1;
    int rep = root;
    int lch = root * 2 + 1;
    int rch = lch + 1;

    while (lch <= bd) {
        if (rch > bd) {
            rep = lch;
        }
        else {
            rep = (e[pdata[lch]].weight > e[pdata[rch]].weight) ? lch : rch;
        }

        if (e[pdata[rep]].weight > e[pdata[root]].weight) {
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

/*add a new node to the tail of current max heap, then shift it up to heapify*/
static void shift_up(int *pdata, int size, edge_t e[]) {
    int parent;
    int new = size; 
    
    while (new > 0) {
        parent = (new - 1) / 2;
        if (e[pdata[new]].weight > e[pdata[parent]].weight) { /*the new node is larger, swap it with parent*/
            int tmp = pdata[new];
            pdata[new] = pdata[parent];
            pdata[parent] = tmp;        
        }
        else {
            return;
        }
        new = parent;
    } 
}

static void heap_sort(int *pdata, int size, edge_t e[]){
    int heap_size = size;

    log("<%s>\n", __FUNCTION__);
    while (heap_size > 1) {
        int tmp;

        tmp = pdata[0];
        pdata[0] = pdata[heap_size - 1];
        pdata[heap_size - 1] = tmp;
        heap_size--;

        shift_down(pdata, 0, heap_size, e);
    }
}

static int extract_edges(unsigned int g[][CNT], edge_t e[], int ei[]) {
    int cnt = 0;
    int i, j;
    
    for (i = 0; i < CNT - 1; i++) {
        for (j = i + 1; j < CNT; j++) {
            if (g[i][j] < INF) {
                /*Append a new edge to the tail*/
                e[cnt].v1 = i;
                e[cnt].v2 = j;
                e[cnt].weight = g[i][j];
                ei[cnt] = cnt;

                /*heapify the edges by index*/
                shift_up(ei, cnt, e);
                
                cnt++;
            }
        }
    }

    return cnt;
}

static void edge_sorting(edge_t e[], int ei[], unsigned int cnt) {
    heap_sort(ei, cnt, e);

    /*  sorting debug */
    printf("%s : ", __FUNCTION__);
    while (cnt > 0) {
        printf("[%d]  ", e[ei[--cnt]].weight);
    }
    printf("\n");
}

static void kruskal(edge_t e[], int ei[], int ecount, unsigned int res[]) {
    int i = 0;
    int cnt = 0;
    int gid = 0;
    int weights = 0;
    int group[CNT];

    memset(group, INF, sizeof(group));

    printf("#Kruskal Best Solution: \n");
    while (cnt < CNT - 1 && i < ecount) {
        int v1 = e[ei[i]].v1;
        int v2 = e[ei[i]].v2;
        int w = e[ei[i]].weight;
        int old_cnt = cnt;        

        if (group[v1] == INF && group[v2] == INF) {
            group[v1] = gid;
            group[v2] = gid;
            gid++;
            cnt++;
            weights += w;
        }
        else if (group[v1] == INF || group[v2] == INF) {
            if (group[v1] == INF) {
                group[v1] = group[v2];
            }
            else {
                group[v2] = group[v1];
            }
            cnt++;
            weights += w;
        }
        else if (group[v1] != group[v2]) {
            int j;
            for (j = 0; j < CNT; j++) {
                if (group[j] == group[v1]) {
                    group[j] = group[v2];
                }
            }
            cnt++;
            weights += w;
        }

        i++;
        
        if (old_cnt != cnt) {
            printf("[%d---%d] ", v1, v2);
        }
    }

    if (cnt < CNT - 1) {
        printf("\nCan't find a Minimal Spinning tree!\n");
    }
    else {
        printf("\nTotal weights: %d\n", weights);
    }
}

int main(int argc, char **argv) {
    unsigned int res[CNT - 1];
    unsigned int cnt;   /*count of edges*/

    memset(edges, INF, sizeof(edges));
    memset(res, INF, sizeof(res));

    cnt = extract_edges(G, edges, edge_idx);
    if (cnt == 0) {
        printf("There is no edge in the graph!\n");
        return -1;
    }

    edge_sorting(edges, edge_idx, cnt);
    kruskal(edges, edge_idx, cnt, res);

    return 0;
}
