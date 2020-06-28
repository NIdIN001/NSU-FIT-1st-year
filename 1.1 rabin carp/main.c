#include <stdio.h>
#include <string.h>

int power(int b,int n) {
    int a = 1;
    while (n != 0) {
        a *= b;
        n--;
    }
    return a;
}

int hash(unsigned char* str, size_t first, size_t last) {
    int hash = 0;
    for (size_t i = first; i <= last; i++) {
        hash += (str[i] % 3) * (power(3, i));
    }
    return hash;
}

int Check(unsigned char* word, unsigned char* string, const int lengthWord, int fromPosition) {

    for (int i = 0; i < lengthWord; ++i) {
        if (word[i] == string[i]) {
            printf("%d ", fromPosition + i + 1);
        } else {

            printf("%d ", fromPosition + i + 1);

            return 0;
        }
    }
    return 1;
}

int main() {
    const int maxlengthPattern = 16;

    unsigned char pattern[maxlengthPattern + 1];
    unsigned char string[maxlengthPattern + 1];
    int ch;
    int d = 0;
    do {
        ch = getchar();

        pattern[d] = ch;
        d++;
    } while (ch != '\n');
    d--;
    pattern[d] = '\0';
    int lengthPattern = d;

    int hashOfWord = hash(pattern,0 ,lengthPattern);

    for (int j = 0; j < lengthPattern; j++) {
        ch = getchar();
        if (ch == EOF) {
            printf("0\n");
            return 0;
        }
        string[j] = ch;
        string[j + 1] = '\0';
    }

    printf("%d ", hashOfWord);


    int hashOfString = hash(string,0 ,lengthPattern);
    int k = 0;

    int factor = power(3, lengthPattern - 1);
    while (1) {
        if (hashOfWord == hashOfString) {
            Check(pattern, string, lengthPattern, k);

        }
        int c = getchar();
        if (c == EOF) {
            break;
        }
        hashOfString = ((hashOfString - string[0] % 3) / 3 + ((unsigned char) c % 3) * factor);
        for (int i = 0; i < lengthPattern - 1; i++) {
            string[i] = string[i + 1];
        }
        string[lengthPattern - 1] = c;

        k++;
    }

    return 0;
}
