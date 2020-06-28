#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "header.h"
#define MAX_VERTEXES 5000
// algorithm Prima



int main(void) {
    int countOfVertex = 0;
    int countOfEdge = 0;
    FILE* input = fopen("in.txt", "r");
    if (fscanf(input, "%d", &countOfVertex) == EOF) { printf("bad number of lines"); fclose(input);  return 0; }
    if (fscanf(input, "%d", &countOfEdge) == EOF) { printf("bad number of lines"); fclose(input);  return 0; }

    if (countOfVertex < 0 || countOfVertex > MAX_VERTEXES) { printf("bad number of vertices"); fclose(input); return 0; }
    if (countOfEdge < 0 || countOfEdge > countOfVertex* (countOfVertex - 1) / 2) { printf("bad number of edges"); fclose(input); return 0; }
    if (countOfVertex == 1 && countOfEdge == 0) { fclose(input); return 0; }
    if (countOfVertex == 0 || countOfEdge < countOfVertex - 1) { printf("no spanning tree"); fclose(input); return 0; }

    int beginVertex = 0;
    int endVertex = 0;
    int weightEdge = 0;

    int** adjMatrix;
    adjMatrix = newMatrix(countOfVertex);

    for (int i = 0; i < countOfEdge; i++) {
        if (fscanf(input, "%d", &beginVertex) == EOF || fscanf(input, "%d", &endVertex) == EOF || fscanf(input, "%d", &weightEdge) == EOF) { printf("bad number of lines"); removeMatrix(adjMatrix, countOfVertex); fclose(input); return 0; }
        if (beginVertex < 1 || beginVertex > countOfVertex || endVertex<1 || endVertex > countOfVertex) { printf("bad vertex"); removeMatrix(adjMatrix, countOfVertex); fclose(input);   return 0; }
        if (weightEdge < 0 || weightEdge > INT_MAX) { printf("bad length"); removeMatrix(adjMatrix, countOfVertex); fclose(input);  return 0; }
        adjMatrix[beginVertex - 1][endVertex - 1] = weightEdge;
        adjMatrix[endVertex - 1][beginVertex - 1] = weightEdge;

    }

    int* parent;
    parent = (int*)calloc(countOfVertex, sizeof(int));

    if (!findSpanningTree(adjMatrix, countOfVertex, parent))
        printf("no spanning tree");
    else
        printTree(parent, countOfVertex);

    removeMatrix(adjMatrix, countOfVertex);
    free(parent);
    fclose(input);
    return 0;
}
