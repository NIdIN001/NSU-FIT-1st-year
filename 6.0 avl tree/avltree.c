#include "header.h"

int max(int a, int b){
    return (a > b) ? a : b;
}

int Height(Tnode* root){
    return (root == NULL) ? 0 : root->height;
}

int Balance(Tnode* root) {
    return (root == NULL) ? 0 : Height(root->left) - Height(root->right);
}

Tnode* Create(int value) {
    Tnode *new = (Tnode *) malloc(sizeof(Tnode));
    new->value = value;
    new->right = NULL;
    new->left = NULL;
    new->height = 1;
    return new;
}

Tnode* LeftRotate(Tnode* a) {
    Tnode* b = a->right;
    Tnode* l = b->left;

    a->right = l;
    b->left = a;

    a->height = max(Height(a->left), Height(a->right)) + 1;
    b->height = max(Height(b->left), Height(b->right)) + 1;

    return b;
}

Tnode* RightRotate(Tnode* a) {
    Tnode *b = a->left;
    Tnode *c = b->right;

    a->left = c;
    b->right = a;

    a->height = max(Height(a->left), Height(a->right)) + 1;
    b->height = max(Height(b->left), Height(b->right)) + 1;

    return b;
}

Tnode *Addnode(int value, Tnode *root) {
    if (root == NULL)
        return (Create(value));

    if (value <= root->value)
        root->left = Addnode(value, root->left);
    else
        root->right = Addnode(value, root->right);


    root->height = max(Height(root->left), Height(root->right)) + 1;


    // Left Left Case
    if (Balance(root) > 1 && value <= root->left->value)
        return RightRotate(root);

    // Right Right Case
    if (Balance(root) < -1 && value >= root->right->value)
        return LeftRotate(root);

    //Left Right Case
    if (Balance(root) > 1 && value >= root->left->value) {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    // Right Left Case
    if (Balance(root) < -1 && value <= root->right->value) {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }
    return root;
}
