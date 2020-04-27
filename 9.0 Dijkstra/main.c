#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "header.h"

int main() {
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


    unsigned int edges[count_vertex][count_vertex];
    memset(edges, 0, sizeof(int) * count_vertex * count_vertex);

    for (int i = 0; i < count_lines; i++) {
        int a = 0;
        int b = 0;
        int length = 0;
        if (scanf("%d %d %d", &a, &b, &length) != 3)
            return 1;
        if (length <= 0) {
            printf("bad length");
        }
        edges[a - 1][b - 1] = length;
        edges[b - 1][a - 1] = length;
    }

    unsigned int d[count_vertex]; // расстояние до других вершин графа
    for (int i = 0; i < count_vertex; i++) {
        d[i] = INT_MAX * 2 + 1;
    }
    to--;
    from--;
    d[from] = 0;

    int result[count_vertex];
    memset(result, 0, sizeof(int) * count_vertex);

    dijkstra(count_vertex, from, edges, d, result);

    for (int i = 0; i < count_vertex; i++) {
        if (d[i] <= INT_MAX) {
            printf(" %u", d[i]);
            continue;
        }
        if (d[i] == INT_MAX * 2 + 1) {
            printf(" oo");
            continue;
        }
        if ((d[i] > INT_MAX) && (d[i] < INT_MAX * 2 + 1)) {
            printf(" INT_MAX+");
            continue;
        }
    }
    printf("\n");

    if (d[to] == INT_MAX * 2 + 1) {
        printf("no path");
        return 0;
    }
    if (d[to] > INT_MAX) {
        printf("overflow");//тут параша
        return 0;
    }


    int current_place = to;
    printf(" %d", to + 1);
    while (current_place != result[from]) {
        printf(" %d", result[current_place]);
        current_place = result[current_place] - 1;
    }
}
