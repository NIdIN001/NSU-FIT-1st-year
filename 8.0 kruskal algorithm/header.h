#ifndef INC_80_VOALS_HEADER_H
#define INC_80_VOALS_HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct edge {
    unsigned begin;
    unsigned end;
    int weight;
}Tedge;

int compare(const void *a, const void *b);
int kruskal(Tedge *ways, unsigned number_ways, unsigned number_tops, Tedge *result);

#endif //INC_80_VOALS_HEADER_H
