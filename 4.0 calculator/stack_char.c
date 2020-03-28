typedef struct Node {
    char value;
    struct Node *next;
} Node;

Node *head = NULL;

void push(Node **head, char data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->next = (*head);
    (*head) = tmp;
    tmp->value = data;
}

char pop(Node **head) {
    Node* prev = NULL;
    char val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->value;
    (*head) = (*head)->next;
    free(prev);
    return val;
}