#ifndef LAB5_HEADER_H
#define LAB5_HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    size_t freq;
    int symbol;
    struct Node *right;
    struct Node *left;
} Tnode;

#define MEGABUF_SIZE 4096
#define OUTBUF_SIZE 1024 * 700

Tnode *newNode(Tnode *left, Tnode *right, size_t freq, int symbol);
void coder(unsigned char *inpbuf, unsigned int bitpos, Tnode *root, size_t file_length, FILE *output);
Tnode *read_tree(unsigned char *outbuf, unsigned int *total_bitpos);
Tnode *read_header(unsigned char *outbuf, unsigned int *bitpos, unsigned int *file_length);
void decode(FILE *input, FILE *output);
void decoder(FILE *input, FILE *output, unsigned int *total_bitpos, unsigned char *outbuf, unsigned char *code[256]);
void make_huff_table(unsigned char path[256], unsigned int level, unsigned char *code[256], Tnode *root);
void save_tree(Tnode *root, unsigned int *total_bitpos, unsigned char *outbuf);
Tnode *build_tree(unsigned int *letters);
void encode(FILE *input, FILE *output);

#endif //LAB5_HEADER_H
