#include <iostream>
#include <memory>
#include "rbtree.h"


void RBTree::rotateLeft(std::shared_ptr<Node>& root, std::shared_ptr<Node>& pt) {
    std::shared_ptr<Node> pt_right = pt->right;

    pt->right = pt_right->left;

    if (pt->right != nullptr)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_right;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;

    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

void RBTree::rotateRight(std::shared_ptr<Node>& root, std::shared_ptr<Node>& pt) {
    std::shared_ptr<Node> pt_left = pt->left;

    pt->left = pt_left->right;

    if (pt->left != nullptr)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_left;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;

    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

void RBTree::fixViolation(std::shared_ptr<Node>& root, std::shared_ptr<Node>& pt) {
    std::shared_ptr<Node> parent_pt = nullptr;
    std::shared_ptr<Node> grand_parent_pt = nullptr;

    while ((pt != root) && (pt->color != BLACK) &&
        (pt->parent->color == RED)) {

        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        /*  Case : A
            Parent of pt is left child of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->left) {

            std::shared_ptr<Node> uncle_pt = grand_parent_pt->right;

            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if (uncle_pt != nullptr && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }

            else {
                /* Case : 2
                   pt is right child of its parent
                   Left-rotation required */
                if (pt == parent_pt->right) {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                   pt is left child of its parent
                   Right-rotation required */
                rotateRight(root, grand_parent_pt);
                std::swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }

        /* Case : B
           Parent of pt is right child of Grand-parent of pt */
        else {
            std::shared_ptr<Node> uncle_pt = grand_parent_pt->left;

            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->left) {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
                rotateLeft(root, grand_parent_pt);
                std::swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = BLACK;
}

void RBTree::insert(const int& data) {
    std::shared_ptr<Node> pt = std::make_shared<Node>(data);

    if (root == nullptr) {
        root = pt;
        root->color = BLACK;
        return;
    }

    std::shared_ptr<Node> parent = nullptr;
    std::shared_ptr<Node> current = root;

    while (current != nullptr) {
        parent = current;
        if (pt->data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    pt->parent = parent;

    if (parent == nullptr)
        root = pt;
    else if (pt->data < parent->data)
        parent->left = pt;
    else
        parent->right = pt;

    fixViolation(root, pt);
}

void RBTree::inorder() { inorderHelper(root); }
void RBTree::inorderHelper(std::shared_ptr<Node> root) {
    if (root == nullptr)
        return;

    inorderHelper(root->left);
    std::cout << root->data << " ";
    inorderHelper(root->right);
}

void RBTree::levelOrder() { levelOrderHelper(root); }
void RBTree::levelOrderHelper(std::shared_ptr<Node> root) {
    if (root == nullptr)
        return;

    if (root->left != nullptr)
        std::cout << root->left->data << " ";
    if (root->right != nullptr)
        std::cout << root->right->data << " ";

    levelOrderHelper(root->left);
    levelOrderHelper(root->right);
}

