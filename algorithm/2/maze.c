#include "utils.h"

static char visted[MAX_NODE] = {0};

static int dfs_search(const char *dest) {
    int i = 0;
    int pos = 0; 
    int start = 1;
    void *st = NULL;

    st = stack_new(MAX_NODE * MAX_NODE);
    if (!st) {
        exit(1);
    }

    /*entrance*/
    printf("Here we go!\n");
    stack_push(st, pos);    

    while (1) {
        pos = stack_pop(st);
        if (pos == -1) { /*all nodes were visited*/
            break;
        }

        if (!visted[pos]) {
            footprint(pos, start);
            visted[pos] = 1;
            stack_push(st, 0);  /*new iteration*/
        }

        if (start == 1) {
            start = 0;
        }

        if (strcmp(dest, place(pos)) == 0) {
            printf("\nHere we are !\n");
            stack_del(st);
            return 0;
        }

        for (i = stack_pop(st); i < MAX_NODE; i++) {
            if (conns[pos][i] && !visted[i]) {
                stack_push(st, i);  /*Save current iteration*/
                stack_push(st, pos);
                stack_push(st, i);
                break;
            }
        }
    }

    printf("\nCan't find destination.\n");
    stack_del(st);
    return -1;            
}

static int bfs_search(const char *dest) {
    int pos = 0;
    char start = 1;
    adj_lnode_t *l;
    
    /*entrance*/
    printf("Here we go !\n");
    queue_push(pos);

    while (1) {
        pos = queue_pop();
        if (pos == -1) { /*Empty*/
            break;
        }

        footprint(pos, start);
        visted[pos] = 1;
        if (start == 1) {
            start = 0;
        }

        if (strcmp(dest, place(pos)) == 0) {
            printf("\nHere we are !\n");
            return 0;
        }   

        l = adj_list_head[pos];
        while (l) {
            if (!visted[l->adj]) {
                queue_push(l->adj);
            }
            l = l->next;
        }
    }

    printf("\nCan't find destination.\n");
    return -1;
}

int main(int argc, char **argv) {

    if (argc != 3 || !argv[1] || !argv[2]) {
        printf("Please specify destination and search mode!\n");
        exit(1);
    }

    atexit(maze_uninit);
    maze_init();

    if (strcmp(argv[2], "dfs") == 0) {
        return dfs_search(argv[1]); 
    }
    else if (strcmp(argv[2], "bfs") == 0) {
        return bfs_search(argv[1]);
    } 
    else {
        printf("Unkown search mode: %s\n", argv[2]);
        exit(1);
    }
}
