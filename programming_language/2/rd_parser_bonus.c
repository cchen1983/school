/*
 * Recursive descent parser
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

enum {
    prog = 0,
    stmtl,
    stmt,
    expr,
    termt,
    term,
    factort,
    factor,
    addop,
    multop,
    SYM_MAX,
    id,
    num,
    read,
    write,
    assign,
    lp,
    rp,
    pls,
    min,
    mlt,
    dv,
    end,
    NONE
};

#define RULE_MAX 19

typedef struct pred_s {
    int size;
    int syms[100];
} pred_t;

typedef struct tok_s {
    unsigned int tok;
    const char *image;
} tok_t;

//emulate input token stream from scanner.
static tok_t toks[] = {
    {read, "read"}, {id, "A"},
    {read, "read"}, {id, "B"},
    {id, "sum"}, {assign, ":="}, {id, "A"}, {pls, "+"}, {id, "B"},
    {write, "write"}, {id, "sum"}, {id, "sum"}, {assign, ":="}, {id, "E"},
    {write, "write"}, {id, "sum"}, {dv, "/"}, {num, "2"}, {end, "$$"}
};
static int tok_idx = 0;

static const char * terms[NONE] = {
    "program", "stmt_list", "stmt", "expr", "term_tail", "term", "factor_tail", "factor", "add_op", "mult_op", "",
    "id", "number", "read", "write", ":=", "(", ")", "+", "-", "*", "/", "$$"
};

static pred_t pred[RULE_MAX + 1];
static unsigned int parser_tbl[SYM_MAX][NONE];

static tok_t *get_token() {
    int size = sizeof(toks) / sizeof(tok_t);

    if (tok_idx >= size) {
        return NULL;
    }

    return &toks[tok_idx++];
}

static void unget_token() {
    if (tok_idx > 0) {
        tok_idx--;
    }
}


static void rd_init() {
    int i;
    memset(pred, 0, sizeof(pred));
    memset(parser_tbl, -1, sizeof(parser_tbl));

    // products
    pred[1].size = 2;
    pred[1].syms[0] = stmtl;
    pred[1].syms[1] = end;
    pred[2].size = 2;
    pred[2].syms[0] = stmt;
    pred[2].syms[1] = stmtl;
    pred[3].size = 0;
    pred[4].size = 3;
    pred[4].syms[0] = id;
    pred[4].syms[1] = assign;
    pred[4].syms[2] = expr;
    pred[5].size = 2;
    pred[5].syms[0] = read;
    pred[5].syms[1] = id;
    pred[6].size = 2;
    pred[6].syms[0] = write;
    pred[6].syms[1] = expr;
    pred[7].size = 2;
    pred[7].syms[0] = term;
    pred[7].syms[1] = termt;
    pred[8].size = 3;
    pred[8].syms[0] = addop;
    pred[8].syms[1] = term;
    pred[8].syms[2] = termt;
    pred[9].size = 0;
    pred[10].size = 2;
    pred[10].syms[0] = factor;
    pred[10].syms[1] = factort;
    pred[11].size = 3;
    pred[11].syms[0] = multop;
    pred[11].syms[1] = factor;
    pred[11].syms[2] = factort;
    pred[12].size = 0;
    pred[13].size = 3;
    pred[13].syms[0] = lp;
    pred[13].syms[1] = expr;
    pred[13].syms[2] = rp;
    pred[14].size = 1;
    pred[14].syms[0] = id;
    pred[15].size = 1;
    pred[15].syms[0] = num;
    pred[16].size = 1;
    pred[16].syms[0] = pls;
    pred[17].size = 1;
    pred[17].syms[0] = min;
    pred[18].size = 1;
    pred[18].syms[0] = mlt;
    pred[19].size = 1;
    pred[19].syms[0] = dv;

    // parser table
    parser_tbl[prog][id] = 1;
    parser_tbl[prog][read] = 1;
    parser_tbl[prog][write] = 1;
    parser_tbl[prog][end] = 1;
    parser_tbl[stmtl][id] = 2;
    parser_tbl[stmtl][read] = 2;
    parser_tbl[stmtl][write] = 2;
    parser_tbl[stmtl][end] = 3;
    parser_tbl[stmt][id] = 4;
    parser_tbl[stmt][read] = 5;
    parser_tbl[stmt][write] = 6;
    parser_tbl[expr][id] = 7;
    parser_tbl[expr][num] = 7;
    parser_tbl[expr][lp] = 7;
    parser_tbl[termt][id] = 9;
    parser_tbl[termt][read] = 9;
    parser_tbl[termt][write] = 9;
    parser_tbl[termt][rp] = 9;
    parser_tbl[termt][pls] = 8;
    parser_tbl[termt][min] = 8;
    parser_tbl[termt][end] = 9;
    parser_tbl[term][id] = 10;
    parser_tbl[term][num] = 10;
    parser_tbl[term][lp] = 10;
    parser_tbl[factort][id] = 12;
    parser_tbl[factort][read] = 12;
    parser_tbl[factort][write] = 12;
    parser_tbl[factort][rp] = 12;
    parser_tbl[factort][pls] = 12;
    parser_tbl[factort][min] = 12;
    parser_tbl[factort][mlt] = 11;
    parser_tbl[factort][dv] = 11;
    parser_tbl[factort][end] = 12;
    parser_tbl[factor][id] = 14;
    parser_tbl[factor][num] = 15;
    parser_tbl[factor][lp] = 13;
    parser_tbl[addop][pls] = 16;
    parser_tbl[addop][min] = 17; 
    parser_tbl[multop][mlt] = 18;
    parser_tbl[multop][dv] = 19;

}


int main(int argc, char **argv) {
    char img[1024];
    unsigned int idx = 0;
    void *st = stack_new(1024);
    int error = 0;
    int sym, curr_symb;

    rd_init();
    memset(img, 0, 1024);
    printf("Input program: \n");
    
    stack_push(st, prog);  // init symbol
    curr_symb = prog;
    while (1) {
        tok_t *t = get_token();
        unsigned int r;

        if (!t) {
            break;
        }

        if (stack_pop(st, &sym) < 0) {
            printf("redundance after full syntax: %s\n", img);
            error = 1;
            break;
        }    
        //printf("sym: %s, tok: %s, img: %s\n", terms[sym], terms[t->tok], t->image);
        if (sym > SYM_MAX) {    // terminal
            printf("sym, tok: %s, %s\n", terms[sym], t->image);
            if (t->tok != sym) { // mimatch
                printf("error symbol[%s]: illegal tok '%s'. after: %s\n", terms[curr_symb], t->image, img);
                error = 1;
                break; 
            }
            strcpy(img + idx, t->image);
            idx += strlen(t->image);
            img[idx++] = ' ';
            img[idx] = '\0';           
        }
        else {  // non-terminal
            curr_symb = sym;
            r = parser_tbl[sym][t->tok];
            printf("sym, tok, r: %s %s %d\n", terms[sym], t->image, r);
            if (r >= RULE_MAX + 1) {    // error
                printf("error symbol[%s]: illegal tok '%s'. after: %s\n", terms[sym], t->image, img);
                error = 1;
                break;
            }
            else {
                pred_t product = pred[r];
                int i;
                for (i = product.size - 1; i >= 0; i--) {
                    stack_push(st, product.syms[i]);  // push next symbol or terminal
                }
                unget_token();  // push back for fully token matching         
            }
        }
    }

    if (error == 0) {
        if (stack_pop(st, &sym) == 0) {  // error or stack is not empty.
            printf("unexpected eof: %s\n", img);
        }
        else {
            printf("Syntax Correct!\n");
        }
    }

    stack_del(st);
    return 0;
}
