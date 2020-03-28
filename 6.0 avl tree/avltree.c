#include "header.h"

int max(int a, int b){
    return (a > b) ? a : b;
}

int Height(node* root){
    return (root == NULL) ? 0 : root->height;
}

int Value(node* root) {
    return (root == NULL) ? 0 : root->value;
}

int Balance(node* root) {
    return (root == NULL) ? 0 : Height(root->left) - Height(root->right);
}

node* Create(int value) {
    node *new = (node *) malloc(sizeof(node *));
    new->value = value;
    new->right = NULL;
    new->left = NULL;
    new->height = 0;
    return new;
}

node* LeftRotate(node* z) {
    node *y = z->right;
    node *t2 = y->left;

    y->left = z;
    z->right = t2;

    z->height = max(Height(z->left), Height(z->right)) + 1;
    y->height = max(Height(y->left), Height(y->right)) + 1;

    return y;
}

node* RightRotate(node* z) {
    node *y = z->left;
    node *t3 = y->right;

    y->right = z;
    z->left = t3;

    z->height = max(Height(z->left), Height(z->right)) + 1;
    y->height = max(Height(y->left), Height(y->right)) + 1;

    return y;
}

node* Addnode(int value,node* root) {
    if (root == NULL) {
        return Create(value);
    }
    if (value > root->value) {
        root->right = Addnode(value, root->right);

    } else { //(value <= root->value)
        root->left = Addnode(value, root->left);
    }
    //Построение двоичного дерева поиска (оно происходит правильно)

    root->height = max(Height(root->left), Height(root->right)) + 1;


    // Left Left Case
    if (Balance(root) > 1 && value < Value(root->left))
        return RightRotate(root);

    // Right Right Case
    if (Balance(root) < -1 && value > Value(root->right))
        return LeftRotate(root);

    //Left Right Case
    if (Balance(root) > 1 && value > Value(root->left)) {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    // Right Left Case
    if (Value(root) < -1 && value < Value(root->right)) {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }
    return root;
}

int Heightoftree(node* root) {
    node *temp = root;
    int h1 = 0;
    int h2 = 0;
    if (root == NULL)
        return 0;
    if (root->left)
        h1 = Height(root->left);
    if (root->right)
        h2 = Height(root->right);
    return (max(h1, h2) + 1);
}
