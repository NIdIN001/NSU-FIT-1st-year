typedef struct Node_ {
    int value;
    struct Node_ *next;
} Node_;

Node_ *head_int = NULL;

void push_int(Node_ **head, int data) {
    Node_ *tmp = (Node_*) malloc(sizeof(Node_));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}

int pop_int(Node_ **head) {
    Node_* prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->value;
    (*head) = (*head)->next;
    free(prev);
    return val;
}