//
// Created by Станислав Уточкин on 28.03.2020.
//

#ifndef LABA1_1_HEADER_H
#define LABA1_1_HEADER_H
#include <stdio.h>
#include <string.h>
int power(int b,int n);
int hash(char* str, size_t first, size_t last);
int hash_step(char* text,int hash, size_t first, size_t last, size_t ex_len);
void RabinCarp(char* example, char* text, size_t ex_len, size_t text_len);

#endif //LABA1_1_HEADER_H
