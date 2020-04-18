#include "header.h"

int make_signs(int* signs,FILE* input) {
    int c;
    int signscount = 0;
    while (!feof(input)) {
        c = fgetc(input);
        if (c == -1)
            continue;
        signs[c]++;
        if (signs[c] == 1)
            signscount++;
    }
    return signscount;
}

void make_table(Tnode *root, Tlist codes[],char path[256], int level,int signscount) {
    if (signscount == 1) {
        codes[count].value = root->value;
        memcpy(codes[count].code, path, 1);
        count++;
        return;
    }

    if (root->value == 0) {
        if (root->left != NULL) {
            path[level] = '0';
            make_table(root->left, codes, path, level + 1, signscount);
        }
        if (root->right != NULL) {
            path[level] = '1';
            make_table(root->right, codes, path, level + 1, signscount);
        }
    } else {
        codes[count].value = root->value;
        memcpy(codes[count].code, path, level);
        count++;
    }
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
}// построил дерево разбора

unsigned char bit_to_char(unsigned char bitbuf[], int bitcount) {
    unsigned char result = 0;
    for (int i = 0, j = 7; i < 8; i++, j--) {
        if (bitbuf[i] == '1') {
            result = result + pow(2, j);
        }
    }
    return result;
}

int coder(Tlist* codes,FILE* input,FILE* output) {
    char bitbuf[8] = {0};
    int bitcount = 0;
    int c;
    while (!feof(input)) {
        c = fgetc(input);
        if (c == -1)
            continue;
        for (int j = 0; j < count; j++) {
            if (codes[j].value == c) {
                for (int l = 0; l < strlen(codes[j].code); l++) {
                    bitbuf[bitcount] = codes[j].code[l];
                    bitcount++;
                    if (bitcount == 8) {
                        fprintf(output, "%c", bit_to_char(bitbuf, bitcount));
                        bitcount = 0;
                        memset(bitbuf, 0, sizeof(unsigned char) * 8);//посмотреть на парашу
                    }
                }
            }
        }
    }
    int nulls = 0;
    while (bitcount != 8) {
        for (int i = bitcount; i < 8; i++) {
            for (int j = 7; j > 0; j--) {
                bitbuf[j] = bitbuf[j - 1];
            }
            bitbuf[0] = '0';
            bitcount++;
            nulls++;
        }

    }
    if (nulls != 0) {
        fprintf(output, "%c", bit_to_char(bitbuf, bitcount));
    }
    return nulls;
}

void DFS(Tnode* root, FILE* log, unsigned char* letters) {
    if (root->left != NULL) {
        fwrite("L", 1, sizeof(unsigned char), log);
        DFS(root->left, log, letters);
    }
    if (root->right != NULL) {
        fwrite("R", 1, sizeof(unsigned char), log);
        DFS(root->right, log, letters);
    }
    if (root->value != 0) {
        letters[count] = root->value;
        count++;
    }
    fwrite("U", 1, sizeof(unsigned char), log);
}

void make_log(Tnode* root, int nulls) {
    /*
    Как устроен log файл:
     первая строка - струкура девева, остов без букв
     вторая строка - буквы, которые нужно вставить в дерево
     последный символ 2 строки - кол-во незначащих бит в последнем байте
    */
    FILE *log = NULL;
    log = fopen("log.txt", "wb");
    if (log == NULL) {
        printf("Can't open log file");
        return;
    }

    count = 1;
    unsigned char letters[256] = {0};
    letters[0] = '\n';

    DFS(root, log, letters);
    fprintf(log, "%s", letters);

    fprintf(log, "%d", nulls);
    fclose(log);
}

