//
// Created by Станислав Уточкин on 28.03.2020.
//

#ifndef LABA6_HEADER_H
#define LABA6_HEADER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    int height;
    struct node *left;
    struct node *right;
}Tnode;

int max(int a, int b);
int Height(Tnode* root);
int Balance(Tnode* root);
Tnode* Create(int value);
Tnode* LeftRotate(Tnode* z);
Tnode* RightRotate(Tnode* z);
Tnode* Addnode(int value,Tnode* root);
void Delete_tree(Tnode* root);

#endif //LABA6_HEADER_H
