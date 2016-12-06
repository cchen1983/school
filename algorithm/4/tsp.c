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

static void dump(int path[]) {
    int i;
    unsigned int c = 0;
    static int min[CNT];
    static unsigned int cost = -1;

    if (!path) {
        printf("best path: ");
        for (i = 0; i < CNT; i++) {
            printf("[%d]----->", min[i] + 1);
        }
        printf("[%d]\ncost: %d\n", min[0] + 1, cost);

        cost = -1;  // reset
        return;
    }

    for (i = 0; i < CNT; i++) {
        printf("[%d]----->", path[i] + 1);
        if (i > 0) {
            c += map[path[i - 1]][path[i]];
        }
    }
    c += map[path[CNT - 1]][path[0]];
    printf("[%d]    cost: %d\n", path[0] + 1, c);

    if (c < cost) { //Update reference to minimal path cost
        cost = c;
        memcpy(min, path, sizeof(min));
    }
}

/*non-repeated and connected*/
static char is_valid(int path[], int next) {
    int i = 0;

    while (i < next) {
        if (path[i] == path[next]) {
            return 0;
        }
        i++;
    }
    
    if (map[path[next - 1]][path[next]] == -1) {
        return 0;
    }
    return 1;
}

/*connected*/
static char is_valid_rec(int path[], int next) {
    if (map[path[next - 1]][path[next]] == -1) {
        return 0;
    }
    return 1;
}

static void swp(int path[], int i, int j) {
    int temp;

    if (i == j) {
        return;
    }

    temp = path[i];    
    path[i] = path[j];
    path[j] = temp;
}

/*recursion in permutation*/
static void tsp_rec(int path[], int src, int next) {
    int i;

    if (next == CNT - 1) {
        if (is_valid_rec(path, next) && map[path[next]][path[0]] != -1) {
            dump(path);
        }
        return;
    }

    for (i = next; i < CNT; i++) {
        /*try each pereutation in next item*/
        swp(path, next, i);
        if (is_valid_rec(path, next)) {
            tsp_rec(path, src, next + 1);
        }
        swp(path, i, next);
    }
}

/*iteration*/
static void tsp_iter(int path[], int src) {
    int i = 1;  //tracking next path from here
    
    while (i >= 1) {
        while (path[i] < CNT && !is_valid(path, i)) {
            path[i]++;
        }

        if (path[i] < CNT) {
            if (i == CNT - 1) {
                if (map[path[i]][path[0]] != -1) {
                    dump(path);
                }
            }
            else {
                i++;
                path[i] = 0;
                continue;
            }
        }
        else {
            i--;
        }
        path[i]++;
    }
}

int main (int argc, char **argv) {
    int src = 0;
    int path[CNT];
    int i;    

    if (argc == 2) {
        src = atoi(argv[1]) - 1;
    }
    
    memset(path, 0, sizeof(path));
    path[0] = src;
   
    printf("============================Iteration TSP============================\n");
    tsp_iter(path, src);
    dump(NULL);

    /*initialization for permutation tsp*/
    for (i = 0; i < CNT; i++) {
        path[i] = i;
    }
    swp(path, 0, src);

    printf("\n============================Recursion TSP============================\n");
    tsp_rec(path, src, 1);
    dump(NULL);
    
    return 0;
}
