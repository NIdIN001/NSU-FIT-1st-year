void syntax_error(){
    printf("syntax error");
    exit(EXIT_FAILURE);
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
    int tmp = 0;

    for (size_t i = 0, j = size; i < size; i++, j--) {
        tmp = char_to_int(tmp_number[i]);
        result += tmp * pow(10, j);
    }
    return result / 10;
}

void to_infix(char expression[],char polski[]) {
    size_t j = 0;
    char tmp = 0;
    int last_operation = 0; // 1 - push 2 - in polski

    if ((expression[strlen(expression) - 1] > '9') ||
        ((expression[strlen(expression) - 1] < '0') && (expression[strlen(expression) - 1] != ')')))
        syntax_error(); // если послединй символ - sign, но не закрывающая скобка - бан

    if (((expression[0] > '9') || (expression[0] < '0')) && (expression[0] != '('))
        syntax_error(); // если первый символ выражения sign, но не открывающая скобка - бан

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
        } else
        if (polski[i] != '.')
            count_signs++;
    } //подсчет кол-ва sign и цифр

    if ((count_signs == 0) && (counter_numbers != 0)) {
        for (size_t i = 0; i < strlen(polski)-1; i++) {
            if (polski[i] != '.')
                printf("%c", polski[i]);
        }
        exit(EXIT_SUCCESS);
    } // если нет знаков, но есть цифра, то просто напечатать цифру и закончить

    if (strlen(polski) == 0) {
        syntax_error();
    } 

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
    else syntax_error(); 
    return 0; //никогда не будет использоваться, просто чтобы не было error (тк не пройдет условие выше)
}
