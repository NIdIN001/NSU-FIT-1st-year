#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
    Tnode *root = NULL;
    int nodes = 0;
    if (scanf("%d", &nodes) != 1)
        return 1;

    for (int i = 0; i < nodes; i++) {
        int value = 0;
        if (scanf("%d", &value) != 1)
            return 1;
        root = Addnode(value, root);
    }

    printf("%d", Height(root));
    Delete_tree(root);
}
