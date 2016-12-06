#include "utils.h"

enum {
    LCH = 0,
    RCH,
    PARENT,
    LIMIT 
};

typedef struct stat_s {
    char c;         //character code
    unsigned int w; //weight
} stat_t;

typedef struct hfnode_s { /*huffman tree node*/
    unsigned int w;
    int relatives[LIMIT]; 
} hfnode_t;

static int stat(const char *s, stat_t *st) {
    int cnt = 0; /*cnt for each appeared characters */

    while (*s) {
        int i = 0;

        if (cnt != 0) {
            for (i = 0; i < cnt; i++) {
                if (st[i].c == *s) {
                    break;
                }       
            }
        }

        st[i].w++;
        if (i == cnt) {
            st[i].c = *s;
            cnt++;
        }
        s++;
    }

    return cnt;
}

/*generating the huffman tree and huffman codes*/
static int hftree(stat_t *st, int size, hfnode_t *hn) {
    int cnt = size;  /*cnt for huffman nodes*/
    int hsize = size;  /*remaining items to be fixed in tree*/
    int i;

    while (hsize > 0) {
        int p1 = INF;   //pickup the lightest character
        int p2 = INF;   //pickup which is only larger than p1
        unsigned int w1 = INF; 
        unsigned int w2 = INF;            
        
        for (i = 0; i < cnt; i++) {
            if (hn[i].relatives[PARENT] != INF) { /*Have a parent, already fixed in tree*/
                continue;
            }

            if (w1 > st[i].w) {
                if (w1 != INF && w2 > w1 ) {
                    w2 = w1;
                    p2 = p1;
                } 
                w1 = st[i].w;
                p1 = i;
            }
            else if (w2 > st[i].w) {
                w2 = st[i].w;
                p2 = i;
            }
        }
        
        /*Move the two or one items to huffman tree and generate a parent for them*/
        if (p1 != INF && p2 != INF) {
            hn[p1].w = w1;            
            hn[p2].w = w2;

            /*add a parent node*/
            hn[cnt].w = w1 + w2;
            hn[cnt].relatives[LCH] = p1;
            hn[cnt].relatives[RCH] = p2;
            hn[cnt].relatives[PARENT] = INF;
            
            hn[p1].relatives[PARENT] = cnt;
            hn[p2].relatives[PARENT] = cnt;            

            if (hsize > 2) {
                st[cnt].c = INF;
                st[cnt].w = hn[cnt].w;
                hsize--;  /*Remove 2 and add the new one back to waitinglist*/
            }
            else {
                /*all nodes were fixed to a root*/
                hsize -= 2;
            }
        }
        else {
            /*Only one item, directly add a root and done*/
            hn[cnt].w = w1;
            hn[cnt].relatives[LCH] = p1;
            hn[cnt].relatives[RCH] = INF;
            hn[cnt].relatives[PARENT] = INF; 
            
            hn[p1].relatives[PARENT] = cnt;

            hsize--;
        }

        cnt++;
    }
    
    /*Generate huffman codes*/
    printf("#Huffman codes : \n");
    for (i = 0; i < size; i++) {
        int parent = hn[i].relatives[PARENT];
        char code[256] = {0};
        int pos = 254;

        while (parent !=  INF) {
            if (hn[parent].relatives[LCH] == i) {
                code[pos--] = '0' + LCH;        
            }
            else {
                code[pos--] = '0' + RCH;
            }
            parent = hn[parent].relatives[PARENT];
        }
        printf("Character[%c] = %s, weight = %d\n", st[i].c, &code[pos + 1], st[i].w);
    }

    return cnt;
}

static void encode(const char *s, stat_t *st) {
    /*TBD*/
}

int main(int argc, char **argv) {
    int size, len;
    stat_t *st = NULL;
    hfnode_t *hn = NULL;

    if (argc != 2) {
        printf("Please input the message!\n");
        return -1;
    }

    len = (strlen(argv[1]) * 2 + 1);
    st = malloc(len * sizeof(stat_t));
    hn = malloc(len * sizeof(hfnode_t));
    if (!st || !hn) {
        printf("Fail to alloc buffers!\n");
        if (!st)
            free(st);
        if (!hn)
            free(hn);
        return -1;
    }

    memset(st, 0, len * sizeof(stat_t));
    memset(hn, INF, len * sizeof(hfnode_t));

    size = stat(argv[1], st);
    
    hftree(st, size, hn);
    encode(argv[1], st);

    free(st);
    free(hn);

    return 0;
}
