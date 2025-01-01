#include "stdio.h"
#include "malloc.h"
#include "UnitTests.h"

typedef struct Tree
{
    int _value;
    int _leaves;
    struct Tree *_left;
    struct Tree *_right;
} Tree;

Tree *MakeNode(int value) // creates leaf
{
    Tree *new = (Tree *)malloc(sizeof(Tree));
    new->_value = value;
    new->_leaves = 0;
    new->_left = NULL;
    new->_right = NULL;
    return new;
}

void ClearTree(Tree *tree)
{
    if (tree)
    {
        ClearTree(tree->_left);
        ClearTree(tree->_right);
        free(tree);
    }
}

int CountLeaves(Tree *tree)
{
    if (tree == NULL)
    {
        return 0;
    }

    if (tree->_left == NULL && tree->_right == NULL)
    {
        tree->_leaves = 1;
        return 1;
    }

    int leftLeaves = CountLeaves(tree->_left);
    int rightLeaves = CountLeaves(tree->_right);
    tree->_leaves = leftLeaves + rightLeaves;
    return tree->_leaves;
}

void TreeToMatrix(Tree *tree, int matrix[100][100], int row, int col)
{
    if (tree == NULL)
    {
        return;
    }
    matrix[row][col] = tree->_leaves;                         // Сохраняем количество листьев в матрицу
    TreeToMatrix(tree->_left, matrix, row + 1, col * 2);      // Левое поддерево
    TreeToMatrix(tree->_right, matrix, row + 1, col * 2 + 1); // Правое поддерево
}

void PrintMatrix(int matrix[100][100], int rows)
{
    for (int i = 0; i < rows; i++)
    {
        int flag = 0;
        for (int j = 0; j < 100; j++)
        {
            if (matrix[i][j] != 0)
            {
                ++flag;
                printf("%d ", matrix[i][j]);
            }
        }
        if (flag)
            printf("\n");
    }
}

// Тест: создание узла с заданным значением
int Test_MakeNode_with_value_no1(void)
{
    Tree *node = MakeNode(10);
    int status = 1;

    status *= ASSERT_INT_EQ(10, node->_value, "node->_value must be 10", "Test_CreateNode_with_value");
    status *= ASSERT_INT_EQ(0, node->_leaves, "node->_leaves must be 0", "Test_CreateNode_with_value");
    status *= ASSERT_PTR_EQ(NULL, node->_left, "node->_left must be NULL", "Test_CreateNode_with_value");
    status *= ASSERT_PTR_EQ(NULL, node->_right, "node->_right must be NULL", "Test_CreateNode_with_value");

    free(node);
    testing_result(status, "Test_CreateNode_with_value");
    return status;
}

// Тест: подсчет листьев в дереве
int Test_CountLeaves_complete_tree_no2(void)
{
    Tree *root = MakeNode(1);
    root->_left = MakeNode(2);
    root->_right = MakeNode(3);
    root->_left->_left = MakeNode(4);
    root->_left->_right = MakeNode(5);

    int status = 1;

    status *= ASSERT_INT_EQ(3, CountLeaves(root), "Total leaves must be 4", "Test_CountLeaves_complete_tree");
    status *= ASSERT_INT_EQ(3, root->_leaves, "root->_leaves must be 4", "Test_CountLeaves_complete_tree");

    ClearTree(root);
    testing_result(status, "Test_CountLeaves_complete_tree");
    return status;
}

// Тест: проверка подсчета листьев с пустым деревом
int Test_CountLeaves_empty_tree_no3(void)
{
    Tree *emptyRoot = NULL;

    int status = 1;
    status *= ASSERT_INT_EQ(0, CountLeaves(emptyRoot), "Leaves must be 0 for empty tree", "Test_CountLeaves_empty_tree");

    testing_result(status, "Test_CountLeaves_empty_tree");
    return status;
}

// Тест: подсчет листьев в дереве с одним узлом
int Test_CountLeaves_single_node_no4(void)
{
    Tree *singleNode = MakeNode(1);

    int status = 1;
    status *= ASSERT_INT_EQ(1, CountLeaves(singleNode), "Should be 1 leaf for a single node", "Test_CountLeaves_single_node");
    status *= ASSERT_INT_EQ(1, singleNode->_leaves, "singleNode->_leaves must be 1", "Test_CountLeaves_single_node");

    free(singleNode);
    testing_result(status, "Test_CountLeaves_single_node");
    return status;
}

