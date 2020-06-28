#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "header.h"

int main(void) {
    unsigned n;
    unsigned m;
    if (scanf("%u%u", &n, &m) < 2) {
        printf("bad number of lines");
        return 0;
    }
    if (n > 5000) {
        printf("bad number of vertices");
        return 0;
    }
    if (m > (n * (n + 1) / 2)) {
        printf("bad number of edges");
        return 0;
    }
    Tedge *ways = malloc(sizeof(Tedge) * m);
    if (ways == NULL) {
        return 0;
    }
    for (unsigned i = 0; i < m; i++) {
        if (scanf("%u%u%d", &ways[i].begin, &ways[i].end, &ways[i].weight) < 3) {
            printf("bad number of lines");
            free(ways);
            return 0;
        }
        if (ways[i].begin > n || ways[i].end > n) {
            puts("bad vertex");
            free(ways);
            return 0;
        }
        if (ways[i].weight < 0 || ways[i].weight > INT_MAX) {
            puts("bad length");
            free(ways);
            return 0;
        }
    }
    Tedge *result = malloc(sizeof(Tedge) * m);
    if (result == NULL) {
        free(ways);
        return 0;
    }
    int size_result = kruskal(ways, m, n, result);
    if (size_result == -1) {
        free(ways);
        free(result);
        return 0;
    }
    if (size_result + 1 < (int) n || (size_result == 0 && n == 0)) {
        puts("no spanning tree");
        free(ways);
        free(result);
        return 0;
    }
    for (int i = 0; i < size_result; ++i) {
        printf("%u %u\n", result[i].begin, result[i].end);
    }
    free(ways);
    free(result);

    return 0;
}
