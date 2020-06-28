#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int main(void) {
    int todo = 0;
    FILE *output,
            *input;
    input = fopen("in.txt", "rb");
    output = fopen("out.txt", "wb");
    char act[4];
    if (!fgets(act, 4, input)) {
        fclose(input);
        fclose(output);
        return 0;
    }
    if (strcmp(act, "c\r\n") == 0) {
        todo = 1;
    } else if (strcmp(act, "d\r\n") == 0) {
        todo = 0;
    }

    if (todo)
        encode(input, output);
    else
        decode(input, output);
    fclose(output);
    fclose(input);
    return 0;
}
