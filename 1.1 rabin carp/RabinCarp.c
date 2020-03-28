int power(int b,int n) {
    int a = 1;
    while (n != 0) {
        a *= b;
        n--;
    }
    return a;
}

int hash(char* str, size_t first, size_t last) {
    int hash = 0;
    for (size_t i = first; i <= last; i++) {
        hash += (str[i] % 3) * (power(3, i));
    }
    return hash;
}

int hash_step(char* text,int hash, size_t first, size_t last, size_t ex_len) {
    hash = hash - (text[first] % 3);
    hash = hash / 3;
    hash = hash + ((text[last + 1] % 3) * (power(3, ex_len - 1)));
    return hash;
}


void RabinCarp(char* example, char* text, size_t ex_len, size_t text_len) {
    size_t first = 0;
    size_t last = ex_len - 1;

    int ex_hash = hash(example, first, last);
    printf("%d\n", ex_hash);

    int buffer_hash = 0;
    buffer_hash = hash(text, first, last);

    for (size_t i = first; i < text_len - 1;) {
        if (buffer_hash != ex_hash) {
            buffer_hash = hash_step(text, buffer_hash, first, last, ex_len);
            first++;
            last++;
            i++;
        } else {
            for (size_t j = 0; j < ex_len; j++) {
                if (text[first] == example[j]) {
                    printf("%zu ", i + 1);
                    buffer_hash = hash_step(text, buffer_hash, first, last, ex_len);
                    first++;
                    last++;
                    i++;
                } else {
                    printf("%zu ", i + 1);
                    buffer_hash = hash_step(text, buffer_hash, first, last, ex_len);
                    first++;
                    last++;
                    i++;
                    break;
                }
            }
        }
    }
}
