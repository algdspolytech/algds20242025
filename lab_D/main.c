#include "stdio.h"
#include "malloc.h"
#include "UnitTests.h"

typedef struct
{
    unsigned int _n;
    int **_matrix;
    int _first_vert;
    int _second_vert;
    int _path_len;
} Graph;

typedef struct
{
    Graph graph;
    int *members
} Branch;

Graph CreateEmptyGraph(int num)
{
    Graph tmp = {num, NULL, 0, 0, 0};
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

Branch BranchFromGraph(Graph graph)
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

Graph ReadGraph(const char *filename)
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
        return CreateEmptyGraph(0);
    }

    Graph tmp = CreateEmptyGraph(num);

    for (int i = 0; i < num; ++i)
    {
        tmp._matrix[i][i] = 1;
    }
    fscanf(file, "%i", &tmp._first_vert);
    fscanf(file, "%i", &tmp._second_vert);
    fscanf(file, "%i", &tmp._path_len);

    int first;
    int second;

    while (fscanf(file, "%i", &first) != EOF)
    {
        fscanf(file, "%i", &second);
        tmp._matrix[first - 1][second - 1] = 1;
        tmp._matrix[second - 1][first - 1] = 1;
    }

    return tmp;
}

void DFS(Branch *branch, int vertex)
{
    if (branch->graph._n)
    {
        if (vertex >= branch->graph._n)
        {
            printf("Wrong input\n");
            exit(3);
        }
        branch->members[vertex] = 1;
        for (int i = 0; i < branch->graph._n; ++i)
        {
            if (branch->graph._matrix[vertex][i] && (!branch->members[i]))
            {
                DFS(branch, i);
            }
        }
    }
}

int FindPath(Graph graph, int ver1, int ver2)
{
    Branch br = BranchFromGraph(graph);
    DFS(&br, ver1);
    if (br.members)
    {
        return br.members[ver2];
    }
    else
        return 0;
}

void LongestPath(Graph graph, int *maxlen, int *maxpath, int curlen, int *curpath, int *visited, int curvert)
{
    if (graph._n)
    {
        visited[curvert - 1] = 1;
        curpath[curlen] = curvert;
        if (curvert == graph._second_vert)
        {
            if (curlen > *maxlen)
            {
                for (int i = 0; i < graph._n; ++i)
                {
                    maxpath[i] = curpath[i];
                }
                *maxlen = curlen + 1;
            }
            visited[curvert - 1] = 0;
            curpath[curlen] = 0;
            return;
        }
        for (int i = 0; i < graph._n; ++i)
        {
            if (graph._matrix[curvert - 1][i] && !visited[i])
            {
                LongestPath(graph, maxlen, maxpath, curlen + 1, curpath, visited, i + 1);
            }
        }
        visited[curvert - 1] = 0;
        curpath[curlen] = 0;
    }
}

int *LongPath(Graph graph)
{
    int *res = (int *)malloc(sizeof(int));
    res[0] = 0;
    int *max = (int *)malloc(sizeof(int) * graph._n);
    int *cur = (int *)malloc(sizeof(int) * graph._n);
    int *vis = (int *)malloc(sizeof(int) * graph._n);
    for (int i = 0; i < graph._n; ++i)
    {
        max[i] = 0;
        cur[i] = 0;
        vis[i] = 0;
    }
    int maxlen = 0;

    LongestPath(graph, &maxlen, max, 0, cur, vis, graph._first_vert);

    if (maxlen >= graph._path_len)
    {
        FILE *file = fopen("output.txt", "w");
        res = (int *)malloc(sizeof(int) * maxlen);
        for (int i = 0; i < maxlen; ++i)
        {
            res[i] = max[i];
            fprintf(file, "%i ", res[i]);
        }
        fclose(file);
    }
    else
    {
        FILE *file = fopen("output.txt", "w");
        fprintf(file, "%i", 0);
        fclose(file);
    }
    return res;
}

