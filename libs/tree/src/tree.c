#include "tree.h"

#include <stdlib.h>

node_t* create_node(int data, color_t color, node_t *nil) {
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    node->color = color;
    node->left = node->right = node->parent = nil;
    return node;
}

tree_t * tree_create() {
    tree_t *t = malloc(sizeof(tree_t));
    t->nil = create_node(0, BLACK, NULL);
    t->root = t->nil;
    return t;
}

//finds min(N in node_t: N.value >= value) by B.value
node_t *findLUB(int value, tree_t *tree) {
    node_t *node = tree->root;
    node_t *result = tree->nil;

    while (node != tree->nil) {
        if(node->data >= value) {
            result = node;
            node = node->left;
        }
        else
            node = node->right;
    }

    return result;
}

direction_t get_direction(node_t *node) {
    return (node->parent->left == node) ? LEFT : RIGHT;
}

void free_node(tree_t *tree, node_t *node) {
    if(node == tree->nil)
        return;

    free_node(tree, node->right);
    free_node(tree, node->left);

    free(node);
}

void dispose_tree(tree_t *tree) {
    free_node(tree, tree->root);
    free(tree->nil);
    free(tree);
}

void rotate(tree_t *tree, node_t *node) {
    if (node == NULL || node->parent == NULL) return;

    node_t *P = node->parent;
    node_t *G = NULL;
    node_t *U = (get_direction(node) == LEFT ? P->right : P->left);
    direction_t direction = get_direction(node);
    unsigned char P_is_root = 0;
    direction_t P_dir = LEFT;

    if(P != tree->root) {
        G = P->parent;
        P_dir = get_direction(P);
    } else {
        P_is_root = 1;
    }

    if(direction == LEFT) {
        node_t *right_child = node->right;
        node->right = P;
        P->left = right_child;
        if(right_child)
            right_child->parent = P;
    } else {
        node_t *left_child = node->left;
        node->left = P;
        P->right = left_child;
        if(left_child)
            left_child->parent = P;
    }

    P->parent = node;
    if(U != NULL)
        U->parent = node;

    if(P_is_root) {
        tree->root = node;
        node->parent = NULL;
    } else {
        if(P_dir == LEFT)
            G->left = node;
        else
            G->right = node;
        node->parent = G;
    }
}

void BST_insert(tree_t *tree, node_t *node) {
    if(tree->root == tree->nil) {
        tree->root = node;
        node->parent = tree->nil;
        node->left = tree->nil;
        node->right = tree->nil;
        return;
    }

    node_t *cnode = tree->root;
    node_t *result = tree->nil;

    while (cnode != tree->nil) {
        result = cnode;
        if(cnode->data >= node->data)
            cnode = cnode->left;
        else
            cnode = cnode->right;
    }

    if(result->data >= node->data)
        result->left = node;
    else
        result->right = node;

    node->parent = result;
    node->left = tree->nil;
    node->right = tree->nil;
}

void fix_violations(tree_t *tree, node_t *new_node) {
    //1
    if(tree->root == new_node) {
        new_node->color = BLACK;
        return;
    }

    node_t *P = new_node->parent;
    //2
    if(P->color == BLACK)
        return;

    direction_t P_dir = get_direction(P);
    node_t *G = new_node->parent->parent;
    node_t* U = (P_dir == LEFT ? G->right : G->left);

    //3
    if(U != tree->nil && U->color == RED) {
        P->color = BLACK;
        U->color = BLACK;
        G->color = RED;
        fix_violations(tree, G);
        return;
    }

    //4
    if(get_direction(new_node) == RIGHT && get_direction(P) == LEFT) {
        rotate(tree, new_node);
        new_node = P;
    } else if(get_direction(new_node) == LEFT && get_direction(P) == RIGHT) {
        rotate(tree, new_node);
        new_node = P;
    }

    P = new_node->parent;
    G = new_node->parent->parent;
    U = (P_dir == LEFT ? G->right : G->left);

    //5
    P->color = BLACK;
    G->color = RED;
    rotate(tree, P);
}

void insert(tree_t *tree, node_t *new_node) {
    if(new_node == tree->nil) return;

    //BST_insertion
    new_node->color = RED;
    BST_insert(tree, new_node);

    //fix violations
    fix_violations(tree, new_node);
}

void transplant(tree_t *tree, node_t *u, node_t *v) {
    if (u->parent == tree->nil) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

node_t* minimum(tree_t *tree, node_t *x) {
    while (x->left != tree->nil) {
        x = x->left;
    }
    return x;
}

void delete_fixup(tree_t *tree, node_t *x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            node_t *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotate(tree, x->parent->right);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotate(tree, w->left);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotate(tree, x->parent->right);
                x = tree->root;
            }
        } else {
            node_t *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotate(tree, x->parent->left);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotate(tree, w->right);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotate(tree, x->parent->left);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

void rb_remove(tree_t *tree, node_t *z) {
    node_t *y = z;
    node_t *x;
    color_t yOriginalColor = y->color;

    if (z->left == tree->nil) {
        x = z->right;
        transplant(tree, z, z->right);
    } else if (z->right == tree->nil) {
        x = z->left;
        transplant(tree, z, z->left);
    } else {
        y = minimum(tree, z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK) {
        delete_fixup(tree, x);
    }

    free(z);
}