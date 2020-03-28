//
// Created by Станислав Уточкин on 28.03.2020.
//

#ifndef LABA7_HEADER_H
#define LABA7_HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int value;
    struct Node* next;
}Node;

Node* first;
Node* last;

void push(int value);
int pop();

void DFS(int x,int* visited,int vertex, int array[][vertex]);

#endif //LABA7_HEADER_H
