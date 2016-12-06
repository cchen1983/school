#include "utils.h"

#define MAX 7

static char dg_a[MAX][MAX] = {
    {0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 1, 0},
    {1, 1, 1, 0, 0, 1, 1},
    {0},
    {0},
    {0, 0, 0, 0, 1, 1, 0}
};

static char dg_b[MAX][MAX] = {
    {0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 1, 0, 0}
};

static char visited[MAX] = {0};
static char (*dg)[MAX][MAX] = NULL;

static int __dfs_top(int src, void *sd, void *st) {
    int i = 0;
    char passed[MAX] = {0};    

    stack_push(sd, src);
    while (1) {
        src = stack_pop(sd);
        if (src == -1) {  /*empty*/
            break;
        }

        if (!visited[src]) {
            visited[src] = 1;
            stack_push(sd, 0); /*new iteration*/
        }

        passed[src] = 1; /*save current path, for cycle check*/

        for (i = stack_pop(sd); i < MAX; i++) {
            if ( (*dg)[src][i] && !visited[i] ) {
                stack_push(sd, i);  /*save current iteration*/
                stack_push(sd, src);
                stack_push(sd, i);
                break;
            }
            else if ( (*dg)[src][i] && visited[i] && passed[i]) { 
                /*find a child ever passed by*/
                printf("[%c, %c] is in a cycle, not a topological graph!\n", 'a' + src, 'a' + i);
                return -1;
            }
        }
        
        //printf("src[%c], @_@ i=%c\n", 'a' + src, 'a' + i);
        if (i == MAX) {
            stack_push(st, src); /*pick up in reverse topological order, by topstack */
            memset(passed, 0, sizeof(passed));  /*clear for next branch*/
        }
    }

    return 0;
}

static int dfs_top(void) {
    void *s_dfs = stack_new(50);
    void *s_top = stack_new(50);
    int i;

    for (i = 0; i < MAX; i++) {
        if (!visited[i]) {
            if (__dfs_top(i, s_dfs, s_top) != 0) { /*cyclic graph, not a topological model*/
                return -1;
            }
        }
    }

    printf("toporder: \n");
    i = stack_pop(s_top);
    while (i >= 0) {
        printf("[%c]  ", 'a' + i);
        i = stack_pop(s_top);    
    }  
    printf("\n");    
    
    stack_del(s_dfs);
    stack_del(s_top);
    return 0;
}

static int srcrm_top(void) {
    int i = 0;
    int j = 0;
    int e = 0;  /*erased cnt*/
    char erased[MAX] = {0};    
 
    printf("toporder: \n");
    while (e < MAX) {
        for (j = 0; j < MAX; j++) {
            if (erased[j]) {
                continue;
            }

            for (i = 0; i < MAX; i++) {
                if ((*dg)[i][j]) {
                    break;
                }
            }

            if (i == MAX) {     /*print & erase the source*/
                printf("[%c]  ", 'a' + j);
                for (i = 0; i < MAX; i++) {
                    (*dg)[j][i] = 0;
                }
                e++;
                erased[j] = 1;
                break;                   
            }
        }
        
        if (j == MAX) { /*Can't find a source*/
            break;
        }
    }

    if (e != MAX) {
        printf("\nCan't find next source, not a topological graph.\n");
        return -1;
    }
    printf("\n");

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2 || !argv[1]) {
        printf("Please specify topological sort type!\n");
        exit(1);
    }    

    if (strcmp(argv[1], "dfs") == 0) {  /*DFS Based Topological Sort*/
        dg = &dg_b;
        return dfs_top();
    }
    else if (strcmp(argv[1], "srcrm") == 0) { /*Source removal*/
        dg = &dg_b;
        return srcrm_top();
    }
    else {
        printf("Unkown topological sort type: %s\n", argv[1]);
        exit(1);
    }
}
