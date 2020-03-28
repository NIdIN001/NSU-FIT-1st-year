void rebuild_heap(int *array, int n, int i) {
    int rude_index = i;
// Инициализируем наибольший элемент как корень
    int left = 2 * i + 1; // левый = 2*i + 1
    int right = 2 * i + 2; // правый = 2*i + 2

// Если левый дочерний элемент больше корня
    if (left < n && array[left] > array[rude_index])
        rude_index = left;

// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (right < n && array[right] > array[rude_index])
        rude_index = right;

// Если самый большой элемент не корень
    if (rude_index != i) {
        int temp = array[i];
        array[i] = array[rude_index];
        array[rude_index] = temp;

// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        rebuild_heap(array, n, rude_index);
    }
}

// Основная функция, выполняющая пирамидальную сортировку
void heapSort(int *array, int n) {
// Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        rebuild_heap(array, n, i);

// Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--) {
// Перемещаем текущий корень в конец
        int temp = array[i];
        array[i] = array[0];
        array[0] = temp;

// вызываем процедуру heapify на уменьшенной куче
        rebuild_heap(array, i, 0);
    }
}