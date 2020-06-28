#ifndef INC_80_VOALS_HEADER_H
#define INC_80_VOALS_HEADER_H

int **newMatrix(int count);
void removeMatrix(int **matrix, int countOfVertex);
int getMinIndex(unsigned *weightArr, char *status, int countOfVertex);
char findSpanningTree(int **graph, int countOfVertex, int *parent);
void printTree(int *parent, int countOfVertex);

#endif //INC_80_VOALS_HEADER_H
