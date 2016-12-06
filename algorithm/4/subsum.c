#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TARGET 32

static void dump(int univ[], char sel[], int size) {
    int i;
    printf("subset: ");
    for (i = 0; i < size; i++) {
        if (sel[i] == 1) {
            printf("%d  ", univ[i]);
        }
    }
    printf("\n");
}

static char is_valid(int univ[], char sel[], int size, int br) {
    int curr = 0;
    int resd = 0;
    int i;

    for (i = 0; i <= br; i++) {
        if (sel[i] == 1) {
            curr += univ[i];
        }
    }

    if (curr > TARGET) {
        return 0;
    }

    for (i = br + 1; i < size; i++) {
        resd += univ[i];
    }

    if (curr + resd < TARGET) {
        return 0;
    }
    return 1;
}

static void subsum(int univ[], char sel[], int size, int br) {
    if (br >= size) {
        return;    
    }

    sel[br] = 0;    //starting a new track
    while (sel[br] < 2) { //selected or unselected
        if (is_valid(univ, sel, size, br)) {
            if (br == size - 1) {
                /*get it.*/
                dump(univ, sel, size);
            }
            else {
                /*keep tracking*/
                subsum(univ, sel, size, br + 1);
            }
        }
        sel[br]++;  /*try next branch*/
    }
}

int main(int argc, char **argv) {
    int univ[] = {4, 6, 8, 8, 10, 3, 18, 24, 9, 8, 10, 5};
    int size = sizeof(univ) / sizeof(univ[0]);
    char *sel = malloc(size);
    int i;
    
    if (!sel) {
        printf("fail to alloc buf!\n");
        return -1;
    } 
    
    memset(sel, 0, size);
    printf("univeral set: ");
    for (i = 0; i < size; i++) {
        printf("%d  ", univ[i]);
    }    
    printf("\n");

    subsum(univ, sel, size, 0); 

    free(sel);
    return 0;
}
