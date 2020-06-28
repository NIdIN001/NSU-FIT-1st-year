#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef struct Node {
    char value;
    struct Node *next;
} Node;

typedef struct Node_ {
    int value;
    struct Node_ *next;
} Node_;

Node *head = NULL;
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

void syntax_error(){
    printf("syntax error");
    exit(0);
}

int Priority(char c) {
    if (c == '(' || c == ')') return 1;
    if (c == '+' || c == '-') return 2;
    if (c == '/' || c == '*') return 3;
    return 0;
}

int char_to_int(char c) {
    int x = c - 48;
    return x;
}

int char_to_int_(char tmp_number[]) {
    size_t size = strlen(tmp_number);
    int result = 0;

    for (size_t i = 0, j = size; i < size; i++, j--) {
        int tmp = char_to_int(tmp_number[i]);
        result += tmp * pow(10, j);
    }
    return result / 10;
}

void to_infix(char expression[],char polski[]) {
    size_t j = 0;
    char tmp = 0;

    int last_operation = 0; // 1 - push 2 - in polski
/*
    if ((expression[strlen(expression) - 1] > '9') ||
        ((expression[strlen(expression) - 1] < '0') && (expression[strlen(expression) - 1] != ')')))
        syntax_error(); // если послединй символ - sign, но не закрывающая скобка - бан

    if (((expression[0] > '9') || (expression[0] < '0')) && (expression[0] != '('))
        syntax_error(); // если первый символ выражения sign, но не открывающая скобка - бан
        */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for (size_t i = 0; i < strlen(expression); i++) {
        if (isdigit(expression[i])) {
            polski[j] = expression[i];
            j++;
            last_operation = 2;
        } else { //Если не цифра
            switch (expression[i]) {
                case '(':
                    if (expression[i + 1] == ')')
                        syntax_error();
                    push(&head, expression[i]);
                    break;

                case ')':
                    if (j == 0)
                        syntax_error();
                    if (polski[j - 1] != '.') {
                        polski[j] = '.';
                        j++;
                    }
                point:
                    if (head == NULL)
                        syntax_error();
                    while (head->value != '(') {
                        polski[j] = pop(&head);
                        j++;
                        goto point;
                    }
                    tmp += pop(&head);
                    break;

                case '+':
                case '*':
                case '/':
                case '-':
                    if (last_operation == 1) {
                        syntax_error();
                    } else
                        last_operation = 1;

                    if (j == 0) {
                        syntax_error();
                    } else {
                        if ((polski[j - 1] != '+') && (polski[j - 1] != '-') && (polski[j - 1] != '*') &&
                            (polski[j - 1] != '/') && (polski[j - 1] != '.')) {
                                polski[j] = '.';
                                j++;
                        }
                        if (head == NULL)
                            push(&head, expression[i]);
                        else {
                            if (Priority(expression[i]) > Priority(head->value)) {
                                push(&head, expression[i]);
                            } else {
                                while (Priority(expression[i]) <= Priority(head->value)) {
                                    polski[j] = pop(&head);
                                    j++;
                                    if (head == NULL)
                                        break;
                                }
                                push(&head, expression[i]);
                            }
                        }
                        break;
                        default:
                            syntax_error();
                    }
            }//Конец switch
        }//Конец Если не цифра
    }//Конец рассмотра выражения

    if (expression[strlen(expression) - 1] != ')') {
        polski[j] = '.';
        j++;
    }

    while (head != NULL) { //Если в стеке что-то осталось - положить в строку
        polski[j] = pop(&head);
        j++;
    }
}

int calculator(char polski[]) {
    int tmp_result = 0;
    int a = 0;
    int b = 0;

    int count_signs = 0;
    int counter_numbers = 0;

    for (size_t i = 0; i < strlen(polski); i++) {
        if ((polski[i] > 47) && (polski[i] < 58)) {
            counter_numbers++;
        } else if (polski[i] != '.')
            count_signs++;
    } //подсчет кол-ва sign и цифр

    if ((count_signs == 0) && (counter_numbers != 0)) {
        for (size_t i = 0; i < strlen(polski) - 1; i++) {
            if (polski[i] != '.')
                printf("%c", polski[i]);
        }
        exit(EXIT_SUCCESS);
    } // если нет знаков, но есть цифра, то просто напечатать цифру и закончить

    if (strlen(polski) == 0) {
        syntax_error();
    } // если пусто - бан

    char number[1100];

    for (size_t i = 0; i < strlen(polski); i++) {
        if ((polski[i] > 47) && (polski[i] < 58)) {
            size_t j = 0;
            while (polski[i] != '.') {
                number[j] = polski[i];
                i++;
                j++;
            }
            number[j] = 0;

            push_int(&head_int, char_to_int_(number));


        } else {
            switch (polski[i]) {
                case '+':
                    a = pop_int(&head_int);
                    b = pop_int(&head_int);

                    tmp_result = a + b;
                    push_int(&head_int, tmp_result);
                    break;

                case '-':
                    a = pop_int(&head_int);
                    b = pop_int(&head_int);

                    tmp_result = a - b;
                    push_int(&head_int, -tmp_result);
                    break;

                case '*':
                    a = pop_int(&head_int);
                    b = pop_int(&head_int);

                    tmp_result = a * b;
                    push_int(&head_int, tmp_result);
                    break;

                case '/':
                    a = pop_int(&head_int);
                    b = pop_int(&head_int);

                    if (a == 0) {
                        printf("division by zero");
                        exit(EXIT_FAILURE);
                    } else {
                        tmp_result = b / a;
                    }
                    push_int(&head_int, tmp_result);
                    break;
                default:
                    syntax_error();
            }
        }
    }
    if (head_int->next == NULL)
        return pop_int(&head_int);
    else syntax_error(); //Большие числа банятся на этом моменте из-за того что умеет складывать только
    // по одной цифре и в стеке остаюстся еще цифры от большого числа
    return 0; //никогда не будет использоваться, просто чтобы не было error (тк не пройдет условие выше)
}

int main() {
    char *expression = (char *) malloc(sizeof(char) * 1200);
    memset(expression, 0, sizeof(char) * 1200);
    if (fgets(expression, 1200, stdin) == 0) {
        free(expression);
        return 0;
    }
    if (expression[strlen(expression) - 1] == '\n')
        expression[strlen(expression) - 1] = 0;
    if (strlen(expression) == 0)
        syntax_error();

    char *polski = (char *) malloc(sizeof(char) * 1900);
    memset(polski, 0, sizeof(char) * 1900);
    to_infix(expression, polski);

    //printf("%s\n", polski);

    printf("%d", calculator(polski));

    free(polski);
    free(expression);
}

