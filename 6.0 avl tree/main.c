#include <stdio.h>
#include "header.h"

int main(void) {
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
    if (Height(root) != 0)
        Delete_tree(root);
    return 0;
}
