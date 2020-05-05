#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

int main(int argc, char **argv) {
    int docode;
    FILE *output;
    FILE *input;
    if (argc > 3) {
        if (strcmp(argv[1], "c") == 0) {
            docode = 1;
        } else if (strcmp(argv[1], "d") == 0) {
            docode = 0;
        } else {
            printf("c|d output input");
            return 1;
        }
        input = fopen(argv[3], "rb");
        output = fopen(argv[2], "wb");
    } else {

        argv[2] = "out.txt";
        argv[3] = "in.txt";

        input = fopen(argv[3], "rb");
        output = fopen(argv[2], "wb");
        char act[4];
        if (fgets(act, 4, input) == NULL) {
            printf("bad input\n");
            return 0;
        }
        if (strcmp(act, "c\n") == 0) {
            docode = 1;
        } else if (strcmp(act, "d\n") == 0) {
            docode = 0;
        } else {
            return 0;
        }
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
    if (docode)
        code(input, output);
    else
        decode(input, output);
    fclose(output);
    fclose(input);
    return EXIT_SUCCESS;
}

/*
int main () {
    //FILE *input = fopen("in.txt", "rt");
    //FILE *output = fopen("out.txt", "wt");

    FILE *input = fopen("in.txt", "wt");
    FILE *output = fopen("out.txt", "rt");
    //code(input, output);
    decode(output, input);
    fclose(input);
    fclose(output);
}
*/
