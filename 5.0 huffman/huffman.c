#include "header.h"

Tnode *newNode(Tnode *left, Tnode *right, size_t freq, int symbol) {
    Tnode *new = (Tnode *) malloc(sizeof(Tnode));
    new->freq = freq;
    new->symbol = symbol;
    new->left = left;
    new->right = right;
    return new;
}

void coder(unsigned char *inpbuf, unsigned int bitpos, Tnode *root, size_t file_length, FILE *output) {
    unsigned char outbuf[MEGABUF_SIZE];
    size_t k;
    size_t outpos = 0;
    size_t pos = bitpos / 8;
    size_t bit_pos = bitpos % 8;

    for (k = 0; k < file_length; k++) {
        Tnode *node = root;

        while (node->left != NULL) {

            node = (inpbuf[pos] & (128u >> bit_pos)) ? node->right : node->left;

            if (8 == ++bit_pos) {
                bit_pos = 0;
                pos++;
            }
        }
        outbuf[outpos++] = (unsigned char) node->symbol;

        if (MEGABUF_SIZE == outpos) {
            size_t written = fwrite(outbuf, 1, outpos, output);

            if (outpos != written) {
                printf("File write error\n");
                exit(1);
            }

            outpos = 0;
        }
    }
    if (outpos > 0) {
        size_t written = fwrite(outbuf, 1, outpos, output);

        if (outpos != written) {
            printf("File write error\n");
            exit(1);
        }
    }
}

Tnode *read_tree(unsigned char *outbuf, unsigned int *total_bitpos) {
    /* выделяем память для одного узла дерева */
    Tnode *nt = (Tnode *) malloc(sizeof(Tnode));
    int bit = outbuf[*total_bitpos / 8] & (128u >> (*total_bitpos % 8));
    (*total_bitpos)++;

    if (bit) {
        /* узел не является листом */
        nt->left = read_tree(outbuf, total_bitpos);
        nt->right = read_tree(outbuf, total_bitpos);
    } else {
        unsigned int bitpos = *total_bitpos % 8;
        /* иначе узел root является листом */
        nt->left = NULL;
        nt->right = NULL;
        /* считываем из файла код символа */
        if (bitpos == 0) {
            nt->symbol = outbuf[*total_bitpos / 8];
        } else {
            nt->symbol = (unsigned char) (outbuf[*total_bitpos / 8] << bitpos);
            nt->symbol |= outbuf[*total_bitpos / 8 + 1] >> (8 - bitpos);
        }
        *total_bitpos += 8;
    }
    return nt;
}

Tnode *read_header(unsigned char *outbuf, unsigned int *bitpos, unsigned int *file_length) {
    *file_length = outbuf[0] << 24;
    *file_length |= outbuf[1] << 16;
    *file_length |= outbuf[2] << 8;
    *file_length |= outbuf[3];
    *bitpos = 32;
    if (*file_length > 0)
        return read_tree(outbuf, bitpos);
    return NULL;
}

void decode(FILE *input, FILE *output) {
    unsigned char *outbuf = (unsigned char *) malloc(OUTBUF_SIZE);
    unsigned int bitpos = 0;
    unsigned int message_len = fread(outbuf, 1, OUTBUF_SIZE, input);

    if (message_len == 0)
        exit(0);
    Tnode *root = read_header(outbuf, &bitpos, &message_len);
    coder(outbuf, bitpos, root, message_len, output);
}