// Тест: освобождение памяти дерева
int Test_ClearTree_no5(void)
{
    Tree *root = MakeNode(1);
    root->_left = MakeNode(2);
    root->_right = MakeNode(3);

    ClearTree(root); // Освобождение памяти
    int status = 1;

    root = NULL; // Устанавливаем указатель на null
    status *= ASSERT_PTR_EQ(NULL, root, "Root should be NULL after clearing", "Test_ClearTree");

    testing_result(status, "Test_ClearTree");
    return status;
}

// Тест: освобождение пустого дерева
int Test_ClearEmptyTree_no6(void)
{
    Tree *empty = NULL;
    ClearTree(empty);
    int status = 1;

    status *= ASSERT_PTR_EQ(NULL, empty, "Root should be NULL after clearing", "Test_ClearEmpyyTree");

    testing_result(status, "Test_ClearEmptyTree");
    return status;
}

// Тест: подсчет листьев в дереве с пустым правым узлом
int Test_CountLeaves_tree_with_empty_branch_no7(void)
{
    Tree *root = MakeNode(1);
    root->_left = MakeNode(2);
    root->_right = NULL; // Пустой правый узел
    root->_left->_left = MakeNode(3);
    root->_left->_right = MakeNode(4);

    int status = 1;
    CountLeaves(root);

    status *= ASSERT_INT_EQ(2, CountLeaves(root), "Total leaves must be 3", "Test_CountLeaves_tree_with_empty_branch");
    status *= ASSERT_INT_EQ(2, root->_left->_leaves, "Left child leaf count must be 2", "Test_CountLeaves_tree_with_empty_branch");

    ClearTree(root);
    testing_result(status, "Test_CountLeaves_tree_with_empty_branch");
    return status;
}

// Тест: структура дерева
int Test_StructureOfTree_no8(void)
{
    Tree *root = MakeNode(1);
    root->_left = MakeNode(2);
    root->_right = MakeNode(3);

    int status = 1;

    status *= ASSERT_INT_EQ(1, root->_value, "Root node value must be 1", "Test_StructureOfTree");
    status *= ASSERT_INT_EQ(2, root->_left->_value, "Left child value must be 2", "Test_StructureOfTree");
    status *= ASSERT_INT_EQ(3, root->_right->_value, "Right child value must be 3", "Test_StructureOfTree");

    ClearTree(root);
    testing_result(status, "Test_StructureOfTree");
    return status;
}

// Тест: проверка работы с односторонним деревом
int Test_OneSidedTree_no9(void)
{
    Tree *oneSidedTree = MakeNode(1);
    oneSidedTree->_left = MakeNode(2); // Только левое поддерево
    oneSidedTree->_left->_left = MakeNode(3);

    int status = 1;
    status *= ASSERT_INT_EQ(1, CountLeaves(oneSidedTree), "Only one leaf should be present", "Test_OneSidedTree");

    ClearTree(oneSidedTree);
    testing_result(status, "Test_OneSidedTree");
    return status;
}

// Тест: некорректное указание на узел
int Test_InvalidNode_no10(void)
{
    Tree *invalidNode = NULL;

    int status = 1;
    status *= ASSERT_INT_EQ(0, CountLeaves(invalidNode), "Leaves must be 0 for invalid node", "Test_InvalidNode");

    testing_result(status, "Test_InvalidNode");
    return status;
}

int main(void)
{
    int status = 1;
    status *= Test_MakeNode_with_value_no1();
    status *= Test_CountLeaves_complete_tree_no2();
    status *= Test_CountLeaves_empty_tree_no3();
    status *= Test_CountLeaves_single_node_no4();
    status *= Test_ClearTree_no5();
    status *= Test_ClearEmptyTree_no6();
    status *= Test_CountLeaves_tree_with_empty_branch_no7();
    status *= Test_StructureOfTree_no8();
    status *= Test_OneSidedTree_no9();
    status *= Test_InvalidNode_no10();

    testing_result(status, "Total_Tests");
    return 0;
}