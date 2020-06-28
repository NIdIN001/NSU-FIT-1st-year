#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define K 4
#define SIZE (2 << K)

struct RingBuffer {
    unsigned int write_count;
    unsigned int mask; // mask = 2^k - 1
    unsigned char data[SIZE];
};

static void write(struct RingBuffer *buff, const char *value, int len_value) {
    for (int i = 0; i < len_value; ++i) {
        buff->data[buff->write_count & buff->mask] = value[i];
        ++buff->write_count;
    }
}

static int get_elem(const struct RingBuffer *buff, unsigned int i) {
    return buff->data[i & buff->mask];
}

static void create_buf (struct RingBuffer *buff) {
    buff->write_count = 0;
    buff->mask = SIZE - 1;
}

int main() {
    unsigned char pattern[17];
    if(scanf("%16[^\n]%*c", pattern) == 0)
        exit(EXIT_FAILURE);
    size_t len = strlen((char*)pattern);

    unsigned int *shift_table = malloc(sizeof(unsigned int) * 256); // table of shifts
    if(shift_table == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < 256; ++i) {
        shift_table[i] = (unsigned int)len;
    }
    // table shifts with negative number
    for (unsigned int i = 0; i + 1 < len; ++i) {
        shift_table[pattern[i]] = (unsigned int)len - i - 1; // constructing table of shifts
    }

    struct RingBuffer buffer;
    create_buf(&buffer);

    unsigned int pos =
            (unsigned int)len - 1; // position of pattern`s last symbol in text

    char symbols[17]; // part text

    size_t read_symbols_count = fread(
            symbols, sizeof(char), (size_t)(pos - buffer.write_count) + 1, stdin);
    write(&buffer, symbols, (int)read_symbols_count);

    while (read_symbols_count != 0 && pos < buffer.write_count) {
        unsigned int concurrences = 0;
        while (len >= concurrences + 1 && get_elem(&buffer, pos - concurrences) ==
                                          pattern[len - concurrences - 1]) {
            printf("%u ", pos - concurrences + 1);
            ++concurrences;
        }
        if (concurrences != len) {
            printf("%u ", pos - concurrences + 1);
        }

        pos += shift_table[get_elem(&buffer, pos)];

        if (pos >= buffer.write_count) {
            read_symbols_count = fread(symbols, sizeof(char),
                                       (size_t)(pos - buffer.write_count) + 1, stdin);
            write(&buffer, symbols, (int)read_symbols_count);
        }
    }
    printf("\n");
    free(shift_table);
    return 0;
}
