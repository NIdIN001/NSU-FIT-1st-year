void quick_sort(int *arr, int left, int right) {
    int midle;
    int temp;
    int left_change;
    int right_change;

    while (right - left >= 1) {
        midle = arr[(right + left) / 2];
        left_change = left,
                right_change = right;

        do {
            while (arr[left_change] < midle)
                left_change++;

            while (midle < arr[right_change])
                right_change--;

            if (left_change <= right_change) {
                temp = arr[right_change];
                arr[right_change] = arr[left_change];
                arr[left_change] = temp;
                left_change++;
                right_change--;
            }
        } while (left_change < right_change);

        if (right_change - left > right - left_change) {
            quick_sort(arr, left_change, right);
            right = right_change;
        } else {
            quick_sort(arr, left, right_change);
            left = left_change;
        }
    }
}
