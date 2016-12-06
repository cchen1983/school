#include "utils.h"

static const char *vname[MAX_NODE] = {
    "Entrance",
    "Fork2",
    "End3",
    "Fork4",
    "Fork5",
    "End6",
    "Fork7",
    "End8",
    "Fork9",
    "End10",
    "End11",
    "Fork12",
    "Bear",
    "Goose",
    "Fox",
    "Fork16",
    "End17",
    "End18",
    "Fork19",
    "End20",
    "Squirrel",
    "Fountain"
};

char conns[MAX_NODE][MAX_NODE] = {
    {0}         /*To be initialized*/
};

adj_lnode_t *adj_list_head[MAX_NODE] = {
    NULL       /*To be initialized*/
};

static adj_lnode_t *adj_list_tail[MAX_NODE] = {
    NULL       /*To be initialized*/
};

static void adj_list_create(void);
static void adj_list_destroy(void);

/*Setup & Dump*/
const char * place(int index) {
    return vname[index];
}

void footprint(int index, char start) {
    if (start == 1) {
        printf("[%s] ", vname[index]);
    }
    else {
        printf("--->[%s]", vname[index]);
    }
}

void maze_init(void) {
    memset(conns, 0, sizeof(conns));
    conns[0][1] = 1;
    conns[0][11] = 1;
    conns[1][0] = 1;
    conns[1][2] = 1;
    conns[1][3] = 1;
    conns[1][4] = 1;
    conns[2][1] = 1;
    conns[3][1] = 1;
    conns[3][14] = 1;
    conns[3][21] = 1;
    conns[4][1] = 1;
    conns[4][5] = 1;
    conns[4][6] = 1;
    conns[5][4] = 1;
    conns[6][4] = 1;
    conns[6][7] = 1;
    conns[6][8] = 1;
    conns[7][6] = 1;
    conns[8][6] = 1;
    conns[8][9] = 1;
    conns[8][10] = 1;
    conns[9][8] = 1;
    conns[10][8] = 1;
    conns[11][0] = 1;
    conns[11][12] = 1;
    conns[11][13] = 1;
    conns[12][11] = 1;
    conns[13][11] = 1;
    conns[14][3] = 1;
    conns[14][15] = 1;
    conns[14][18] = 1;
    conns[15][14] = 1;
    conns[15][16] = 1;
    conns[15][17] = 1;
    conns[16][15] = 1;
    conns[17][15] = 1;
    conns[18][19] = 1;
    conns[18][20] = 1;
    conns[19][18] = 1;
    conns[20][18] = 1;
    conns[21][3] = 1;

    adj_list_create();
}

void maze_uninit(void) {
    adj_list_destroy();
}

static void adj_list_destroy(void) {
    int i;

    for (i = 0; i< MAX_NODE; i++) {
        adj_lnode_t *l = adj_list_head[i];
        while (l) {
            adj_lnode_t *n = l;
            l = l->next;
            free(n);
        }
        adj_list_head[i] = NULL;
        adj_list_tail[i] = NULL;
    }
}

static void adj_list_create(void) {
    int i, j;

    for (i = 0; i < MAX_NODE; i++) {
        for (j = 0; j < MAX_NODE; j++) {
            if (conns[i][j] == 1) {
                adj_lnode_t *n = (adj_lnode_t *)malloc(sizeof(adj_lnode_t));
                if (n == NULL) {
                    printf("Error: fail to alloc adj list node.\n");
                    exit(1);
                }
                
                n->adj = j;
                n->next = NULL;
                if (adj_list_head[i] == NULL) {
                    adj_list_head[i] = n;
                    adj_list_tail[i] = n;                                           
                }
                else {
                    adj_list_tail[i]->next = n;
                    adj_list_tail[i] = n;
                }
            }
        }
    }
}

#if 0
/*Stack Class*/
#define STACK_SZ (MAX_NODE * MAX_NODE)
static int stack[STACK_SZ];
static int top = 0;

void stack_push(int val) {
    if (top >= STACK_SZ) {
        printf("Error: Stack is full!\n");
        exit(1);
    }

   stack[top++] = val;
}

int stack_pop(void) {
    if (top == 0) {     /*Empty*/
        return -1;
    }

    return stack[--top];
}
#endif 

/*Dynamic Stack Class*/
typedef struct my_stack_s {
    int *stack;
    int top;
    int size;
} my_stack_t;

void *stack_new(int size) {
    my_stack_t *st = (my_stack_t *)malloc(sizeof(my_stack_t) + size);
    if (!st) {
        printf("Fail to alloc stack size=%d\n", size);
        return NULL;
    }

    st->stack = (int *)((char *)st + sizeof(my_stack_t));
    st->top = 0;
    st->size = size;
    return (void *)st;
}

void stack_del(void *st) {
    if (st) {
        free(st);
    }
}

void stack_push(void *st, int val) {
    my_stack_t *s = (my_stack_t *)st;
    if (s->top >= s->size) {
        printf("Error: Stack is full!\n");
        exit(1);
    }

   s->stack[s->top++] = val;
}

int stack_pop(void *st) {
    my_stack_t *s = (my_stack_t *)st;
    if (s->top == 0) {     /*Empty*/
        return -1;
    }

    return s->stack[--s->top];
}

/*Queue Class*/
#define QUEUE_SZ (MAX_NODE * MAX_NODE)
static int queue[QUEUE_SZ];
static int head = 0;
static int tail = 0;

void queue_push(int val) {
    if ( (tail + 1) % QUEUE_SZ == head ) {
        printf("Error: Queue is full!\n");
        exit(1);
    }

    queue[tail] = val;
    tail = (tail + 1) % QUEUE_SZ;
}

int queue_pop(void) {
    int v;
    if (tail == head) { /*Empty*/
       return -1;
    }

    v = queue[head];
    head = (head + 1) % QUEUE_SZ;
    return v;
}

