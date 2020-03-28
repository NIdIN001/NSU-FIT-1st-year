void DFS(int x,int* visited,int vertex, int array[][vertex]) { //обход графа в глубину
    if (visited[x] == 2) {
        return;
    }
    if (visited[x] == 1) {
        printf("impossible to sort\n");
        exit(EXIT_SUCCESS);
    }
    visited[x] = 1;
//написать рекурсивную часть функции DFS
    for (int i = 0; i < vertex; i++) {
        if (array[i][x] == 1) {
            DFS(i, visited, vertex, array);
        }
    }
    visited[x] = 2;
    push(x);
}