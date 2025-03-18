#include <stdio.h>
#include <stdlib.h>

typedef struct CartesianTree {
    int key;
    int priority;
    struct Treap* left;
    struct Treap* right;
} CartesianTree_t;

CartesianTree_t* CreateNode(int key) {
    srand(time(NULL));
    CartesianTree_t* tmp = (CartesianTree_t*)malloc(sizeof(CartesianTree_t));
    tmp->key = key;
    tmp->priority = rand();
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

CartesianTree_t* Find(CartesianTree_t* t, int key) {
    CartesianTree_t* cur = t;
    while (cur != NULL && cur->key != key) {
        if (key < cur->key) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }
    return cur;
}

CartesianTree_t* Merge(CartesianTree_t* l, CartesianTree_t* r) {
    if (!l)
        return r;
    if (!r)
        return l;
    if (l->priority < r->priority) {
        l->right = Merge(l->right, r);
        return l;
    }
    else {
        r->left = Merge(l, r->left);
        return r;
    }
}

void Split(CartesianTree_t* t, int key, CartesianTree_t** l, CartesianTree_t** r) {
    if (!t) {
        *l = NULL;
        *r = NULL;
    }
    else {
        if (t->key < key) {
            *l = t;
            Split(t->right, key, &(t->right), r);
        }
        else {
            *r = t;
            Split(t->left, key, l, &(t->left));
        }
    }
}

CartesianTree_t* Add(CartesianTree_t* t, int key) {
    CartesianTree_t* newNode = CreateNode(key);
    CartesianTree_t *l, *r;
    Split(t, key, &l, &r);
    CartesianTree_t* res = Merge(l, Merge(newNode, r));
    return res;
}

CartesianTree_t* Delete(CartesianTree_t* t, int key) {
    if (Find(t, key) == NULL)
        return t;
    CartesianTree_t *l, *r, *rl, *rr;
    Split(t, key, &l, &r);
    Split(r, key + 1, &rl, &rr);
    CartesianTree_t* res = Merge(l, rr);
    return res;
}