void code(FILE *input, FILE *output) {
    int signs[256] = {0};
    int signscount = make_signs(signs, input);

    fseek(input, 0, SEEK_SET);

    Tnode *root = NULL;
    root = make_huff_tree(signs);
    if (root == NULL) {// пустой файл
        return;
    }

    Tlist codes[signscount];
    for (int i = 0; i < signscount; i++) {
        for (int j = 0; j < 8; j++) {
            codes[i].code[j] = 0;
        }
    }

    char path[256] = {'0'};
    make_table(root, codes, path, 0, signscount);

    int nulls = coder(codes, input, output);
    make_log(root, nulls);
}

Tnode* new_node(unsigned char value) {
    Tnode *new = (Tnode *) malloc(sizeof(Tnode));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    new->parent = NULL;
    return new;
}

Tnode* remake_tree(size_t tree_len, unsigned char* tree) {
    Tnode *root = new_node(0);
    unsigned char c;
    int i = 0;
    while (i < tree_len) {
        c = tree[i];
        i++;
        if (c == 255)
            continue;
        if (c == 'R') {
            root->right = new_node(0);
            Tnode *tmp = root;
            root = root->right;
            root->parent = tmp;
        }
        if (c == 'L') {
            root->left = new_node(0);
            Tnode *tmp = root;
            root = root->left;
            root->parent = tmp;
        }
        if (c == 'U') {
            root = root->parent;
        }
    }
    return root;
}

void install_letters(Tnode* root, unsigned char* tree) {
    if (root->left != NULL) {
        install_letters(root->left, tree);
    }
    if (root->right != NULL) {
        install_letters(root->right, tree);
    }
    if ((root->left == NULL) && (root->right == NULL)) {
        root->value = tree[count];
        count++;
    }
}

void char_to_bit(int c, int* buffer) {
    for (int i = 0, j = 7; c != 0; i++, j--) {
        buffer[j] = c % 2;
        c /= 2;
    }
}

void decoder(Tnode *const_root,FILE* input, FILE* output, int nulls) {
    int buffer[8] = {0};
    int bitpos = 0;
    int symbol = 0;
    Tnode *root = const_root;
    int is_1_letter = 0;

    if ((const_root->right == NULL) && (const_root->left == NULL)) {
        is_1_letter = 1;
    }


    if(fscanf(input, "%c", &symbol) != 1)
        return;
    char_to_bit(symbol, buffer);

    while (!feof(input)) {
        if (is_1_letter == 1) {
            fprintf(output, "%c", root->value);
            if (buffer[bitpos] == -1) {
                return;
            }
        } else {
            if (buffer[bitpos] == -1) {
                return;
            }
            if (buffer[bitpos] == 0) {
                root = root->left;
            } else {
                root = root->right;
            }
            if ((root->right == NULL) && (root->left == NULL)) {
                fprintf(output, "%c", root->value);
                root = const_root;
            }
        }
        bitpos++;
        if (bitpos == 8) {
            bitpos = 0;
            memset(buffer, 0, sizeof(int) * 8);
            if(fscanf(input, "%c", &symbol) != 1)
                return;

            int tmp = fgetc(input);
            fseek(input, -1, SEEK_CUR);
            if (tmp == -1) { // если это последний символ потока
                char_to_bit(symbol, buffer);
                for (int i = nulls, j = 0; i < 8; i++, j++) {
                    buffer[j] = buffer[i];
                }
                buffer[8 - nulls] = -1;
            } else {
                char_to_bit(symbol, buffer);
            }
        }
    }
}

void decode(FILE* input, FILE* output) {
    FILE *log = fopen("log.txt", "rb");

    unsigned char tree[1000] = {0};
    if (fscanf(log, "%s", tree) != 1)
        return;
    size_t tree_len = strlen(tree);

    Tnode *root = remake_tree(tree_len - 1, tree);

    for (int i = 0; i < tree_len; i++) {
        tree[i] = 0;
    }
    fseek(log, 1, SEEK_CUR);
    fread(tree, 1, 1000, log);

    int nulls = tree[strlen(tree) - 1] - 48;

    count = 0;
    install_letters(root, tree);

    decoder(root, input, output, nulls);
    fclose(log);
    fclose(input);
    fclose(output);
}
