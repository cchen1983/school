/*
 * Recursive descent parser
 *
 * S > AB
 * A > aC
 * B > -b | *(AB)
 * C > null | +aC
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

enum {
    SYM_S = 0,
    SYM_A,
    SYM_B,
    SYM_C,
    SYM_MAX,
    TERM_a,
    TERM_b,
    TERM_pls,
    TERM_min,
    TERM_ast,
    TERM_lp,
    TERM_rp,
    NONE
};

enum {
    RULE_1 = 0,     // S > AB
    RULE_2,         // A >aC
    RULE_3,         // B > -b
    RULE_4,         // B > *(AB)
    RULE_5,         // C > null
    RULE_6,         // C > +aC
    RULE_MAX
};

typedef struct pred_s {
    int size;
    int syms[100];
} pred_t;

static unsigned char term[NONE + 1] = {
    'S', 'A', 'B', 'C', 0,
    'a', 'b', '+', '-', '*', '(', ')', (unsigned char)EOF
};

static pred_t pred[RULE_MAX];
static unsigned int parser_tbl[SYM_MAX][256];

static unsigned int sym_idx(unsigned char c) {
    int i;
    for (i = 0; i < NONE; i++) {
        if (c == term[i]) {
            return i;
        }
    }
    return NONE;
}

static void rd_init() {
    int i;
    memset(pred, 0, sizeof(pred));
    memset(parser_tbl, -1, sizeof(parser_tbl));

    // products
    pred[RULE_1].syms[0] = SYM_A;
    pred[RULE_1].syms[1] = SYM_B;
    pred[RULE_1].syms[2] = NONE;
    pred[RULE_1].size = 3;

    pred[RULE_2].syms[0] = TERM_a;
    pred[RULE_2].syms[1] = SYM_C;
    pred[RULE_2].size = 2;

    pred[RULE_3].syms[0] = TERM_min;
    pred[RULE_3].syms[1] = TERM_b;
    pred[RULE_3].size = 2;

    pred[RULE_4].syms[0] = TERM_ast;
    pred[RULE_4].syms[1] = TERM_lp;
    pred[RULE_4].syms[2] = SYM_A;
    pred[RULE_4].syms[3] = SYM_B;
    pred[RULE_4].syms[4] = TERM_rp;
    pred[RULE_4].size = 5;

    pred[RULE_5].size = 0;

    pred[RULE_6].syms[0] = TERM_pls;
    pred[RULE_6].syms[1] = TERM_a;
    pred[RULE_6].syms[2] = SYM_C;
    pred[RULE_6].size = 3;

    // parser table
    parser_tbl[SYM_S]['a'] = RULE_1;
    parser_tbl[SYM_A]['a'] = RULE_2;
    parser_tbl[SYM_B]['-'] = RULE_3;
    parser_tbl[SYM_B]['*'] = RULE_4;

    parser_tbl[SYM_C]['-'] = RULE_5;
    parser_tbl[SYM_C]['*'] = RULE_5;
    parser_tbl[SYM_C]['+'] = RULE_6; 
}


int main(int argc, char **argv) {
    unsigned char img[1024];
    unsigned int idx = 0;
    void *st = stack_new(1024);
    int error = 0;
    int sym, curr_symb;
    char c = 0;

    rd_init();
    memset(img, 0, 1024);
    printf("Please input a program: \n");
    
    stack_push(st, SYM_S);  // init symbol
    curr_symb = SYM_S;
    while (1) {
        unsigned int r;

        if (c != EOF) { // Peek 
            c = getc(stdin);
            if (c == ' ' || c == '\t' || c == '\n') {
                continue;   // skip white space
            }

            if (c != EOF) 
                ungetc(c, stdin); //just peek
        }
        
        if (stack_pop(st, &sym) < 0) {
            printf("stack couldn't be empty before escape out, check algorithm."); 
            error = 1;
            break;
        }
    
        if (sym > SYM_MAX) {    // terminal

            if (sym_idx(c) != sym) { // mimatch
                printf("match error symbol[%c]: illegal char '%c(%d)'. after: %s\n", term[curr_symb], c, c, img);
                error = 1;
                break; 
            }

            getc(stdin); // match success, consume it
            img[idx++] = c; 
            if (c == EOF) {
                break;  // Parser Success!
            }           
        }
        else {  // non-terminal
            curr_symb = sym;
            r = parser_tbl[sym][(unsigned char)c];
            if (r >= RULE_MAX) {    // error
                printf("pred error symbol[%c]: illegal char '%c(%d)'. after: %s\n", term[sym], c, c, img);
                error = 1;
                break;
            }
            else {
                pred_t product = pred[r];
                int i;
                for (i = product.size - 1; i >= 0; i--) {
                    stack_push(st, product.syms[i]);  // push next symbol or terminal
                }
            }
        }
    }

    if (error == 0) {
        printf("Syntax Correct!\n");
    }

    stack_del(st);
    return 0;
}
