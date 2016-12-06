#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct enclosing_s {
    char lchar;
    char rchar;
} enclosing_t;

enclosing_t enclosings[3] = {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

enum {
    LCHAR = 0,
    RCHAR,
    NONE
};

static int is_enc_char(char c) {
    int i;
    for (i = 0; i < (sizeof(enclosings) / sizeof(enclosing_t)); i++) {
        enclosing_t *e = &enclosings[i];
        if (c == e->lchar) {
            return LCHAR;
        }
        else if (c == e->rchar) {
            return RCHAR;
        }
    }
    return NONE;
}

static char get_rchar(char lc) {
    int i;
    for (i = 0; i < (sizeof(enclosings) / sizeof(enclosing_t)); i++) {
        enclosing_t *e = &enclosings[i];
        if (lc == e->lchar) {
            return e->rchar;
        }
    }
    return 0;
}

static int get_enclosing(const char *s, char rc, int len) {
    int i = 1;

    while (i < len) {
        int res;
        if (s[i] == rc) {
            char str[255];
            memcpy(str, s, i + 1);
            str[i + 1] = '\0';
            printf("%s\n", str);
            return i + 1;
        }

        res = is_enc_char(s[i]);
        if (res == LCHAR) {
            /*sub enclosing*/
            int offset = get_enclosing(&s[i], get_rchar(s[i]), len - i);
            if (offset < 0) {
                printf("Invalid enclosing for %c\n", s[i]);
                break;
            }
            else {
                i += offset;
            }
        }
        else if (res == RCHAR) {
            /*mismatch ending*/
            break;
        }
        else {
            i++;
        }
    }

    return -1; /*failed*/
}

int main(int argc, char **argv) {
    const char *in = argv[1];
    unsigned int pos = 0; 
    int length;

    if (!in) {
        printf("Please input a string.");
        return 1;
    }
    
    length = strlen(in);
    while (pos < length) {
        char rc = 0;

        while (pos < length) {
            rc = get_rchar(in[pos]);
            if (rc != 0) {  /*got an enclosing starting*/
                break;
            }
            pos++;
        }
 
        if (pos < length) {
            /*Validation*/
            int offset = get_enclosing(&in[pos], rc, length - pos);
            if (offset < 0) {
                printf("Invalid enclosing for %c\n", in[pos]);
                return 1;
            }
            
            pos += offset;
        }
    }

    printf("All enclosings are Valid !\n");
    return 0;
}
