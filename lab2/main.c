#include "stdio.h"
#include "malloc.h"
#include "UnitTests.h"

typedef struct
{
    unsigned int _n;
    int **_matrix
} Matrix;

typedef struct
{
    Matrix graph;
    int *members
} Branch;

Matrix CreateEmptyMatrix(int num)
{
    Matrix tmp = {num, NULL};
    if (!num)
    {
        return tmp;
    }
    tmp._matrix = (int **)malloc(num * sizeof(int *));
    for (int i = 0; i < num; ++i)
    {
        tmp._matrix[i] = (int *)malloc(num * sizeof(int));
        for (int j = 0; j < num; ++j)
        {
            tmp._matrix[i][j] = 0;
        }
    }
    return tmp;
}

Branch BranchFromMatrix(Matrix graph)
{
    Branch tmp = {graph, NULL};
    if (graph._n)
    {
        tmp.members = (int *)malloc(graph._n * sizeof(int));
        for (int i = 0; i < graph._n; ++i)
        {
            tmp.members[i] = 0;
        }
    }
    return tmp;
}

Matrix ReadMatrix(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int num = 0;
    if ((fscanf(file, "%i", &num) == EOF) || !num)
    {
        printf("Empty file\n");
        return CreateEmptyMatrix(0);
    }

    Matrix tmp = CreateEmptyMatrix(num);
    if (!num)
    {
        return tmp;
    }
    for (int i = 0; i < num; ++i)
    {
        for (int j = 0; j < num; ++j)
        {
            if (fscanf(file, "%i", &tmp._matrix[i][j]) == EOF)
            {
                printf("Wrong data in file\n");
                exit(2);
            }
        }
    }
    return tmp;
}

void DFS(Branch branch, int vertex)
{
    if (branch.graph._n)
    {
        if (vertex >= branch.graph._n)
        {
            printf("Wrong input\n");
            exit(3);
        }
        branch.members[vertex] = 1;
        for (int i = 0; i < branch.graph._n; ++i)
        {
            if (branch.graph._matrix[vertex][i] && (!branch.members[i]))
            {
                DFS(branch, i);
            }
        }
    }
}

int FindPath(Matrix graph, int ver1, int ver2)
{
    Branch br = BranchFromMatrix(graph);
    DFS(br, ver1);
    if (br.members)
    {
        return br.members[ver2];
    }
    else
        return 0;
}

// Test: CreateEmptyMatrix with arg 0
int Test_CreateEmptyMatrix_no1(void)
{
    Matrix a = CreateEmptyMatrix(0);
    int status = 1;

    status *= ASSERT_INT_EQ(0, a._n, "_n must be 0", "Test_CreateEmptyMatrix_no1");
    status *= ASSERT_PTR_EQ(NULL, a._matrix, "_matrix must be NULL", "Test_CreateEmptyMatrix_no1");

    testing_result(status, "Test_CreateEmptyMatrix_no1");
    return status;
}

// Test: CreateEmptyMatrix with arg 1
int Test_CreateEmptyMatrix_no2(void)
{
    Matrix a = CreateEmptyMatrix(1);
    int status = 1;

    status *= ASSERT_INT_EQ(1, a._n, "_n must be 1", "Test_CreateEmptyMatrix_no2");
    status *= ASSERT_INT_EQ(0, a._matrix[0][0], "_matrix[0][0] must be 0", "Test_CreateEmptyMatrix_no2");

    testing_result(status, "Test_CreateEmptyMatrix_no2");
    return status;
}

// Test: Branch from empty matrix
int Test_BranchFromMatrix_no3(void)
{
    Matrix a = {0, NULL};
    Branch b = BranchFromMatrix(a);
    int status = 1;

    status *= ASSERT_INT_EQ(0, b.graph._n, "_n must be 0", "Test_BranchFromMatrix_no3");
    status *= ASSERT_PTR_EQ(NULL, b.graph._matrix, "_matrix must be NULL", "Test_BranchFromMatrix_no3");
    status *= ASSERT_PTR_EQ(NULL, b.members, "members must be NULL", "Test_BranchFromMatrix_no3");

    testing_result(status, "Test_BranchFromMatrix_no3");
    return status;
}

// Test: Branch from non empty matrix
int Test_BranchFromMatrix_no4(void)
{
    int **tmp = (int **)malloc(sizeof(int *));
    tmp[0] = (int *)malloc(sizeof(int));
    tmp[0][0] = 1;
    Matrix a = {1, tmp};
    Branch b = BranchFromMatrix(a);
    int status = 1;

    status *= ASSERT_INT_EQ(1, b.graph._n, "_n must be 0", "Test_BranchFromMatrix_no4");
    status *= ASSERT_INT_EQ(1, b.graph._matrix[0][0], "_matrix[0][0] must be NULL", "Test_BranchFromMatrix_no4");
    status *= ASSERT_INT_EQ(0, b.members[0], "members[0] must be 0", "Test_BranchFromMatrix_no4");

    testing_result(status, "Test_BranchFromMatrix_no4");
    return status;
}

