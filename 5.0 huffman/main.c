#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "huffman.c"

int main(int argc, char**argv) {

    int encode = 0;
    FILE *output = NULL;
    FILE *input = NULL;

    if (argc > 3) {
        if (strncmp(argv[1], "c", 1) == 0) {
            encode = 1;
        } else if (strncmp(argv[1], "d", 1) == 0) {
            encode = 0;
        } else {
            printf("c|d");
            return 1;
        }
        input = fopen(argv[2], "rb");
        if (input == NULL) {
            fclose(output);
            printf("cannot open file %s\n", argv[2]);
            return 1;
        }
        output = fopen(argv[3], "wb");
        if (output == NULL) {
            printf("cannot open file %s\n", argv[3]);
            return 1;
        }
    } else {
        char act[4];

        if (fgets(act, 4, stdin) == NULL) {
            printf("bad input\n");
            return 1;
        }
        if (strncmp(act, "c\n", 2) == 0) {
            encode = 1;
        } else if (strncmp(act, "d\n", 2) == 0) {
            encode = 0;
        } else {
            printf("bad input\n");
            return 1;
        }

        output = stdout;
        input = stdin;
    }

    if (encode) {
        code(input, output);
    } else {
        decode(input, output);
    }

    if (output != stdout)
        fclose(output);

    if (input != stdin)
        fclose(input);

    return 0;


/*
    //FILE *input = fopen("input.txt", "rt");
    //FILE *output = fopen("output.txt", "wt");

    FILE *input = fopen("input.txt", "wt");
    FILE *output = fopen("output.txt", "rt");
    //code(input, output);
    decode(output, input);
    fclose(input);
    fclose(output);
*/
}