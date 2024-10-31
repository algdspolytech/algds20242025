#include "method.h"

void dfs(matrix* mat, unsigned int cur, unsigned int find, int* visited, bool* res)
{
    if (cur == find) (*res) = true;
    visited[cur] = 1;
    for(int i = 0; i < mat->height; ++i)
    {
        int elem = mat->elems[cur][i]; 
        int visit = visited[i];
        if((elem == 1) && (i != cur) && (visit == 0)) 
        {
            dfs(mat, i, find, visited, res);
        }
    }
}

