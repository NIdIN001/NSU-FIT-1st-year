#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstra.c"

int main() {
    char input[11];
    if (scanf("%10s", input) != 1) {
        printf("bad input");
    }

    size_t size = strlen(input);
    int arr[size];

    for (size_t i = 0; i < size; i++) arr[i] = input[i] - 48;

    bad_input_check(arr, size);

    int n = 0;
    if (scanf("%d", &n) != 1) {
        printf("bad input");
    }

    while (n != 0) {
        dijkstra(arr, size);
        n--;
        for (size_t i = 0; i < size; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}
