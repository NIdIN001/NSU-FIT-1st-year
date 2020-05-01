#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {
    int vertex = -1;
    if (scanf("%d", &vertex) != 1) {
        printf("bad number of lines");
        return 0;
    }
    int lines = -1;
    if (scanf("%d", &lines) != 1) {
        printf("bad number of lines");
        return 0;
    }

    if ((vertex < 0) || (vertex > 1000)) {
        printf("bad number of vertices");
        return 0;
    }

    if ((lines < 0) || (lines > (vertex * (vertex - 1) / 2))){
        printf("bad number of edges");
        return 0;
    }

    int array[vertex][vertex];
    memset(array, 0, vertex * vertex * sizeof(int));

    for (int i = 0; i < lines; i++) {
        int a = -1;
        int b = 0;
        if (scanf("%d%d", &a, &b) != 2){
            printf("bad number of lines");
            return 0;
        }
        if (a == b) {
            printf ("impossible to sort");
            return 0;
        }
        if ((a > vertex) || (b > vertex) || (a < 0) || (b < 0)){
            printf("bad vertex");
            return 0;
        }

        array[a - 1][b - 1] = 1; // тк первый элемент 0-0 я деляю его 1-1, тк так привычнее
    }

    int visited[vertex];
    memset(visited, 0, vertex * sizeof(int));
    create();

    for (int i = 0; i < vertex; i++) {       //Нам важно, чтобы DFS посетил все вершины графа,
        if (visited[i] == 0) {               //а не только достижимые из нулевой. Поэтому мы явно
            DFS(i, visited, vertex, array);  //вызываем его для всех, ещё не посещённых ранее.
        }
    }
    
    for (int i = 0; i < vertex; i++) {
        printf(" %d", pop() + 1);
    }

/*
    for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < vertex; j++) {
            printf(" %d", array[j][i]);
        }
        printf("\n");
    }
*/
}
