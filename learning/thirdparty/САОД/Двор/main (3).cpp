#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int rost;
int dec;
long int turn = 0;

struct tree {
    int data;
    int bal;
    tree* left;
    tree* right;
};

tree *t;

void print_tree(tree *t) {
    if (t == NULL) return;
    print_tree(t->left);
    printf("%d ", t->data);
    print_tree(t->right);
}

void LL1(tree *&p) {
    tree *q = p->left;
    if (q->bal == 0) {
        p->bal = -1;
        q->bal = 1;
        dec = 0;
    }
    else {
        p->bal = 0;
        q->bal = 0;
    }
    p->left = q->right;
    q->right = p;
    p = q;
    turn++;
}

void RR1(tree *&p) {
    tree *q = p->right;
    if (q->bal == 0) {
        p->bal = 1;
        q->bal = -1;
        dec = 0;
    }
    else {
        p->bal = 0;
        q->bal = 0;
    }
    p->right = q->left;
    q->left = p;
    p = q;
    turn++;
}

void LR(tree *&p) {
    tree *q = p->left;
    tree *r = q->right;
    if (r->bal < 0) p->bal = 1;
    else p->bal = 0;
    if (r->bal > 0) q->bal = -1;
    else q->bal = 0;
    r->bal = 0;
    p->left = r->right;
    q->right = r->left;
    r->left = q;
    r->right = p;
    p = r;
    turn++;
}

void RL(tree *&p) {
    tree *q = p->right;
    tree *r = q->left;
    if (r->bal > 0) p->bal = -1;
    else p->bal = 0;
    if (r->bal < 0) q->bal = 1;
    else q->bal = 0;
    r->bal = 0;
    p->right = r->left;
    q->left = r->right;
    r->left = p;
    r->right = q;
    p = r;
    turn++;
}

void BL(tree *&p) {
    if (p->bal == -1) p->bal = 0;
    else if (p->bal == 0) {
        p->bal = 1;
        dec = 0;
    }
    else if (p->bal == 1) {
        if (p->right->bal >= 0) RR1(p);
        else RL(p);
    }
}

void BR(tree *&p) {
    if (p->bal == 1) p->bal = 0;
    else if (p->bal == 0) {
        p->bal = -1;
        dec = 0;
    }
    else if (p->bal == -1) {
        if (p->left->bal <= 0) LL1(p);
        else LR(p);
    }
}

void del(tree *&r) {
    if (r->right != NULL) {
        del(r->right);
        if (dec == 1) BR(r);
    }
    else {
        t->data = r->data;
        t = r;
        r = r->left;
        dec = 1;
    }
}

void Delete_AVL(int x, tree *&p) {
    if (p == NULL) {
        return;
    }
    else if (p->data > x) {
        Delete_AVL(x, p->left);
        if (dec == 1) BL(p);
    }
    else if (p->data < x ) {
        Delete_AVL(x, p->right);
        if (dec == 1) BR(p);
    }
    else {
        t = p;
        if (t->left == NULL) {
            p = t->right;
            dec = 1;
        }
        else if (t->right == NULL) {
            p = t->left;
            dec = 1;
        }
        else {
            del(t->left);
            if (dec == 1) BL(p);
        }
        free(t);
    }
}

void AVL(int D, tree* &p) {
    if (p == NULL) {
        p = new tree;
        p->data = D;
        p->left = NULL;
        p->right = NULL;
        p->bal = 0;
        rost = 1;
    }
    else {
            if (p->data > D) {
                AVL(D, p->left);
                if (rost == 1) {
                    if (p->bal > 0) {
                        p->bal = 0;
                        rost = 0;
                    }
                    else if (p->bal == 0) {
                        p->bal = -1;
                        rost = 1;
                    }
                    else {
                        if (p->left->bal < 0) {
                            tree *q = p->left;
                            q->bal = 0;
                            p->bal = 0;
                            p->left = q->right;
                            q->right = p;
                            p = q;
                            rost = 0;
                            turn++;
                        }
                        else {
                            LR(p);
                            rost = 0;
                        }
                    }
                }
            }
            else if (p->data < D) {
                AVL(D, p->right);
                if (rost == 1) {
                    if (p->bal < 0) {
                        p->bal = 0;
                        rost = 0;
                    }
                    else if (p->bal == 0) {
                        p->bal = 1;
                        rost = 1;
                    }
                    else {
                        if (p->right->bal > 0) {
                            tree *q = p->right;
                            p->bal = 0;
                            q->bal = 0;
                            p->right = q->left;
                            q->left = p;
                            p = q;
                            rost = 0;
                            turn++;
                        }
                        else {
                            RL(p);
                            rost = 0;
                        }
                    }
                }
            }
    }
}
const long int n = 10;
int main() {
    srand(time(NULL));
    long int arr[n];
    long int data;
    long int vertex;
    long int count = 0;
    long int temp = 0;
    for(int i = 0; i < n; ++i) {
        arr[i] = rand() % 100;
    }
	printf("\n");
    tree *root = NULL;
    printf("AVL tree\n");
    for(int i = 0; i < n; ++i) {
        AVL(arr[i], root);
        count++;
    }
    print_tree(root);
    printf("\n\nCount of adding: %ld\n", count);
    printf("Count of turn: %ld\n", turn);
    turn = 0;
    //while (root != NULL) {
          print_tree(root);
		for(int i = 0; i < n; i++ ){
        printf("\n\n");
        printf("Enter vertex for delete: ");
		scanf("%d", &vertex);
        Delete_AVL(vertex, root);
        print_tree(root);
		}
    //}
    printf("\nCount of turn: %ld\n", turn);
    turn = 0;
	system("PAUSE");
}
