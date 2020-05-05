#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

int main(int argc, char** argv) {

    int encode;
    FILE *output = NULL;
    FILE *input = NULL;
    FILE *log = NULL;

    if (argc > 3) {
        if (strcmp(argv[1], "c") == 0) {
            encode = 1;
        } else if (strcmp(argv[1], "d") == 0) {
            encode = 0;
        } else {
            printf("c|d output input");
            return 1;
        }
    } else {
        char act[4];
        if (fgets(act, 4, stdin) == NULL) {
            printf("bad input\n");
            return 0;
        }
        if (strcmp(act, "c\n") == 0) {
            encode = 1;
        } else if (strcmp(act, "d\n") == 0) {
            encode = 0;
        } else {
            printf("bad input\n");
            return 0;
        }
        argv[2] = "output.txt";
        argv[3] = "input.txt";
    }
    if (encode) {
        log = fopen("log.txt", "wb");
    } else {
        log = fopen("log.txt", "rb");
    }
    if (encode) {
        input = fopen(argv[3], "rb");
        output = fopen(argv[2], "wb");
    } else {
        input = fopen(argv[2], "rb");
        output = fopen(argv[3], "wb");
    }
    if (output == NULL) {
        printf("cannot open file %s\n", argv[2]);
        return 1;
    }
    if (input == NULL) {
        fclose(output);
        printf("cannot open file %s\n", argv[3]);
        return 1;
    }
    if (log == NULL) {
        fclose(output);
        fclose(input);
        printf("cannot open file log.txt");
        return 1;
    }
    if (encode)
        code(input, output, log);
    else
        decode(input, output, log);
    fclose(output);
    fclose(input);
    return EXIT_SUCCESS;

/*
    FILE *input = fopen("input.txt", "rt");
    FILE *output = fopen("output.txt", "wt");

    //FILE *input = fopen("input.txt", "wt");
    //FILE *output = fopen("output.txt", "rt");
    code(input, output);
    //decode(output, input);
    fclose(input);
    fclose(output);
*/
}


