#include "B.h"

Node* getFreeNode(T value, Node *parent) {
    Node* tmp = new Node;
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

void Binsert(Node **head, T value) {
    Node *tmp = NULL;
    if (*head == NULL) {
        *head = getFreeNode(value, NULL);
        return;
    }

    tmp = *head;
    while (tmp) {
        if (CMP_GT(value, tmp->data)) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = getFreeNode(value, tmp);
                return;
            }
        } else {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = getFreeNode(value, tmp);
                return;
            }
        }
    }
}

Node* getMinNode(Node *root) {
    while (root->left) {
        root = root->left;
    }
    return root;
}

Node* getMaxNode(Node *root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}

Node *getNodeByValue(Node *root, short int value) {
    while (root) {
        if (root->data->data.year > value) {
            root = root->left;
            continue;
        } else if (root->data->data.year < value) {
            root = root->right;
            continue;
        } else {
            return root;
        }
    }
    return NULL;
}

void printTree(Node *root, const char *dir, int level) {
    if (root) {
        cout << setw(12) << root->data->data.author << ' '
         << setw(32) << root->data->data.title << ' '
         << setw(16) << root->data->data.publisher << ' '
         << setw(4) << root->data->data.year << ' '
         << setw(4) << root->data->data.num_of_page << ' '
         << endl;
        printTree(root->left, "left", level+1);
        printTree(root->right, "right", level+1);
    }
}
