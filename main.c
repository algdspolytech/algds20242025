#include "code.h"

int main() {
    int num, K;
    Vertex* graph = read("input.txt", &num, &K);
    if (!graph) {
        return 1;
    }

    vertex_cover(graph, num, K);
    
    free(graph);

    return 0;
}