#include <stdio.h>
#include "Header.h"

int main(int argc, char *argv[]) {
//int n = atoi(argv[1]);
    int n;
    if (scanf("%d", &n) != 1) {
        printf("bad input");
    }

    int arr[n];
    for (int i = 0; i < n; i++) {
//arr[i] = atoi(argv[i + 2]);
        if (scanf("%d", &arr[i]) != 1) {
            printf("bad input");
        }
    }
    quick_sort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}