// Test: CreateEmptyGraph with arg 0
int Test_CreateEmptyMatrix_no1(void)
{
    Graph a = CreateEmptyGraph(0);
    int status = 1;

    status *= ASSERT_INT_EQ(0, a._n, "_n must be 0", "Test_CreateEmptyMatrix_no1");
    status *= ASSERT_PTR_EQ(NULL, a._matrix, "_matrix must be NULL", "Test_CreateEmptyMatrix_no1");

    testing_result(status, "Test_CreateEmptyMatrix_no1");
    return status;
}

// Test: CreateEmptyGraph with arg 1
int Test_CreateEmptyMatrix_no2(void)
{
    Graph a = CreateEmptyGraph(1);
    int status = 1;

    status *= ASSERT_INT_EQ(1, a._n, "_n must be 1", "Test_CreateEmptyMatrix_no2");
    status *= ASSERT_INT_EQ(0, a._matrix[0][0], "_matrix[0][0] must be 0", "Test_CreateEmptyMatrix_no2");

    testing_result(status, "Test_CreateEmptyMatrix_no2");
    return status;
}

// Test: Branch from empty matrix
int Test_BranchFromMatrix_no3(void)
{
    Graph a = {0, NULL};
    Branch b = BranchFromGraph(a);
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
    Graph a = {1, tmp};
    Branch b = BranchFromGraph(a);
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
    DFS(&b, 0);
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
    DFS(&b, 0);
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
    DFS(&b, 0);
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
    Graph b = {0, NULL};
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
    Graph b = {2, a};
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
    Graph b = {2, a};
    int res = FindPath(b, 0, 1);
    int status = 1;

    status *= ASSERT_INT_EQ(2, b._n, "_n must be 2", "Test_FindPath_no10");
    status *= ASSERT_INT_EQ(0, res, "res must be 1", "Test_FindPath_no10");
    testing_result(status, "Test_FindPath_no10");
    return status;
}

int Test_LongestPathExist_no11(void)
{
    Graph graph;
    graph._n = 3;
    graph._first_vert = 1;
    graph._path_len = 2;
    graph._second_vert = 3;
    graph._matrix = (int **)malloc(sizeof(int *) * 3);
    for (int i = 0; i < 3; ++i)
    {
        graph._matrix[i] = (int *)malloc(sizeof(int) * 3);
        for (int j = 0; j < 3; ++j)
        {
            graph._matrix[i][j] = 1;
        }
    }
    int *res = LongPath(graph);
    int status = 1;

    status *= ASSERT_INT_EQ(1, res[0], "res[0] must be 1", "Test_LongestPathExist_no11");
    status *= ASSERT_INT_EQ(2, res[1], "res[1] must be 2", "Test_LongestPathExist_no11");
    status *= ASSERT_INT_EQ(3, res[2], "res[2] must be 3", "Test_LongestPathExist_no11");
    testing_result(status, "Test_LongestPathExist_no11");
    return status;
}

int Test_LongestPathDoNotExist_no12(void)
{
    Graph graph;
    graph._n = 3;
    graph._first_vert = 1;
    graph._path_len = 4;
    graph._second_vert = 3;
    graph._matrix = (int **)malloc(sizeof(int *) * 3);
    for (int i = 0; i < 3; ++i)
    {
        graph._matrix[i] = (int *)malloc(sizeof(int) * 3);
        for (int j = 0; j < 3; ++j)
        {
            graph._matrix[i][j] = 1;
        }
    }
    int *res = LongPath(graph);
    int status = 1;

    status *= ASSERT_INT_EQ(0, res[0], "res[0] must be 0", "Test_LongestPathDoNotExist_no12");
    testing_result(status, "Test_LongestPathDoNotExist_no12");
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
    status *= Test_FindPathTwoBranch_no10();
    status *= Test_LongestPathExist_no11();
    status *= Test_LongestPathDoNotExist_no12();

    testing_result(status, "Total_Tests");
    return 0;
}