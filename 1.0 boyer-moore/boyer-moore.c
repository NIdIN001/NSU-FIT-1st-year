#include <string.h>

void table_(size_t ex_size, char example[], int ascii[]) {
    for (int i = 0; i < 256; i++) {
        ascii[i] = ex_size;
    }

    for (size_t i = 0; i < ex_size - 1; i++) {
        ascii[example[i]] = ex_size-i-1;
    } //составлена таблица смещений ascii
}
void moore_moore(int ascii[], size_t ex_size, char example[], char text[]) {
    size_t text_size = strlen(text);
    size_t i = ex_size - 1;
    size_t j = ex_size - 1;
    size_t max = 1;

    while (i <= text_size - 1) {
        if (i > max)
            max = i;
        if (text[i] == example[j]) {
            while (text[i] == example[j]){
                printf(" %zu", i + 1);
                i--;
                j--;
                if (j == -1) {
                    j = ex_size - 1;
                    i = max + ex_size;
                    break;
                }
            }
        } else {
            printf(" %zu", i + 1);
            i = max + ascii[text[max]];
            j = ex_size - 1;
        }
        if (max >= text_size - 1)
            break;
    }
}
