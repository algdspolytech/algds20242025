#include "labE.h"

void createNode_emptyTree_returnValidVal_no1();
void createNode_newNodeLeafCountZero_returnValidVal_no2();
void fillAndCountLeaves_nullInput_returnZero_no3();
void fillAndCountLeaves_singleLeaf_returnOne_no4();
void fillAndCountLeaves_onlyLeftChild_returnOne_no5();
void fillAndCountLeaves_twoLeaves_returnTwo_no6();
void fillMatrix_singleNode_returnZero_no7();
void fillMatrix_leftChild_returnZero_no8();
void printTree_nullRoot_noCrash_no9();
void printTree_singleNode_noCrash_no10();
int main() {
    Node* root = createNode();
    root->left = createNode();
    root->right = createNode();
    root->left->left = createNode();
    root->left->right = createNode();
    root->right->right = createNode();

    fillAndCountLeaves(root);

    int maxDepth = 3; // можно вычислять динамически. но по условию не требуется
    printTree(root, maxDepth);

    free(root->left->left);
    free(root->left->right);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);

    // тесты
    void createNode_emptyTree_returnValidVal_no1();
    void createNode_newNodeLeafCountZero_returnValidVal_no2();
    void fillAndCountLeaves_nullInput_returnZero_no3();
    void fillAndCountLeaves_singleLeaf_returnOne_no4();
    void fillAndCountLeaves_onlyLeftChild_returnOne_no5();
    void fillAndCountLeaves_twoLeaves_returnTwo_no6();
    void fillMatrix_singleNode_returnZero_no7();
    void fillMatrix_leftChild_returnZero_no8();
    void printTree_nullRoot_noCrash_no9();
    void printTree_singleNode_noCrash_no10();
    return 0;
}
