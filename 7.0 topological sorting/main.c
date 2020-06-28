#include <stdlib.h>
#include <stdio.h>
#include "header.h"

int main(void) {
    int countOfVertex = 0;
    int countOfEdge = 0;

    if (scanf("%d", &countOfVertex) == EOF) {
        printf("bad number of lines");
        return 0;
    }
    if (scanf("%d", &countOfEdge) == EOF) {
        printf("bad number of lines");
        return 0;
    }

    if (countOfVertex < 0 || countOfVertex > 1000) {
        printf("bad number of vertices");
        return 0;
    }
    if (countOfEdge < 0 || countOfEdge > countOfVertex * (countOfVertex - 1) / 2) {
        printf("bad number of edges");
        return 0;
    }

    Vector *vector = (Vector *) calloc(countOfVertex, sizeof(Vector));
    initializeVector(vector, countOfVertex);

    int beginVertex = 0;
    int endVertex = 0;
    int starterVertex = 0;
    for (int i = 0; i < countOfEdge; i++) {
        if (scanf("%d", &beginVertex) == EOF || scanf("%d", &endVertex) == EOF) {
            printf("bad number of lines");
            removeVector(&vector, countOfVertex);
            return 0;
        }
        if (beginVertex < 1 || beginVertex > countOfVertex || endVertex < 1 || endVertex > countOfVertex) {
            printf("bad vertex");
            removeVector(&vector, countOfVertex);
            return 0;
        }
        if (i == 0)
            starterVertex = beginVertex - 1;

        pushInVector(&vector[beginVertex - 1], endVertex - 1);
    }
    int *output;
    output = (int *) calloc(countOfVertex, sizeof(int));

    sortGraph(vector, countOfVertex, starterVertex, output);
    printGraph(output, countOfVertex);

    free(output);
    removeVector(&vector, countOfVertex);
    return 0;
}
