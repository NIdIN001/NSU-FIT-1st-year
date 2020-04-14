#include "header.h"

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