// Test: DFS on empty Branch
int Test_DFSEmpty_no5(void)
{
    Branch b = {{0, NULL}, NULL};
    DFS(b, 0);
    int status = 1;

    status *= ASSERT_INT_EQ(0, b.graph._n, "_n must be 0", "Test_DFS_no5");
    status *= ASSERT_PTR_EQ(NULL, b.graph._matrix, "_matrix must be NULL", "Test_DFS_no5");
    status *= ASSERT_PTR_EQ(NULL, b.members, "members must be NULL", "Test_DFS_no5");

    testing_result(status, "Test_DFS_no5");
    return status;
}

// Test: DFS on one-branch graph
int Test_DFSOneBranch_no6(void)
{
    int **a = (int **)malloc(sizeof(int *) * 2);
    a[0] = (int *)malloc(sizeof(int) * 2);
    a[1] = (int *)malloc(sizeof(int) * 2);
    a[0][0] = 1;
    a[1][0] = 1;
    a[0][1] = 1;
    a[1][1] = 1;
    int *mem = (int *)malloc(sizeof(int) * 2);
    mem[0] = 0;
    mem[1] = 0;
    Branch b = {{2, a}, mem};
    DFS(b, 0);
    int status = 1;

    status *= ASSERT_INT_EQ(2, b.graph._n, "_n must be 2", "Test_DFS_no6");
    status *= ASSERT_INT_EQ(1, b.members[0], "b.members[0] must be 1", "Test_DFS_no6");
    status *= ASSERT_INT_EQ(1, b.members[1], "b.members[1] must be 1", "Test_DFS_no6");
    testing_result(status, "Test_DFS_no6");
    return status;
}

// Test: DFS on two-branch graph
int Test_DFSTwoBranch_no7(void)
{
    int **a = (int **)malloc(sizeof(int *) * 2);
    a[0] = (int *)malloc(sizeof(int) * 2);
    a[1] = (int *)malloc(sizeof(int) * 2);
    a[0][0] = 1;
    a[1][0] = 0;
    a[0][1] = 0;
    a[1][1] = 1;
    int *mem = (int *)malloc(sizeof(int) * 2);
    mem[0] = 0;
    mem[1] = 0;
    Branch b = {{2, a}, mem};
    DFS(b, 0);
    int status = 1;

    status *= ASSERT_INT_EQ(2, b.graph._n, "_n must be 2", "Test_DFS_no7");
    status *= ASSERT_INT_EQ(1, b.members[0], "b.members[0] must be 1", "Test_DFS_no7");
    status *= ASSERT_INT_EQ(0, b.members[1], "b.members[1] must be 1", "Test_DFS_no7");
    testing_result(status, "Test_DFS_no7");
    return status;
}

// Test: FindPath on empty matrix
int Test_FindPathEmpty_no8(void)
{
    Matrix b = {0, NULL};
    int res = FindPath(b, 0, 0);
    int status = 1;

    status *= ASSERT_INT_EQ(0, b._n, "_n must be 0", "Test_FindPath_no8");
    status *= ASSERT_PTR_EQ(NULL, b._matrix, "_matrix must be NULL", "Test_FindPath_no8");
    status *= ASSERT_INT_EQ(0, res, "res must be 0", "Test_FindPath_no8");

    testing_result(status, "Test_FindPath_no8");
    return status;
}

// Test: FindPath on one-branch graph
int Test_FindPathOneBranch_no9(void)
{
    int **a = (int **)malloc(sizeof(int *) * 2);
    a[0] = (int *)malloc(sizeof(int) * 2);
    a[1] = (int *)malloc(sizeof(int) * 2);
    a[0][0] = 1;
    a[1][0] = 1;
    a[0][1] = 1;
    a[1][1] = 1;
    Matrix b = {2, a};
    int res = FindPath(b, 0, 1);
    int status = 1;

    status *= ASSERT_INT_EQ(2, b._n, "_n must be 2", "Test_FindPath_no9");
    status *= ASSERT_INT_EQ(1, res, "res must be 1", "Test_FindPath_no9");
    testing_result(status, "Test_FindPath_no9");
    return status;
}

int Test_FindPathTwoBranch_no10(void)
{
    int **a = (int **)malloc(sizeof(int *) * 2);
    a[0] = (int *)malloc(sizeof(int) * 2);
    a[1] = (int *)malloc(sizeof(int) * 2);
    a[0][0] = 1;
    a[1][0] = 0;
    a[0][1] = 0;
    a[1][1] = 1;
    Matrix b = {2, a};
    int res = FindPath(b, 0, 1);
    int status = 1;

    status *= ASSERT_INT_EQ(2, b._n, "_n must be 2", "Test_FindPath_no9");
    status *= ASSERT_INT_EQ(0, res, "res must be 1", "Test_FindPath_no9");
    testing_result(status, "Test_FindPath_no9");
    return status;
}

int main(void)
{
    int status = 1;
    status *= Test_CreateEmptyMatrix_no1();
    status *= Test_CreateEmptyMatrix_no2();
    status *= Test_BranchFromMatrix_no3();
    status *= Test_BranchFromMatrix_no4();
    status *= Test_DFSEmpty_no5();
    status *= Test_DFSOneBranch_no6();
    status *= Test_DFSTwoBranch_no7();
    status *= Test_FindPathEmpty_no8();
    status *= Test_FindPathOneBranch_no9();
    // status *= Test_FindPathTwoBranch_no10();

    testing_result(status, "Total_Tests");

    return 0;
}