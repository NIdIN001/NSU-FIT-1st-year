//
// Created by Станислав Уточкин on 06.05.2020.
//
#include "header.h"

size_t make_signs(FILE* input, int* letters_count) {
    int c;
    size_t text_len = 0;
    while (!feof(input)) {
        c = fgetc(input);
        if (c == -1)
            continue;
        letters_count[c]++;
        text_len++;
    }
    return text_len;
}

void delete_tree(Tnode* root) {
    if (root->left != NULL) {
        delete_tree(root->left);
    }
    if (root->right != NULL) {
        delete_tree(root->right);
    }
    if ((root->left == NULL) && (root->right == NULL))
        free(root);
}

Tnode* make_huff_tree(int* signs) {
    Tnode *array[256] = {NULL};
    int count = 0;

    for (size_t i = 0; i < 256; i++) {
        if (signs[i] > 0) {
            Tnode *new = (Tnode *) malloc(sizeof(Tnode));
            new->value = i;
            new->weight = signs[i];
            new->left = NULL;
            new->right = NULL;
            array[count] = new;
            count++;
        }
    }//построил элементы графа с ненулевой встречаймостью в коде

    while (count > 1) {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (array[j]->weight < array[j + 1]->weight) {
                    Tnode *tmp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = tmp;
                }
            }
        }
        Tnode *new = (Tnode *) malloc(sizeof(Tnode));
        new->left = array[count - 2];
        new->right = array[count - 1];
        new->value = 0;
        new->weight = array[count - 1]->weight + array[count - 2]->weight;
        array[count - 2] = new;
        count--;
    }
    return array[0];
}

void save_huffman_tree(Tnode* root, unsigned int* total_bitpos, unsigned char* outbuf) {
    if (root->left) {
        outbuf[*total_bitpos / 8] |= 128u >> ((*total_bitpos) % 8);
        *total_bitpos += 1;

        save_huffman_tree(root->left, total_bitpos, outbuf);
        save_huffman_tree(root->right, total_bitpos, outbuf);
    } else {
        unsigned int bitpos;
        *total_bitpos += 1;
        bitpos = (*total_bitpos) % 8;
        if (bitpos == 0) {
            outbuf[*total_bitpos / 8] = root->value;
        } else {
            outbuf[*total_bitpos / 8] |= root->value >> bitpos;
            outbuf[*total_bitpos / 8 + 1] |= root->value << (8 - bitpos);
        }
        *total_bitpos += 8;
    }
}

void make_huff_table(Tnode *root, unsigned char *code[256], unsigned char path[256], unsigned int level) {
    if (root->value == 0) {
        if (root->left != NULL) {
            path[level] = '0';
            make_huff_table(root->left, code, path, level + 1);
        }
        if (root->right != NULL) {
            path[level] = '1';
            make_huff_table(root->right, code, path, level + 1);
        }
    } else {
        code[root->value] = (unsigned char *) malloc(sizeof(unsigned char) * level);
        memcpy(code[root->value], path, level);
    }
}

void write_encode(FILE *input, FILE *output, unsigned int *total_bitpos, unsigned char *outbuf, unsigned char *code[256]) {
    unsigned int bytepos = *total_bitpos / 8;
    unsigned int bitpos = *total_bitpos % 8;
    int c;

    while (!feof(input)) {
        c = fgetc(input);
        if (c == -1)
            continue;
        unsigned char *current_code = code[c];

        for (unsigned int j = 0; current_code[j] != 0; j++) {
            if (current_code[j] == '1')
                outbuf[bytepos] |= 128u >> bitpos;

            bitpos++;
            if (bitpos > 7) {
                bytepos++;
                bitpos = 0;
                outbuf[bytepos] = 0;
            }
        }
    }
    fwrite(outbuf, 1, bytepos + (bitpos > 0 ? 1 : 0), output);
}

void code(FILE *input ,FILE *output) {
    int letters_count[256] = {0};
    size_t text_len = make_signs(input, letters_count);
    fseek(input, 2, SEEK_SET);

    Tnode *root = NULL;
    root = make_huff_tree(letters_count);

    unsigned char *outbuf = (unsigned char *) malloc(SIZE_OUT);
    memset(outbuf, 0, SIZE_OUT);
    outbuf[0] = (unsigned char) (text_len >> 24);
    outbuf[1] = (unsigned char) (text_len >> 16);
    outbuf[2] = (unsigned char) (text_len >> 8);
    outbuf[3] = (unsigned char) text_len;
    unsigned int bitpos = 32;

    unsigned char *codesTable[256] = {NULL};

    unsigned char path[256] = {'\0'};

    if (text_len > 0)
        save_huffman_tree(root, &bitpos, outbuf);

    make_huff_table(root, codesTable, path, 0);

    write_encode(input, output, &bitpos, outbuf, codesTable);
    free(outbuf);
    delete_tree(root);
}

Tnode *read_huffman_tree(unsigned char *outbuf, size_t *total_bitpos) {
    Tnode *new = (Tnode *) malloc(sizeof(Tnode));
    unsigned int bit = outbuf[*total_bitpos / 8] & (128u >> (*total_bitpos % 8));
    (*total_bitpos)++;

    if (bit) { //не лист

        new->left = read_huffman_tree(outbuf, total_bitpos);
        new->right = read_huffman_tree(outbuf, total_bitpos);
    } else { //лист

        unsigned int bitpos = *total_bitpos % 8;
        new->left = NULL;
        new->right = NULL;
        if (bitpos == 0) {
            new->value = outbuf[*total_bitpos / 8];
        } else {
            new->value = (unsigned char) (outbuf[*total_bitpos / 8] << bitpos);
            new->value |= outbuf[*total_bitpos / 8 + 1] >> (8 - bitpos);
        }
        *total_bitpos += 8;
    }
    return new;
}

size_t read_header(unsigned char *outbuf, size_t *bitpos, size_t message_len) {
    message_len = outbuf[0] << 24;
    message_len |= outbuf[1] << 16;
    message_len |= outbuf[2] << 8;
    message_len |= outbuf[3];
    *bitpos = 32;

    return message_len;
}

void write_raw(unsigned char *inpbuf, size_t bitpos, Tnode *root, size_t message_len, FILE *output) {
    unsigned char outbuf[SIZE_OUT];
    size_t k;
    size_t outpos = 0;
    size_t byte_pos = bitpos / 8;
    size_t bit_pos = bitpos % 8;

    for (k = 0; k < message_len; k++) {
        Tnode *node = root;

        while ((node->left != NULL) && (root->right != NULL)) {
            node = (inpbuf[byte_pos] & (128u >> bit_pos)) ? node->right : node->left;
            if (7 == bit_pos++) {
                bit_pos = 0;
                byte_pos++;
            }
        }
        outbuf[outpos++] = (unsigned char) node->value;
    }
    if (outpos > 0) {
        fwrite(outbuf, 1, outpos, output);
    }
}

void decode(FILE *input ,FILE *output) {
    unsigned char *outbuf = (unsigned char *) malloc(SIZE_OUT);
    size_t bitpos = 0;
    size_t message_len = 0;

    fread(outbuf, 1, SIZE_OUT, input);

    message_len = read_header(outbuf, &bitpos, message_len);

    Tnode *root = (message_len == 0) ? NULL : read_huffman_tree(outbuf, &bitpos);

    write_raw(outbuf, bitpos, root, message_len, output);
    free(outbuf);
    delete_tree(root);
}
