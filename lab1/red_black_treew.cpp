#include "red_black_treew.h"
#include <stdlib.h>


Node* rotateLeft(Node* root, Node* node) {
    Node* child = node->right;
    node->right = child->left;
    if (node->right != nullptr)
        node->right->parent = node;

    child->left = node;
    child->parent = node->parent;
    node->parent = child;
    if (child->parent == nullptr)
        root = child;
    else if (child->parent->left == node)
        child->parent->left = child;
    else
        child->parent->right = child;
    return root;
}


Node* rotateRight(Node* root, Node* node) {
    Node* child = node->left;
    node->left = child->right;
    if (node->left != nullptr)
        node->left->parent = node;
    child->right = node;
    child->parent = node->parent;
    node->parent = child;
    if (child->parent == nullptr)
        root = child;
    else if (child->parent->left == node)
        child->parent->left = child;
    else
        child->parent->right = child;
    return root;

}

Node* grandparent(Node* node) {
    if ((node != nullptr) && (node->parent != nullptr))
        return node->parent->parent;
    else
        return nullptr;
}

Node* uncle(Node* node) {
    Node* gp = grandparent(node);
    if (gp == nullptr)
        return nullptr;
    if (gp->left == node->parent)
        return gp->right;
    return gp->left;
}

Node* sibling(Node* node) {
    if (node == node->parent->left)
        return node->parent->right;
    else
        return node->parent->left;
}

Node* create_node(double data) {
    Node* node = (Mode*)malloc(sizeof(Node));
    node->left = nullptr;
    node->right = nullptr;
    node->data = data;
    node->parent = nullptr;
    node->color = 0;
}

Node* insert_case5(Node* root, Node* node) {
    Node* gp = grandparent(node);
    if (node->parent->left == node && gp->left == node->parent)
        root = rotateRight(root, gp);
    if (node->parent->right == node && gp->right == node->parent)
        root = rotateLeft(root, gp);
    node->parent->color = BLACK;
    gp->color = RED;
    return root;

}

Node* insert_case4(Node* root, Node* node) {
    Node* gp = grandparent(node);
    if (node->parent->right == node && gp->left == node->parent) {
        root = rotateLeft(root, node->parent);
        node = node->left;

    }
    if (node->parent->left == node && gp->right == node->parent) {
        root = rotateRight(root, node->parent);
        node = node->right;
    }
    return insert_case5(root, node);
}

Node* insert_case2(Node* root, Node* node);
Node* insert_case1(Node* root, Node* node) {
    if (node->parent == nullptr)
        node->color = BLACK;
    else
        root = insert_case2(root, node);
    return root;
}

Node* insert_case3(Node* root, Node* node) {
    Node* u = uncle(node);
    Node* gp = grandparent(node);
    if (u != nullptr && u->color == RED) {
        gp->color = RED;
        u->color = BLACK;
        node->parent->color = BLACK;
        root = insert_case1(root, gp);
    }
    else {
        root = insert_case4(root, node);
    }
    return root;
}

Node* insert_case2(Node* root, Node* node) {
    if (node->parent->color == BLACK)
        return root;
    else
        root = insert_case3(root, node);
    return root;
}

Node* insert_node(Node* root, double data) {
    Node* node = create_node(data);

    if (root == nullptr) {
        root = insert_case1(root, node);
        root = node;
        return root;
    }

    Node* cur_node = root;
    while (cur_node->left != nullptr || cur_node->right != nullptr) {
        if (node->data > cur_node->data) {
            if (cur_node->right != nullptr)
                cur_node = cur_node->right;
            else {
                break;
            }
        }
        else {
            if (cur_node->left != nullptr)
                cur_node = cur_node->left;
            else {
                break;
            }
        }

    }

    node->parent = cur_node;
    if (node->data > cur_node->data)
        cur_node->right = node;
    else
        cur_node->left = node;

    return insert_case1(root, node);

}


void replace_node(Node* node, Node* child) {
    if (child == nullptr) {
        if (node->parent->left == node)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        return;
    }

    child->parent = node->parent;
    if (node == node->parent->left) {
        node->parent->left = child;
    }
    else {
        node->parent->right = child;
    }
}

Node* delete_case6(Node* tree, Node* node) {
    Node* s = sibling(node);

    s->color = node->parent->color;
    node->parent->color = BLACK;

    if (node == node->parent->left) {
        s->right->color = BLACK;
        return rotateLeft(tree, node->parent);
    }
    else {
        s->left->color = BLACK;
        return rotateRight(tree, node->parent);
    }
}

Node* delete_case5(Node* tree, Node* node) {

    Node* s = sibling(node);

    if (s->color == BLACK) {
        if ((node == node->parent->left) && (s->right->color == BLACK) && (s->left->color == RED)) {
            s->color = RED;
            s->left->color = BLACK;
            tree = rotateRight(tree, s);
        }
        else if ((node == node->parent->right) && (s->left->color == BLACK) && (s->right->color == RED)) {
            s->color = RED;
            s->right->color = BLACK;
            tree = rotateLeft(tree, s);
        }
    }
    return delete_case6(tree, node);
}

Node* delete_case4(Node* tree, Node* node) {
    Node* s = sibling(node);

    if ((node->parent->color == RED) && (s->color == BLACK) && (s->left->color == BLACK) && (s->right->color == BLACK)) {
        s->color = RED;
        node->parent->color = BLACK;
        return tree;
    }
    else
        return delete_case5(tree, node);
}

Node* delete_case1(Node* tree, Node* node);
Node* delete_case3(Node* tree, Node* node) {
    Node* s = sibling(node);
    if ((node->parent->color == BLACK) && (s->color == BLACK) && (!s->left || s->left->color == BLACK) && (!s->right || s->right->color == BLACK))
    {
        s->color = RED;
        return delete_case1(tree, node->parent);
    }
    else
        return delete_case4(tree, node);
}

Node* delete_case2(Node* tree, Node* node) {
    Node* s = sibling(node);

    if (s->color == RED) {
        node->parent->color = RED;
        s->color = BLACK;
        if (node == node->parent->left)
            tree = rotateLeft(tree, node->parent);
        else
            tree = rotateRight(tree, node->parent);
    }
    return delete_case3(tree, node);
}

Node* delete_case1(Node* tree, Node* node) {
    if (node->parent != NULL)
        return delete_case2(tree, node);

    return nullptr;
}

Node* delete_one_child(Node* tree, Node* node) {
    Node* child;
    if (node->right == nullptr)
        child = node->left;
    else
        child = node->right;

    if (node->color == BLACK) {
        if (child == nullptr) {
            node->data = NULL;
            return delete_case1(tree, node);
        }
        else {
            replace_node(node, child);
            child->color = BLACK;
        }
            
    }
    else
        replace_node(node, child);
    free(node);
    return tree;
}

Node* delete_two_children(Node* tree, Node* node) { //максимум левой ветки
    Node* cur_node = node->left;
    while (cur_node->right != nullptr) {
        cur_node = cur_node->right;
    }
    node->data = cur_node->data;
    return delete_one_child(tree, cur_node);
}

Node* delete_node(Node* tree, Node* node) {
    if (node->right != nullptr && node->left != nullptr)
        return delete_two_children(tree, node);
    else
        return delete_one_child(tree, node);
}

Node* search(Node* root, double data) {

    Node* cur_node = root;
    while (cur_node->data != data) {
        if (data > cur_node->data)
            cur_node = cur_node->right;
        else
            cur_node = cur_node->left;
        if (cur_node == nullptr)
            return nullptr;
    }
    return cur_node;

}
