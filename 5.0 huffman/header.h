//
// Created by Станислав Уточкин on 06.05.2020.
//

#ifndef LABA5_HEADER_H
#define LABA5_HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE_OUT 1024*700

typedef struct node {
    unsigned int weight;
    unsigned int value;
    struct node *left;
    struct node *right;
}Tnode;


size_t make_signs(FILE* input, int* letters_count);
void delete_tree(Tnode* root);
Tnode* make_huff_tree(int* signs);
void save_huffman_tree(Tnode* root, unsigned int* total_bitpos, unsigned char* outbuf);
void make_huff_table(Tnode *root, unsigned char *code[256], unsigned char path[256], unsigned int level);
void write_encode(FILE *input, FILE *output, unsigned int *total_bitpos, unsigned char *outbuf, unsigned char *code[256]);
void code(FILE *input ,FILE *output);
Tnode *read_huffman_tree(unsigned char *outbuf, size_t *total_bitpos);
size_t read_header(unsigned char *outbuf, size_t *bitpos, size_t message_len);
void write_raw(unsigned char *inpbuf, size_t bitpos, Tnode *root, size_t message_len, FILE *output);
void decode(FILE *input ,FILE *output);

#endif //LABA5_HEADER_H
