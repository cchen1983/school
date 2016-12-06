#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INF (-1)   //Infinite

#define DEBUG

#ifdef DEBUG
#define log(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define log(fmt, ...)
#endif
