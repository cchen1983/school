#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOK_MAX 255
#define STATE_MAX 18
#define VAL_UNKNOWN -1

enum {
    TOK_DIV = 0,
    TOK_LP,
    TOK_RP,
    TOK_PL,
    TOK_MIN,
    TOK_TM,
    TOK_ASS,
    TOK_NUM,
    TOK_ID,
    TOK_SPACE,
    TOK_COMM,
    TOK_UNKNOWN 
};

typedef struct state_vector_s {
    int state[255];
    unsigned int tok;
} state_vector_t;

typedef struct token_s {
    unsigned int tok;
    char image[TOK_MAX];
} token_t;

const char* tokname[] = {
    "DIV",
    "LP",
    "RP",
    "PLUS",
    "MIN",
    "TIMES",
    "ASSIGN",
    "NUMBER",
    "ID",
    "SPACE",
    "COMMENCE"
};

/*state matrix*/
static state_vector_t sm[STATE_MAX];

static char idx(char c) {
    if (c == '\t' || c == ' '){
        c = ' ';
    }
    else if (c >= '0' && c <= '9') {
        c = '0';
    }
    else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        c = 'a';
    }
    else if (c != '\n' && c != '/' && c != '*' && c != '(' && c != ')' &&
             c != '+' && c != '-' && c != ':' && c != '=' &&
             c != '.') {
        c = 'x';  //other
    }
    return c;
}

static void sm_init() {
    int *st;
    int i;

    memset(sm, VAL_UNKNOWN, sizeof(sm));

    /*Init state machine*/
    st = sm[0].state;
    st[' '] = 17;  //space,tab
    st['\n'] = 17;
    st['/'] = 2;
    st['*'] = 10;
    st['('] = 6;
    st[')'] = 7;
    st['+'] = 8;
    st['-'] = 9;
    st[':'] = 11;
    st['.'] = 13;
    st['0'] = 14;  //digit
    st['a'] = 16; //letter
    st['x'] = VAL_UNKNOWN; //other

    st = sm[1].state;
    st['/'] = 3;
    st['*'] = 4;
    
    st = sm[2].state;
    for (i = 0; i < 255; i ++) {
        st[i] = 3;
    }
    st['\n']  = 18;

    st = sm[3].state;
    for (i = 0; i < 255; i ++) {
        st[i] = 4;
    }
    st['*'] = 5;

    st = sm[4].state;
    for (i = 0; i < 255; i ++) {
        st[i] = 4;
    }
    st['/'] = 18;
    st['*'] = 5;

    st = sm[10].state;
    st['='] = 12;

    sm[12].state['0'] = 15;

    sm[13].state['.'] = 15;
    sm[13].state['0'] = 14;

    sm[14].state['0'] = 15;

    sm[15].state['0'] = 16;
    sm[15].state['a'] = 16;

    sm[16].state[' '] = 17;
    sm[16].state['\n'] = 17;

    /*Tokens*/
    sm[1].tok = TOK_DIV;
    sm[5].tok = TOK_LP;
    sm[6].tok = TOK_RP;
    sm[7].tok = TOK_PL;
    sm[8].tok = TOK_MIN;
    sm[9].tok = TOK_TM;
    sm[11].tok = TOK_ASS;
    sm[13].tok = TOK_NUM;
    sm[14].tok = TOK_NUM;
    sm[15].tok = TOK_ID;
    sm[16].tok = TOK_SPACE;
    sm[17].tok = TOK_COMM;
}

static int next(int state, char c) {
    unsigned int st = sm[state].state[idx(c)];
    return (st == VAL_UNKNOWN) ? VAL_UNKNOWN: st - 1;
}

int main(int argc, char **argv) {
    token_t toks[1024];
    int i = 0;    
    int st = 0; //current state
    int st_prev = VAL_UNKNOWN;
    int st_next;

    char img[TOK_MAX] = {0};
    char tempbuf[TOK_MAX] = {0};
    char input[4096];

    int imgIdx, tempIdx = 0;    

    int toks_cnt = 0;
    
    strcpy(input, argv[1]);
    input[strlen(argv[1])] = '\n';
    input[strlen(argv[1]) + 1] = '\0';

    sm_init();
    memset(toks, VAL_UNKNOWN, sizeof(toks));
    while(input[i] != '\0') {
        char c = input[i++];
        
        st_next = next(st, c);
        //printf("c[%c]  cur, next: %d, %d\n", c, st+1, st_next+1);
        if (st_next == VAL_UNKNOWN) {  
            if (sm[st].tok >= TOK_UNKNOWN) {    /*error happens*/
               if (st_prev != VAL_UNKNOWN) {   /*Recognized: draw back previous valid token*/
                    toks[toks_cnt].tok = sm[st_prev].tok;

                    /*remove tempbuf from img*/
                    imgIdx -= tempIdx;

                    memcpy(toks[toks_cnt].image, img, imgIdx);
                    toks[toks_cnt].image[imgIdx] = '\0';
                    toks_cnt++;

                    i--; //push back curr char
                    i -= tempIdx; //push back tempbuf
                }
                else {  /*Error Msg, then skip curr char and continue*/
                    img[imgIdx] = '\0';
                    printf("Illegal token found: [%c] after %s\n", c, img);
                }
            }
            else {  /*Recognized*/
                toks[toks_cnt].tok = sm[st].tok;
                memcpy(toks[toks_cnt].image, img, imgIdx);
                toks[toks_cnt].image[imgIdx] = '\0';
                toks_cnt++;
                i--; //push back curr char
            }

            st = 0;
            st_prev = VAL_UNKNOWN;
            imgIdx = 0;
            tempIdx = 0;
            continue;
        }
        else if (st_next != st) {  /*move*/
            if (sm[st].tok < TOK_UNKNOWN) {
                st_prev = st;
                tempIdx = 0;
            }
            tempbuf[tempIdx++] = c; //record for push back, in case the further scanning fails.
            st = st_next; 
        }
        img[imgIdx++] = c;
    }

    /*Collect the remaining token.*/
    if (imgIdx > 0 && sm[st].tok < TOK_UNKNOWN) {
        toks[toks_cnt].tok = sm[st].tok;
        memcpy(toks[toks_cnt].image, img, imgIdx);
        toks[toks_cnt].image[imgIdx] = '\0';
        toks_cnt++;
    }

    printf("Tokens fetched:\n");
    for (i = 0; i < toks_cnt; i++) {
        printf("[%d][type: %s]: %s\n", i, tokname[toks[i].tok], toks[i].image);
    }

    return 0;
}
