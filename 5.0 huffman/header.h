//
// Created by Станислав Уточкин on 18.04.2020.
//

#ifndef LABA5_HEADER_H
#define LABA5_HEADER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {
    unsigned int weight;
    unsigned char value;
    struct node *left;
    struct node *right;
    struct node *parent;
}Tnode;
typedef struct list{
    unsigned char value;
    char code[8];
}Tlist;

static int count = 0;

int make_signs(int* signs,FILE* input);
void make_table(Tnode *root, Tlist codes[],char path[256], int level,int signscount);
Tnode* make_huff_tree(int* signs);
unsigned char bit_to_char(unsigned char bitbuf[], int bitcount);
int coder(Tlist* codes,FILE* input,FILE* output);
void DFS(Tnode* root, FILE* log, unsigned char* letters);
void make_log(Tnode* root, int nulls, FILE *log);
void code(FILE *input, FILE *output, FILE *log);

Tnode* new_node(unsigned char value);
Tnode* remake_tree(size_t tree_len,char* tree);
void install_letters(Tnode* root,char* tree);
void char_to_bit(int c, int* buffer);
void decoder(Tnode *const_root,FILE* input, FILE* output, int nulls);
void decode(FILE* input, FILE* output, FILE *log);


#endif //LABA5_HEADER_H
