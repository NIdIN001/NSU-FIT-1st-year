//
// Created by Станислав Уточкин on 14.04.2020.
//

#ifndef LABA8_0_HEADER_H
#define LABA8_0_HEADER_H

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

typedef struct Node{
    int fp;
    int sp;
    int leight;
}Tnode;

struct result{
    int is_ok;
    int count;
};

int compare(const void* a, const void* b);
struct result frame(Tnode edges[],Tnode out[], int lines, int vertex);

#endif //LABA8_0_HEADER_H
