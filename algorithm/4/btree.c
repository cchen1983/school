#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define T 2

typedef struct node_s {
    char leaf;
    int key[2 * T - 1];    //keys in node, (T - 1) ~ (2T - 1); if it's root, 1 ~ (2T - 1).
    struct node_s * c[2 * T];  //children of node, always count of keys + 1.
    int n;      //count of keys
} node_t;

typedef struct btree_s {
    node_t *root;
    //int height;
} btree_t;

static int source[] = {5, 4, 6, 7, 10, 1, 8, 2, 11, 3, 20, 17, 19, 18, 12, 14, 13, 15, 16};
static btree_t tree;

static node_t * alloc_node(char leaf) {
    node_t *n = (node_t *)malloc(sizeof(node_t));
    if (!n) {
        printf("fail to alloc node.\n");
        return NULL;
    }

    memset(n, 0, sizeof(node_t));
    n->leaf = leaf;
    return n;
}

static void free_node(node_t *n) {
    free(n);
}

/*bfs dump
 * destroy == 0, only do print
 * destroy == 1, destroy whole tree after printed
 * */
static void dump(btree_t *t, char destroy) {
    node_t **queue = malloc(sizeof(source) * 2);
    int head;
    int size; /*queue size*/ 
    int i;
    int ls;   /*layer size*/ 
    int nls;  /*new layer size*/   

    queue[0] = t->root;
    head = 0;
    size = 1;
    ls = 1;
    nls = 0;

    while (size > 0) { 
        node_t *nd = queue[head++];
        
        if (ls == 0) { /*layer in the new depth*/
            ls = nls;
            nls = 0;
            printf("\n");
        }

        size--;
        ls--;
        if (!nd->leaf) {    //calculate new layer size
            nls += nd->n + 1;
        }
        
        for (i = 0; i < nd->n; i++) {
            if (!nd->leaf) {
                /*push children into queue*/
                queue[head + size] = nd->c[i];
                size++;
                if (i == nd->n - 1) {
                    queue[head + size] = nd->c[i + 1];
                    size++;
                }
            }
            
            printf("%d ", nd->key[i]);
        }
        printf("|| ");

        if (destroy) {
            free_node(nd);
        }
    }
    printf("\n\n");
    free(queue);
}

static void init_btree(btree_t *t) {
    node_t *root = alloc_node(1);
    t->root = root;
}

static void destroy_btree(btree_t *t) {
    dump(t, 1);
}

/*if matched, fill info to the res and k*/
static void search(node_t *r, int key, node_t **res, int *k) {
    int i;
    
    for (i = 0; i < r->n; i++) {
        if (key <= r->key[i]) {
            break;
        }
    }

    if (key == r->key[i]) {
        *res = r;
        *k = i;
        return;
    }

    if (r->leaf) {
        printf("key[%d] not exist!\n", key);
        return;
    }

    search(r->c[i], key, res, k);
}

/*split full size child c of node p by half of the full size (T - 1)*/
static void split_child(node_t *p, int c) {
    int i;
    node_t *new = alloc_node(p->c[c]->leaf);
    
    if (!new) {
        exit(1);
    }

    /*move 2nd half of c to new node*/
    new->n = T - 1;
    memcpy(&new->key[0], &p->c[c]->key[T], sizeof(new->key[0]) * (T - 1));
    if (!new->leaf) {
        memcpy(&new->c[0], &p->c[c]->c[T], sizeof(new->c[0]) * T);
    }
    p->c[c]->n = T - 1;
    
    /*shift the median key of c up to p*/
    /*insert new child to c+1 of p*/
    for (i = p->n + 1; i > c + 1; i--) {
        p->c[i] = p->c[i - 1];
    }
    p->c[c + 1] = new;
    /*insert median key of c to pos c of p*/
    for (i = p->n; i > c; i--) {
        p->key[i] = p->key[i - 1];
    }
    p->key[c] = p->c[c]->key[T - 1];
    p->n++;
}

/*insert to non-full node*/
static void __insert(node_t *n, int key) {
    int i, j;
    
    for (i = 0; i < n->n; i++) {
        if (key <= n->key[i]) {
            break;
        }
    }

    if (n->leaf) { /*if it's a leaf, insert*/
        for (j = n->n; j > i; j--) {
            n->key[j] = n->key[j - 1];
        }
        n->key[i] = key;
        n->n++;
    }
    else { /*or else, insert to corresponding child*/
        if (n->c[i]->n == 2 * T - 1) {   /*full, split it*/
            split_child(n, i);

            /*determine which splitd child to insert*/
            if (key <= n->key[i]) {
                __insert(n->c[i], key);
            }
            else {
                __insert(n->c[i + 1], key);
            }
        }
        else {
            __insert(n->c[i], key);
        }
    }
}

/*insert new key*/
static void insert(btree_t *t, int key) {
    if (t->root->n == 2 * T - 1) {
        /*if root is full, append a new empty root to the tree, 
         *then perform insertion again*/
        node_t *new = alloc_node(0);
        if (!new) {
            exit(1);
        }
        
        new->n = 0;
        new->c[0] = t->root;
        t->root = new;
        split_child(new, 0);
        __insert(new, key);
    }
    else {
        __insert(t->root, key);
    }
}

