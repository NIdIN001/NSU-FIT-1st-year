#include "header.h"


void initializeVector(Vector* vector, int countOfVertex) {
    for (int i = 0; i < countOfVertex; i++) {
        vector[i].capacity = 10;
        vector[i].size = 0;
        vector[i].data = (int*)calloc(10, sizeof(int));
    }
}

void pushInVector(Vector* vector, int vertex) {
    if (vector->capacity < vector->size + 1) {
        vector->capacity = vector->capacity + 10;
        vector->data = (int*)realloc(vector->data, sizeof(int) * vector->capacity);
    }
    vector->data[vector->size] = vertex;
    vector->size++;
}


void sort(Vector* vector, int index, int* color_table, int* output, int* sizeOutput) {
    color_table[index] = 1;

    for (int i = 0; i < vector[index].size; i++) {
        if (color_table[vector[index].data[i]] == 2)
            break;
        if (color_table[vector[index].data[i]] == 1) {
            printf("impossible to sort");
            exit(EXIT_SUCCESS);
        }

        if (color_table[vector[index].data[i]] == 0)
            sort(vector, vector[index].data[i], color_table, output, sizeOutput);


    }

    color_table[index] = 2;
    output[*sizeOutput] = index + 1;
    *sizeOutput = *sizeOutput + 1;
}

void sortGraph(Vector* vector, int countOfVertex, int starterVertex, int* output) {
    int* color_table;
    color_table = (int*)calloc(countOfVertex, sizeof(int));

    int sizeOutput = 0;
    sort(vector, starterVertex, color_table, output, &sizeOutput);

    for (int i = 0; i < countOfVertex; i++) {
        if (color_table[i] == 0 && i != starterVertex && color_table[i] != 2)
            sort(vector, i, color_table, output, &sizeOutput);
    }

    free(color_table);
}

void printGraph(int* output, int countOfVertex) {
    for (int i = countOfVertex - 1; i >= 0; i--)
        printf("%d ", output[i]);
}

void removeVector(Vector** vector, int countOfVertex) {
    for (int i = 0; i < countOfVertex; i++)
        free((*vector)[i].data);

    free(*vector);
}

