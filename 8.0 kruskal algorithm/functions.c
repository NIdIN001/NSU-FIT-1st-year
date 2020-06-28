#include "header.h"

int compare(const void *a, const void *b) {
    return ((const Tedge *) a)->weight - ((const Tedge *) b)->weight;
}

int kruskal(Tedge *ways, unsigned number_ways, unsigned number_tops, Tedge *result) {
    qsort(ways, number_ways, sizeof(Tedge), compare);
    unsigned *colour = malloc(sizeof(unsigned) * (number_tops + 1));
    if (colour == NULL) {
        return -1;
    }
    for (unsigned i = 0; i <= number_tops; ++i) {
        colour[i] = i;
    }
    int size_result = 0;
    for (unsigned i = 0; i < number_ways; ++i) {
        if (colour[ways[i].begin] != colour[ways[i].end]) {
            result[size_result] = ways[i];
            ++size_result;
            unsigned new_colour = colour[ways[i].begin];
            unsigned old_colour = colour[ways[i].end];
            for (unsigned j = 0; j <= number_tops; ++j) {
                if (colour[j] == old_colour) {
                    colour[j] = new_colour;
                }
            }
        }
    }
    free(colour);
    return size_result;
}