/*sink the key from parent, and merge with the left and right children*/
static void sink_and_merge(node_t *p, int k) {
    int i;
    node_t *left = p->c[k];
    node_t *right = p->c[k + 1];

    /*sink the key*/
    left->key[left->n] = p->key[k];
    /*append right to left*/
    memcpy(&left->key[left->n + 1], &right->key[0], sizeof(right->key[0]) * right->n);
    if (!left->leaf) {
        memcpy(&left->c[left->n + 1], &right->c[0], sizeof(right->c[0]) * right->n + 1);
    }
    left->n = 2 * T - 1;
    free_node(right);
    
    /*remove the key and right child from p*/
    for (i = k; i < p->n - 1; i++) {
        p->key[i] = p->key[i + 1];
        p->c[i + 1] = p->c[i + 2];
    }
    p->n--;
}

/*recursion of deleting a key*/
static void __delete(node_t *n, int key) {
    int i, j;

    for (i = 0; i < n->n; i++) {
        if (key <= n->key[i]) {
            break;
        }
    }

    if (key == n->key[i]) {
        if (n->leaf) {
            for (j = i; j < n->n - 1; j++) {
                n->key[j] = n->key[j + 1];
            }
            n->n--;
            
            return;
            /*done*/
        }
        else {
            int lc = n->c[i]->n;
            int rc = n->c[i + 1]->n;

            /*perform deletion only if there are enough items 
             *in left or right to replace the one to be deleted, 
             *or else perform merging and continue.*/
            if (lc > T - 1 || rc > T - 1) {
                if (lc > T - 1) {
                    /*shift up the last key from left to replace it*/
                    n->key[i] = n->c[i]->key[lc - 1];
                    n->c[i]->n--;
                }
                else {
                    /*shift up the first key from right to replace it*/
                    n->key[i] = n->c[i + 1]->key[0];
                    for (j = 0; j < rc - 1; j++) {
                        n->c[i + 1]->key[j] = n->c[i + 1]->key[j + 1];
                    }
                    n->c[i + 1]->n--;                    
                }

                return;
                /*done*/
            }
            else {
                sink_and_merge(n, i);
            }
        }
    }
    else {
        /*left and right siblings adjacent to target subtree*/
        node_t *ls = (i == 0) ? NULL : n->c[i - 1];
        node_t *rs = (i == n->n) ? NULL : n->c[i + 1];
               
        if (n->c[i]->n == T - 1) {
            int lc = ls ? ls->n : 0;
            int rc = rs ? rs->n : 0;

            if (lc > T - 1 || rc > T - 1) {
                /*shift up one key from adjacent child, sink down one key from p 
                *to target subtree to guarantee 
                * the keys in the root of target subtree is sufficient to do recursion*/
                if (lc > T - 1) {
                    for (j = 1; j < T; j++) {
                        n->c[i]->key[j] = n->c[i]->key[j - 1];
                    }
                    n->c[i]->key[0] = n->key[i - 1];    //sink
                    n->key[i - 1] = ls->key[lc - 1];    //Up
                    
                    /*move the relative child from left sibling to target node*/
                    for (j = 1; j < T + 1; j++) {
                        n->c[i]->c[j] = n->c[i]->c[j - 1];
                    }
                    n->c[i]->c[0] = ls->c[lc];

                    ls->n--;
                } 
                else {          
                    n->c[i]->key[T - 1] = n->key[i];    //sink
                    n->key[i] = rs->key[0];             //Up
                    for (j = 0; j < rc - 1; j++) {
                        rs->key[j] = rs->key[j + 1];
                    }

                    /*move relative child from right sibling to target node*/
                    n->c[i]->c[T] = rs->c[0];
                    for (j = 0; j < rc; j++) {
                        rs->c[j] = rs->c[j + 1];
                    }
            
                    rs->n--;
                }
                n->c[i]->n++;
            }
            else {
                /*both of them are insufficient, merge with any one*/
                if (rc == 0) { //always merge with right, except right not exist
                    i--;
                }
                sink_and_merge(n, i);
            }
        }
        
    }
    
    /*Recursion rules were Guaranteed, continue.*/
    __delete(n->c[i], key);
} 

/*delete a key*/
static void delete(btree_t *t, int key) {
    node_t *tgt = NULL;
    int k = -1;

    printf("Try to delete <%d>\n", key);
    search(t->root, key, &tgt, &k);
    if (!tgt) {
        return;
    }

    __delete(t->root, key);
}

static void dump_node(node_t *node) {
    int i;
    printf("Node: [leaf=%d] [size=%d]\n", node->leaf, node->n);
    for (i = 0; i < node->n; i++) {
        printf("%d ", node->key[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    int i;
    int sch;    
    int schk = -1;
    node_t *schn = NULL; 

    init_btree(&tree);

    /*build btree from source*/
    for (i = 0; i < (sizeof(source) / sizeof(source[0])); i++) {
        insert(&tree, source[i]);
    }
    dump(&tree, 0);

    /*searching*/
    sch = 10;
    printf("Searching <%d>....\n", sch);
    search(tree.root, sch, &schn, &schk);
    if (schn) {
        dump_node(schn);
        printf("matched key %d\n", schk);
    }

    schn = NULL;
    sch = 99;
    printf("Searching <%d>....\n", sch);
    search(tree.root, sch, &schn, &schk);
    if (schn) {
        dump_node(schn);
        printf("matched key %d\n", schk);
    }

    /*insertion*/
    sch = 21;
    printf("Inserting <%d>....\n", sch);
    insert(&tree, sch);
    dump(&tree, 0); 

    printf("Searching <%d>....\n", sch);
    search(tree.root, sch, &schn, &schk);
    if (schn) {
        dump_node(schn);
        printf("matched key %d\n", schk);
    }

    /*deletion*/
    delete(&tree, 99);
    delete(&tree, 4);
    dump(&tree, 0); 
    delete(&tree, 20);
    dump(&tree, 0);
    delete(&tree, 10);

    destroy_btree(&tree);

    return 0;
}
