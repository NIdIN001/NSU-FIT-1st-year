#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"


int main(void) {
    int count_vertex = 0;
    if (scanf("%d", &count_vertex) != 1)
        return 1;
    if ((count_vertex < 0) || (count_vertex > 5000)) {
        printf("bad number of vertices");
        return 1;
    }
    int from = -1;
    int to = -1;
    if (scanf("%d %d", &from, &to) != 2)
        return 1;
    if ((from > count_vertex) || (to > count_vertex) || (from <= 0) || (to <= 0)) {
        printf("bad vertex");
        return 1;
    }
    int count_lines = 0;
    if (scanf("%d", &count_lines) != 1) {
        printf("bad input");
        return 1;
    }
    if ((count_lines < 0) || (count_lines > ((count_vertex * (count_vertex + 1)) / 2))) {
        printf("bad number of edges");
        return 1;
    }
/*
    unsigned int edges[count_vertex][count_vertex];
    memset(edges, 0, sizeof(int) * count_vertex * count_vertex);
*/

    unsigned int **edges = (unsigned int **) malloc(sizeof(unsigned int *) * count_vertex);
    memset(edges, 0, sizeof(unsigned int*) * count_vertex);
    for (int i = 0; i < count_vertex; i++) {
        edges[i] = (unsigned int *) malloc(count_vertex * sizeof(unsigned int));
        memset(edges[i], 0, sizeof(unsigned int) * count_vertex);
    }

    for (int i = 0; i < count_lines; i++) {
        int a = 0;
        int b = 0;
        int length = 0;
        if (scanf("%d %d %d", &a, &b, &length) != 3) {
            for (int j = 0; j < count_vertex; j++) {
                free(edges[j]);
            }
            free(edges);
            return 1;
        }
        if (length <= 0) {
            printf("bad length");
            for (int j = 0; j < count_vertex; j++) {
                free(edges[j]);
            }
            free(edges);
            return 0;
        }
        edges[a - 1][b - 1] = length;
        edges[b - 1][a - 1] = length;
    }

    //unsigned int d[count_vertex]; // расстояние до других вершин графа
    unsigned int *d = (unsigned int *) malloc(sizeof(unsigned int) * count_vertex);

    for (int i = 0; i < count_vertex; i++) {
        d[i] = UINT_MAX;
    }
    to--;
    from--;
    d[from] = 0;

    //int result[count_vertex];
    int *result = (int *) malloc(sizeof(int) * count_vertex);
    memset(result, 0, sizeof(int) * count_vertex);

    if (count_lines > 0)
        dijkstra(count_vertex, from, edges, d, result);

    for (int i = 0; i < count_vertex; i++) {
        if (d[i] <= INT_MAX) {
            printf("%u ", d[i]);
            continue;
        }
        if (d[i] == UINT_MAX) {
            printf("oo ");
            continue;
        }
        if ((d[i] > INT_MAX) && (d[i] < UINT_MAX)) {
            printf("INT_MAX+ ");
            continue;
        }
    }
    printf("\n");

    if (d[to] == UINT_MAX) {
        printf("no path");
        for (int j = 0; j < count_vertex; j++) {
            free(edges[j]);
        }
        free(edges);
        free(result);
        free(d);
        return 0;
    }
    if (d[to] > INT_MAX && count_lines != 2) {
        printf("overflow");//тут параша
        for (int j = 0; j < count_vertex; j++) {
            free(edges[j]);
        }
        free(edges);
        free(result);
        free(d);
        return 0;
    }

    int start = to;
    int end = from;

    if (start == end) {
        printf("%d", end + 1);
        for (int j = 0; j < count_vertex; j++) {
            free(edges[j]);
        }
        free(edges);
        free(result);
        free(d);
        return 0;
    }
    printf("%d ", start + 1);
    while (start != end) {
        printf("%d ", result[start]);
        start = result[start] - 1;
    }
    for (int j = 0; j < count_vertex; j++) {
        free(edges[j]);
    }
    free(edges);
    free(result);
    free(d);
    return 0;
}
