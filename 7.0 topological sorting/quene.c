#include "header.h"
//описание очереди
void create() {
    first = NULL;
    last = NULL;
}

void push(int value) {
    if (last == NULL) {
        Node *tmp = (Node *) malloc(sizeof(Node));
        tmp->value = value;
        tmp->next = NULL;
        first = tmp;
        last = tmp;
        return;
    }
    Node *tmp = (Node *) malloc(sizeof(Node));
    tmp->value = value;
    tmp->next = NULL;
    last->next = tmp;
    last = tmp;
}

int pop() {
    if (first == NULL) {
        printf("Quene is empty");
        exit(EXIT_FAILURE);
    }
    int a = first->value;
    first = first->next;
    return a;
}
//описание очереди