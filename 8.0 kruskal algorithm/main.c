#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include "header.h"
/*
typedef struct Node{
    int fp;
    int sp;
    int leight;
}Tnode;

struct frame{
    int is_ok;
    int count;
};

int compare(const void* a, const void* b) {
    return ((((Tnode *) a)->leight) - (((Tnode *) b)->leight));
}

struct frame frame(Tnode edges[],Tnode out[], int lines, int vertex) {

    qsort(edges, lines, sizeof(Tnode), compare);

    int color[vertex];
    for (int i = 0; i < vertex; i++) {
        color[i] = i;
    }

    int count = 0;

    for (int i = 0; i < lines; i++) {
        if (color[edges[i].fp-1] != color[edges[i].sp-1]) {
            out[count] = edges[i];
            count++;
            for (int j = 0; j < vertex; j++) {
                if (color[j] == color[edges[i].sp-1]) {
                    color[j] = color[edges[i].fp-1];
                }
            }
        }
    }
    int is_ok = 0;
    for (int i = 0; i < vertex - 1; i++) {
        for (int j = i; j < vertex; j++) {
            if (color[i] != color[j]) {
                is_ok++;
            }
        }
    }
    struct frame ret;
    ret.count = count;
    ret.is_ok = is_ok;
    return ret;
}
*/
int main() {
    int vertex = 0;
    if (scanf("%d", &vertex) != 1) {
        return 1;
    }
    int lines = 0;
    if (scanf("%d", &lines) != 1) {
        return 1;
    }

    if ((vertex < 0) || (vertex > 5000)) {
        printf("bad number of vertices");
        return 1;
    }
    if ((lines < 0) || (lines > ((vertex * (vertex + 1)) / 2))) {
        printf("bad number of edges");
        return 1;
    }

    Tnode edges[lines];
    memset(edges, 0, sizeof(Tnode) * lines);

    for (int i = 0; i < lines; i++) {
        if (scanf("%d%d%d", &edges[i].fp, &edges[i].sp, &edges[i].leight) != 3) {
            printf("bad number of lines");
            return 1;
        }
        if ((edges[i].leight < 0) || (edges[i].leight > INT_MAX)) {
            printf("bad length");
            return 1;
        }
        if ((edges[i].fp < 1) || (edges[i].fp > vertex) || (edges[i].sp < 1) || (edges[i].sp > vertex)) {
            printf("bad vertex");
            return 1;
        }
    }

    Tnode out[lines];
    memset(out, 0, sizeof(Tnode) * lines);
    struct frame ret = frame(edges, out, lines, vertex);

    if (ret.is_ok == 0) {
        for (int i = 0; i < ret.count; i++) {
            printf("%d %d\n", out[i].fp, out[i].sp);
        }
    } else {
        printf("no spanning tree");
        return 0;
    }
}
