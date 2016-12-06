#include <stdio.h>
#include <stdlib.h>

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

int stack_push(void *st, int val) {
    my_stack_t *s = (my_stack_t *)st;
    if (s->top >= s->size) {
        printf("Error: Stack is full!\n");
        return -1;
    }

    s->stack[s->top++] = val;
    return 0;
}

int stack_pop(void *st, int *val) {
    my_stack_t *s = (my_stack_t *)st;
    if (s->top == 0) {     /*Empty*/
        return -1;
    }

    *val = s->stack[--s->top];
    return 0;
}

