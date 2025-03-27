#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "UnitTests.h"

typedef struct AVLNode
{
    int key;
    int height;
    int size;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

int Maximum(int a, int b) { return a > b ? a : b; }

int GetHeight(AVLNode *node) { return node ? node->height : -1; }

int GetSize(AVLNode *node) { return node ? node->size : 0; }

void UpdateNode(AVLNode *node)
{
    if (node)
    {
        node->height = 1 + Maximum(GetHeight(node->left), GetHeight(node->right));
        node->size = 1 + GetSize(node->left) + GetSize(node->right);
    }
}

AVLNode *RotateRight(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    UpdateNode(y);
    UpdateNode(x);

    return x;
}

AVLNode *RotateLeft(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    UpdateNode(x);
    UpdateNode(y);

    return y;
}

AVLNode *Balance(AVLNode *node)
{
    if (!node)
        return node;

    int balanceFactor = GetHeight(node->right) - GetHeight(node->left);

    if (balanceFactor > 1)
    {
        if (GetHeight(node->right->right) - GetHeight(node->right->left) < 0)
            node->right = RotateRight(node->right);
        node = RotateLeft(node);
    }
    else if (balanceFactor < -1)
    {
        if (GetHeight(node->left->left) - GetHeight(node->left->right) < 0)
            node->left = RotateLeft(node->left);
        node = RotateRight(node);
    }

    UpdateNode(node);
    return node;
}

AVLNode *CreateNode(int key)
{
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->key = key;
    node->height = 0;
    node->size = 1;
    node->left = node->right = NULL;
    return node;
}

// Основные операции
AVLNode *InsertAtPosition(AVLNode *root, int k, int key)
{
    if (!root)
        return CreateNode(key);

    if (GetSize(root->left) >= k)
    {
        root->left = InsertAtPosition(root->left, k, key);
    }
    else
    {
        root->right = InsertAtPosition(root->right, k - GetSize(root->left) - 1, key);
    }

    UpdateNode(root);
    return Balance(root);
}

AVLNode *Search(AVLNode *root, int key)
{
    if (!root || root->key == key)
        return root;
    return Search(key < root->key ? root->left : root->right, key);
}

AVLNode *FindKth(AVLNode *root, int k)
{
    if (!root)
        return NULL;

    int leftSize = GetSize(root->left);
    if (leftSize == k)
        return root;
    return FindKth(k < leftSize ? root->left : root->right, k < leftSize ? k : k - leftSize - 1);
}

AVLNode *DeleteNode(AVLNode *root, int key)
{
    if (!root)
        return root;

    if (key < root->key)
    {
        root->left = DeleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = DeleteNode(root->right, key);
    }
    else
    {
        if (!root->left || !root->right)
        {
            AVLNode *temp = root->left ? root->left : root->right;
            if (!temp)
            {
                free(root);
                return NULL;
            }
            else
            {
                *root = *temp;
                free(temp);
            }
        }
        else
        {
            AVLNode *temp = root->right;
            while (temp->left)
                temp = temp->left;
            root->key = temp->key;
            root->right = DeleteNode(root->right, temp->key);
        }
    }

    if (!root)
        return root;
    UpdateNode(root);
    return Balance(root);
}

AVLNode *Merge(AVLNode *t1, AVLNode *t2)
{
    if (!t1)
        return t2;
    if (!t2)
        return t1;

    AVLNode *maxNode = t1;
    while (maxNode->right)
        maxNode = maxNode->right;
    maxNode->right = t2;

    return Balance(t1);
}

int test_InsertSearch_no1()
{
    AVLNode *root = NULL;
    int status = 1;

    root = InsertAtPosition(root, 0, 10);
    status &= ASSERT_PTR_NE(Search(root, 10), NULL, "After insert 10", "test_InsertSearch_no1");
    status &= ASSERT_INT_EQ(GetSize(root), 1, "Tree size after insert", "test_InsertSearch_no1");

    root = InsertAtPosition(root, 1, 20);
    status &= ASSERT_PTR_NE(Search(root, 20), NULL, "After insert 20", "test_InsertSearch_no1");
    status &= ASSERT_INT_EQ(GetSize(root), 2, "Tree size after second insert", "test_InsertSearch_no1");

    testing_result(status, "test_InsertSearch_no1");
    return status;
}

int test_FindKth_no2()
{
    AVLNode *root = NULL;
    int status = 1;

    root = InsertAtPosition(root, 0, 10);
    root = InsertAtPosition(root, 1, 20);
    root = InsertAtPosition(root, 1, 15);

    status &= ASSERT_INT_EQ(FindKth(root, 0)->key, 10, "0th element", "test_FindKth_no2");
    status &= ASSERT_INT_EQ(FindKth(root, 1)->key, 15, "1st element", "test_FindKth_no2");
    status &= ASSERT_INT_EQ(FindKth(root, 2)->key, 20, "2nd element", "test_FindKth_no2");

    testing_result(status, "test_FindKth_no2");
    return status;
}

int test_Delete_no3()
{
    AVLNode *root = NULL;
    int status = 1;

    root = InsertAtPosition(root, 0, 10);
    root = InsertAtPosition(root, 1, 20);
    root = DeleteNode(root, 20);

    status &= ASSERT_PTR_EQ(Search(root, 20), NULL, "After delete 20", "test_Delete_no3");
    status &= ASSERT_INT_EQ(GetSize(root), 1, "Size after delete", "test_Delete_no3");

    testing_result(status, "test_Delete_no3");
    return status;
}

int test_Merge_no4()
{
    AVLNode *t1 = NULL, *t2 = NULL;
    int status = 1;

    t1 = InsertAtPosition(t1, 0, 10);
    t2 = InsertAtPosition(t2, 0, 20);
    AVLNode *merged = Merge(t1, t2);

    status &= ASSERT_INT_EQ(GetSize(merged), 2, "Size must be 2", "test_Merge_no4");
    status &= ASSERT_PTR_NE(FindKth(merged, 1), NULL, "Second element exists", "test_Merge_no4");

    testing_result(status, "test_Merge_no4");
    return status;
}

int test_InsertBalance_no5()
{
    AVLNode *root = NULL;
    int status = 1;

    root = InsertAtPosition(root, 0, 10);
    root = InsertAtPosition(root, 0, 5);
    root = InsertAtPosition(root, 0, 3); // Must be balanced

    status &= ASSERT_INT_EQ(GetHeight(root), 1, "Height must be 1", "test_InsertBalance_no5");

    testing_result(status, "test_InsertBalance_no5");
    return status;
}

int test_DeleteNonExisting_no6()
{
    AVLNode *root = NULL;
    int status = 1;

    root = InsertAtPosition(root, 0, 10);
    root = DeleteNode(root, 99);

    status &= ASSERT_INT_EQ(GetSize(root), 1, "Size = 1", "test_DeleteNonExisting_no6");

    testing_result(status, "test_DeleteNonExisting_no6");
    return status;
}

int test_InsertMult_no7()
{
    AVLNode *root = NULL;
    int status = 1;

    root = InsertAtPosition(root, 0, 10); // [10]
    root = InsertAtPosition(root, 0, 5);  // [5,10]
    root = InsertAtPosition(root, 2, 15); // [5,10,15]

    status &= ASSERT_INT_EQ(FindKth(root, 2)->key, 15, "Insert at end", "test_InsertMult_no7");

    testing_result(status, "test_InsertMult_no7");
    return status;
}

int test_DeleteRoot_no8()
{
    AVLNode *root = NULL;
    int status = 1;

    root = InsertAtPosition(root, 0, 10);
    root = DeleteNode(root, 10);

    status &= ASSERT_PTR_EQ(root, NULL, "Tree is empty after root delete", "test_DeleteRoot_no8");

    testing_result(status, "test_DeleteRoot_no8");
    return status;
}

int test_FindKthNonExisting_no9()
{
    AVLNode *root = NULL;
    int status = 1;

    root = InsertAtPosition(root, 0, 10);
    status &= ASSERT_PTR_EQ(FindKth(root, 1), NULL, "Must be NULL", "test_FindKthNonExisting_no9");

    testing_result(status, "test_FindKthNonExisting_no9");
    return status;
}

int test_SearchNonExisting_no10()
{
    AVLNode *root = NULL;
    int status = 1;

    root = InsertAtPosition(root, 0, 10);
    status &= ASSERT_PTR_EQ(Search(root, 5), NULL, "Non-existent key", "test_SearchNonExisting_no10");

    testing_result(status, "test_SearchNonExisting_no10");
    return status;
}

int test_MegreWithEmpty_no11()
{
    AVLNode *t1 = NULL, *t2 = NULL;
    int status = 1;

    t1 = InsertAtPosition(t1, 0, 10);
    AVLNode *merged = Merge(t1, t2);

    status &= ASSERT_INT_EQ(GetSize(merged), 1, "Size must be 1", "test_MegreWithEmpty_no11");

    testing_result(status, "test_MegreWithEmpty_no11");
    return status;
}


int main()
{

    int status = 1;
    status *= test_InsertSearch_no1();
    status *= test_FindKth_no2();
    status *= test_Delete_no3();
    status *= test_Merge_no4();
    status *= test_InsertBalance_no5();
    status *= test_DeleteNonExisting_no6();
    status *= test_InsertMult_no7();
    status *= test_DeleteRoot_no8();
    status *= test_FindKthNonExisting_no9();
    status *= test_SearchNonExisting_no10();
    status *= test_MegreWithEmpty_no11();

    testing_result(status, "Total_Tests");
    return 0;
}