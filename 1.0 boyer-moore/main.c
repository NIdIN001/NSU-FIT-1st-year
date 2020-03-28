#include <stdio.h>
#include <locale.h>
#include "boyer-moore.c"

int main(int argc, char *argv[]) {
    setlocale(0,"");

    char example[16];
    gets(example);

    //   const char *example;
    //   example = argv[1];

    size_t ex_size = strlen(example);

    int ascii[256];
    table_(ex_size, example, ascii);

    char text[100];
    gets(text);

    //   const char *text;
    //   text = argv[2];

    if ((strlen(text) == 0) || (strlen(example) == 0))
        return 0;

    moore_moore(ascii, ex_size, example, text);
}
