//
// Created by Станислав Уточкин on 28.03.2020.
//

#ifndef LABA6_HEADER_H
#define LABA6_HEADER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    int height;
    struct node* left;
    struct node* right;
}node;

int max(int a, int b);
int Height(node* root);
int Value(node* root);
int Balance(node* root);
node* Create(int value);
node* LeftRotate(node* z);
node* RightRotate(node* z);
node* Addnode(int value,node* root);
int Heightoftree(node* root);

#endif //LABA6_HEADER_H