void decoder(FILE *input, FILE *output, unsigned int *total_bitpos, unsigned char *outbuf, unsigned char *code[256]) {
    unsigned char inpbuf[MEGABUF_SIZE] = {0};
    unsigned int bytepos = *total_bitpos / 8;
    unsigned int bitpos = *total_bitpos % 8;
    size_t frag = 0;

    while ((frag = fread(inpbuf, 1, MEGABUF_SIZE, input)) > 0) {
        for (size_t i = 0; i < frag; i++) {
            unsigned char *current_code = code[inpbuf[i]];

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
    }
    fwrite(outbuf, 1, bytepos + (bitpos > 0 ? 1 : 0), output);
}

void make_huff_table(unsigned char path[256], unsigned int level, unsigned char *code[256], Tnode *root) {
    if (root->left || root->right) //if !leaf
    {
        path[level] = '0';
        make_huff_table(path, level + 1, code, root->left);
        path[level] = '1';
        make_huff_table(path, level + 1, code, root->right);
    } else {
        path[level] = 0;
        code[root->symbol] = memcpy(malloc(level + 1), path, level + 1);
    }
}

void save_tree(Tnode *root, unsigned int *total_bitpos, unsigned char *outbuf) {
    if (root->left) {
        /*записать_в_файл_1_бит(файл, 1)*/
        outbuf[*total_bitpos / 8] |= 128u >> ((*total_bitpos) % 8);
        *total_bitpos += 1;
        save_tree(root->left, total_bitpos, outbuf);
        save_tree(root->right, total_bitpos, outbuf);
    } else {
        unsigned int bitpos;
        /*записать_в_файл_1_бит(файл, 0)*/
        *total_bitpos += 1;
        bitpos = (*total_bitpos) % 8;
        /*записать_в_файл_8_бит(файл, root->symbol)*/
        if (bitpos == 0) {
            outbuf[*total_bitpos / 8] = root->symbol;
        } else {
            outbuf[*total_bitpos / 8] |= root->symbol >> bitpos;
            outbuf[*total_bitpos / 8 + 1] |= root->symbol << (8 - bitpos);
        }
        *total_bitpos += 8;
    }
}

Tnode *build_tree(unsigned int *letters) {
    Tnode *ArrNode[256] = {NULL};
    int count = 0;
    for (int i = 0; i < 256; i++) {

        if (letters[i]) {
            ArrNode[count] = (Tnode *) malloc(sizeof(Tnode));
            ArrNode[count]->freq = letters[i];
            ArrNode[count]->symbol = i;
            ArrNode[count]->left = NULL;
            ArrNode[count]->right = NULL;
            count++;
        }
    }
    while (count > 1) {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (ArrNode[j]->freq < ArrNode[j + 1]->freq) {
                    Tnode *tmp = ArrNode[j];
                    ArrNode[j] = ArrNode[j + 1];
                    ArrNode[j + 1] = tmp;
                }
            }
        }
        Tnode *NewNode = newNode(ArrNode[count - 2], ArrNode[count - 1],
                                 ArrNode[count - 2]->freq + ArrNode[count - 1]->freq, 0);
        ArrNode[count - 2] = NewNode;
        count--;
    }
    Tnode *root = ArrNode[0];
    return root;
}

void encode(FILE *input, FILE *output) {
    unsigned int lettersFreq[256] = {0};
    int symbol = 0;
    unsigned int message_len = 0;
    while ((symbol = fgetc(input)) != EOF) {
        message_len++;
        lettersFreq[symbol]++;
    }
    if (message_len == 0)
        exit(0);
    Tnode *root = build_tree(lettersFreq);
    //Finished build Huffman Tree
    unsigned char *outbuf = (unsigned char *) malloc(OUTBUF_SIZE);
    memset(outbuf, 0, OUTBUF_SIZE);
    outbuf[0] = (unsigned char) (message_len >> 24);
    outbuf[1] = (unsigned char) (message_len >> 16);
    outbuf[2] = (unsigned char) (message_len >> 8);
    outbuf[3] = (unsigned char) message_len;
    unsigned int bitpos = 32;
    /*сохранить дерево*/
    save_tree(root, &bitpos, outbuf);
    unsigned char *codesTable[256] = {0},
            path[256] = {0};
    make_huff_table(path, 0, codesTable, root);
    fseek(input, 3, SEEK_SET);
    decoder(input, output, &bitpos, outbuf, codesTable);
}
