#include <stdio.h>
#include <string.h>
#include "RabinCarp.c"

int main(int argc, char *argv[]) {
    char example[16];
    char text[100];

    FILE *input = NULL;

    if (argc == 2)
        input = fopen(argv[1], "rt");

    if (input == NULL) {
        if (fgets(example, 16, stdin) == 0)
            return 0;
        if (fgets(text, 100, stdin) == 0)
            return 0;
    } else {
        if (fgets(example, 16, input) == 0)
            return 0;
        if (fgets(text, 100, input) == 0)
            return 0;
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