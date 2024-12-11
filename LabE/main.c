#include "funcs.h"

int main() {
    TreeNode* root = create_node(10);
    root->left = create_node(5);
    root->right = create_node(15);
    root->left->left = create_node(2);
    root->left->right = create_node(7);
    root->right->right = create_node(20);

    calculate_subtree_width(root);

    print_tree_with_width(root, 0);

    free_tree(root);

    return 0;
}
