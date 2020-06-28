#ifndef MYASO_HEADER_H
#define MYASO_HEADER_H

#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int *data;
    int size;
    int capacity;
}Vector;

void initializeVector(Vector* vector, int countOfVertex);
void pushInVector(Vector* vector, int vertex);
void sort(Vector* vector, int index, int* color_table, int* output, int* sizeOutput);
void sortGraph(Vector* vector, int countOfVertex, int starterVertex, int* output);
void printGraph(int* output, int countOfVertex);
void removeVector(Vector** vector, int countOfVertex);
#endif //MYASO_HEADER_H
