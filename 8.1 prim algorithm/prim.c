#include <stdlib.h>
#include <stdio.h>
#include "header.h"
#include <limits.h>
int **newMatrix(int count)
{
    int **matrix;
    matrix = (int **)calloc(count, sizeof(int *));
    for (int i = 0; i < count; i++)
    {
        matrix[i] = (int *)calloc(count, sizeof(int));
    }
    return matrix;
}

void removeMatrix(int **matrix, int countOfVertex)
{
    for (int i = 0; i < countOfVertex; i++)
        free(matrix[i]);
    free(matrix);
}

int getMinIndex(unsigned *weightArr, char *status, int countOfVertex)
{
    unsigned min = (unsigned)INT_MAX + 1;
    int minIndex = -1; // First vertex don't have parent, is begin
    for (int i = 0; i < countOfVertex; i++)
    {
        if (status[i] == 0 && min > weightArr[i])
        {
            min = weightArr[i];
            minIndex = i;
        }
    }
    return minIndex;
}

char findSpanningTree(int **graph, int countOfVertex, int *parent)
{
    char *status;
    unsigned *weightArr;

    status = (char *)calloc(countOfVertex, sizeof(char));
    weightArr = (unsigned *)calloc(countOfVertex, sizeof(unsigned));

    for (int i = 0; i < countOfVertex; i++)
    {
        weightArr[i] = (unsigned)INT_MAX + 1;
        status[i] = 0;
    }

    weightArr[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < countOfVertex - 1; i++)
    {
        int minIndex = getMinIndex(weightArr, status, countOfVertex);
        status[minIndex] = 1;

        for (int j = 0; j < countOfVertex; j++)
            if (graph[minIndex][j] && status[j] == 0 && (unsigned)graph[minIndex][j] < weightArr[j])
            {
                parent[j] = minIndex;
                weightArr[j] = graph[minIndex][j];
            }
    }

    for (int i = 0; i < countOfVertex; i++)
        if (weightArr[i] == (unsigned)INT_MAX + 1)
        {
            printf("no spanning tree");
            free(weightArr);
            free(status);
            return 0;
        }

    free(weightArr);
    free(status);
    return 1;
}

void printTree(int *parent, int countOfVertex)
{
    for (int i = 1; i < countOfVertex; i++)
    { // loop begin from 1, because first vertex don't have parent
        printf("\n%d ", parent[i] + 1);
        printf("%d", i + 1);
    }
}
