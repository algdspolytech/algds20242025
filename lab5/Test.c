#include "BSearchTree.h"
 
void TestCreate_no1() {
    BinaryTreeNode* root = NULL;
    root = Create(76);
    if (root->size == 1) {
        printf("Test1 - passed\n");
    }
    else {
        printf("Test1 - not passed\n");
    }
}

void TestUpdateSize_no2() {
    BinaryTreeNode* root = NULL;
    root = Create(76);
    root->left = Create(32);
    root->right = Create(89);
    UpdateSize(root);
    if (root->size == 3) {
        printf("Test2 - passed\n");
    }
    else {
        printf("Test2 - not passed\n");
    }
}

void TestInsert_no3() {
    BinaryTreeNode* root = NULL;
    int values[] = { 45, 56, 9 };

    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++){
        root = Insert(root, values[i]);
    }
    if(root->size == 3){
        printf("Test3 - passed\n");
    }
    else {
        printf("Test3 - not passed\n");
    }
}

void TestFindNumElem_no4() {
    BinaryTreeNode* root = NULL;
    int values[] = { 40, 56, 33 };
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        root = Insert(root, values[i]);
    }
    int elem = 56;
    if (FindNumElem(root, elem) == 3) {
        printf("Test4 - passed\n");
    }
    else {
        printf("Test4 - not passed\n");
    }
}  

void TestFindNumElem_ifNoEl_no5() {
    BinaryTreeNode* root = NULL;
    int values[] = { 40, 56, 33 };
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        root = Insert(root, values[i]);
    }
    int elem = 77;
    if (FindNumElem(root, elem) == -1) {
        printf("Test5 - passed\n");
    }
    else {
        printf("Test5 - not passed\n");
    }
}

void TestFindElemInNum_no6() {
    BinaryTreeNode* root = NULL;
    int values[] = { 40, 56, 33 };
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        root = Insert(root, values[i]);
    }
    int num = 2;
    if (FindElemInNum(root, num)->key == 40) {
        printf("Test6 - passed\n");
    }
    else {
        printf("Test6 - not passed\n");
    }
}

void TestFindElemInNum_ifNoNum_no7() {
    BinaryTreeNode* root = NULL;
    int values[] = { 40, 56, 33 };
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        root = Insert(root, values[i]);
    }
    int num = 6;
    if (FindElemInNum(root, num) == NULL) {
        printf("Test7 - passed\n");
    }
    else {
        printf("Test7 - not passed\n");
    }
}

void TestFindElemNumMinusK_no8() {
    BinaryTreeNode* root = NULL;
    int values[] = { 40, 56, 33 };
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        root = Insert(root, values[i]);
    }
    int num = 56;
    int k = 2;
    if (FindElemNumMinusK(root, num, k)->key == 33) {
        printf("Test8 - passed\n");
    }
    else {
        printf("Test8 - not passed\n");
    }
}

void TestFindElemNumMinusK_ifKInvalid_no9() {
    BinaryTreeNode* root = NULL;
    int values[] = { 40, 56, 33 };
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        root = Insert(root, values[i]);
    }
    int num = 56;
    int k = 3;
    if (FindElemNumMinusK(root, num, k) == NULL) {
        printf("Test9 - passed\n");
    }
    else {
        printf("Test9 - not passed\n");
    }
}

void TestPrint_no10() {
    BinaryTreeNode* root = NULL;
    int values[] = { 40, 56, 33 };
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        root = Insert(root, values[i]);
    }
    printf("Test10 - ");
    Print(root);      //ожидается 33 40 56
    printf("\n");
}

void RunAllTests() {
    TestCreate_no1();
    TestUpdateSize_no2();
    TestInsert_no3();
    TestFindNumElem_no4();
    TestFindNumElem_ifNoEl_no5();
    TestFindElemInNum_no6();
    TestFindElemInNum_ifNoNum_no7();
    TestFindElemNumMinusK_no8();
    TestFindElemNumMinusK_ifKInvalid_no9();
    TestPrint_no10();
}

int main() {
    RunAllTests();
    return 0;
}                     
