//
// Created by Станислав Уточкин on 27.04.2020.
//
#include "header.h"
void dijkstra(int count_vertex, int from, unsigned int edges[][count_vertex],unsigned int* d, int* result) {

    int visited[count_vertex];
    memset(visited, 0, sizeof(int) * count_vertex);


    int current_vertex = from;
    int counter_of_vertex = 0;

    while (counter_of_vertex < count_vertex) {
        visited[current_vertex] = 1; //поставил отметку что посетил


        unsigned int min_length = INT_MAX * 2 + 1;;

        for (int i = 0; i < count_vertex; i++) {
            if (edges[current_vertex][i] != 0) {
                if ((visited[i] == 0) && (edges[current_vertex][i] <= min_length)) {
                    if (d[i] > d[current_vertex] + edges[current_vertex][i]) {
                        d[i] = d[current_vertex] + edges[current_vertex][i];
                        result[i] = current_vertex + 1;
                    }
                }
            }
        }
        for (int i = 0; i < count_vertex; i++) {
            if ((visited[i] == 0) && (d[i] < min_length)) {
                min_length = d[i];
                current_vertex = i;
            }
        }
        counter_of_vertex++;
    }
}


