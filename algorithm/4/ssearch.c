#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * KMP Search
 * */
static int * build_kmp_tbl(const char *pattern) {
    int len = strlen(pattern);
    int *tbl = malloc(len * sizeof(int));

    if (tbl) {
        int m = 1;
        int cd = 0;     //candidate

        tbl[0] = -1;    //Always invalid in kmp mapping
        tbl[1] = 0;     //start mapping next

        while (m < len - 1) {
            if (cd == -1 || pattern[cd] == pattern[m]) {
                tbl[++m] = ++cd;     //init the candidate of next position
            }
            else {  //update current candidate
                cd = tbl[cd];
            }
        }
    }
    return tbl;
}

/*return the offset of matched content, or else return -1*/
static int __kmp(const char *s, const char *p, int *tbl) {
    int is = 0;
    int ip = 0;
    int ls = strlen(s);
    int lp = strlen(p);

    while ( (ls - is) >= (lp - ip) ) {
        if (ip == -1 || s[is] == p[ip]) {
            is++;
            ip++;
        }
        else {
            ip = tbl[ip];   //try the candidate
        }

        if (ip == lp) {
            return is - lp;  // offset of matched string
        }
    }

    return -1;
}

/*return the count of matching*/
static int kmp(const char *s, const char *p) {
    int *tbl = build_kmp_tbl(p);
    int cnt = 0;
    int lp = strlen(p);
    int ls = strlen(s);

    if (!tbl) {
        printf("Fail to build kmp table!\n");
        return 0;
    }

    while (ls >= lp) {
        int offset = __kmp(s, p, tbl);
        if (offset == -1) {
            break;
        }
    
        s += offset + lp;
        ls -= offset + lp;
        cnt++;
    }
    free(tbl);
    return cnt;
}


/*
 * Horspool Searching
 * */
static int hspool[256];

static void build_horspool(const char *p) {
    int l = strlen(p);
    int i;

    for (i = 0; i < 256; i++) {
        hspool[i] = l;
    }

    for (i = 0; i < l - 1; i++) {
        hspool[p[i]] = l - i - 1; //Update the shift distance
    }
}

/*return offset if found, or else return -1*/
static int __horspool(const char *s, const char *p) {
    int lp = strlen(p);
    int ls = strlen(s);
    int tail = lp - 1;
    int cnt = 0;

    while (tail < ls) {
        while (s[tail - cnt] == p[lp - cnt - 1]) {
            cnt++;
            if (cnt == lp) {
                return tail - cnt + 1;
            }
        }
    
        //printf("<%d> <+%d>\n", s[tail], hspool[s[tail]]);

        /*
        * NOTE ! the source string may contains ext ascii code which is negative 
        * in signed char type. That case will cause overflowed index of hspool..
        * So I transfer it to unsigned type..
        * */
        tail += hspool[(unsigned char)s[tail]];   //mismatch, shift next candidate to tail
        cnt = 0;
    }
    return -1;
}

/*return matched count*/
static int horspool(const char *s, const char *p) {
    int offset;
    int lp = strlen(p);
    int ls = strlen(s);
    int cnt = 0;

    build_horspool(p);
    while (ls >= lp) {
        offset = __horspool(s, p);
        if (offset == -1) {
            break;
        }

        cnt++;
        s += offset + lp;
        ls -= offset + lp;
    }
    return cnt;
}

static char * read_file_to_buf(FILE *fp) {
    long size;
    char *buf = NULL;

    if (fseek(fp, 0, SEEK_END) == 0) {
        size = ftell(fp);
        if (size > 0) {
            buf = malloc(size + 1);
            if (!buf) {
                printf("fail to alloc file buffer.");
            }
            else {
                memset(buf, 0, size + 1);
                fseek(fp, 0, SEEK_SET);
                fread(buf, size, 1, fp);
            }   
        }
    }
    return buf;
}

int main(int argc, char **argv) {
    char *s = NULL;
    char *p = NULL;

    if (argc != 4) {
        printf("illegal args: ./kmp <f or s> <source> <pattern>\n");
        return -1;
    } 

    if (strcmp(argv[1], "f") == 0) {
        FILE *f = fopen(argv[2], "r");
        if (!f) {
            perror("fail to read from file: ");
            return -1;
        }
        
        s = read_file_to_buf(f);
        fclose(f);
    }
    else {
        s = strdup(argv[2]);
    }
    
    p = argv[3];

    if (!s) {
        return -1;
    }

    printf("[KMP] Total matched items: %d\n", kmp(s, p));
    printf("[Horspool] Total matched items: %d\n", horspool(s, p));

    free(s);
    return 0;    
}
