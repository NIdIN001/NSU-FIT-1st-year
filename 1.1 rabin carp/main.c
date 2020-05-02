#include <stdio.h>
#include <string.h>
#include "header.h"

int main(int argc, char *argv[]) {
    char example[18];
    char text[1000];

    FILE *input = NULL;

    if (argc == 2)
        input = fopen(argv[1], "rt");
    //input = fopen("input.txt", "rb");

    if (input == NULL) {
        if (fgets(example, 18, stdin) == 0)
            return 0;
        if (fgets(text, 1000, stdin) == 0)
            return 0;
    } else {
        if (fgets(example, 18, input) == 0)
            return 0;
        if (fgets(text, 1000, input) == 0) {
            printf("0");
            return 0;
        }
    }

    if (example[strlen(example) - 1] == '\n')
        example[strlen(example) - 1] = '\0';
    if (text[strlen(text) - 1] == '\n')
        text[strlen(text) - 1] = '\0';

    size_t ex_len = strlen(example);
    size_t text_len = strlen(text);

    if ((strlen(text) == 0) || (strlen(example) == 0))
        return 0;

    RabinCarp(example, text, ex_len, text_len);

    if (input != NULL)
        fclose(input);
}
