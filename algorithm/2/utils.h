#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 22

typedef struct adj_lnode_s {
    int adj;
    struct adj_lnode_s *next;
} adj_lnode_t;

extern char conns[MAX_NODE][MAX_NODE];
extern adj_lnode_t *adj_list_head[MAX_NODE];

extern const char *place(int index);
extern void footprint(int index, char start);
extern void maze_init(void);
extern void maze_uninit(void);

extern void *stack_new(int size);
extern void stack_del(void *st);
extern void stack_push(void *st, int val);
extern int stack_pop(void *st);

extern void queue_push(int val);
extern int queue_pop(void);
 
