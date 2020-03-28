#include <stdio.h>
#include "header.h"

int main(int argc, char** argv) {
    int count;
    FILE *input = fopen("input.txt", "rt");
    if (input == NULL) {
        if (fscanf(stdin, "%d", &count) != 1)
            return 0;
    } else {
        if (fscanf(stdin, "%d", &count) != 1)
            return 0;
    }
    int array[count];
    if (input == NULL) {
        for (int i = 0; i < count; i++) {
            if (fscanf(stdin, "%d", &array[i]) != 1)
                return 0;
        }
    } else {
        for (int i = 0; i < count; i++) {
            if (fscanf(input, "%d", &array[i]) != 1)
                return 0;
        }
    }
    heapSort(array, count);
    for (int i = 0; i < count; i++)
        printf("%d ", array[i]);
}