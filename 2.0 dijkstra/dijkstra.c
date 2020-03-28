void swap(int *x, int *y){
    int tmp=*x;
    *x=*y;
    *y=tmp;
}
void bad_input_check(int* arr, int size) {
    if (size > 10) {
        printf("bad input");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                printf("bad input");
                exit(EXIT_FAILURE);
            }
        }
    }
    for (int i = 0; i < size; i++) {
        if (arr[i] > 9) {
            printf("bad input");
            exit(EXIT_FAILURE);
        }
    }
}
void dijkstra(int* arr, size_t size) {
    int pivot = -1;
    size_t pivot_place = 0;
    int min = 10;
    size_t min_place = 0;

    for (size_t i = size - 1; i > 0; i--) {
        if (arr[i - 1] < arr[i]) {
            pivot = arr[i - 1];
            pivot_place = i - 1;
            break;
        }
    }

    if (pivot == -1)
        exit(EXIT_SUCCESS);

    for (size_t i = pivot_place + 1; i < size; i++) {
        if ((arr[i] > pivot) && (arr[i] < min)) {
            min = arr[i];
            min_place = i;
        }
    }

    swap(&arr[pivot_place], &arr[min_place]);

    size_t suf_size = size - pivot_place - 1;
    int n = 0;
    for (size_t i = pivot_place + 1, j = size - 1; n < (suf_size / 2); i++, j--) {
        swap(&arr[i], &arr[j]);
        n++;
    }
}