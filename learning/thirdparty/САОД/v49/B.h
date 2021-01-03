#ifndef B_H
#define B_H

#include "DB.h"
#include "queue.hpp"
#include <stdio.h>


typedef listnode* T;

#define CMP_EQ(a, b) ((a->data.year) == (b->data.year))
#define CMP_LT(a, b) ((a->data.year) < (b->data.year))
#define CMP_GT(a, b) ((a->data.year) > (b->data.year))

typedef struct Node {
    T data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

    Node* getFreeNode(T value, Node *parent);

    void Binsert(Node **head, T value);

    Node* getMinNode(Node *root);

    Node* getMaxNode(Node *root);

    Node *getNodeByValue(Node *root, short int value);

    void printTree(Node *root, const char *dir, int level);

    Node* getFreeNode(T value, Node *parent);

#endif // B_H
