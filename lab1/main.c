#define _CRT_SECURE_NO_WARNINGS


#include "funcs.h"
#include "tests.h"

int main() {
    Graph graph;
    bool included[MAX_VERTICES] = { false };

    if (!readGraph("input.txt", &graph)) {
        return 1;
    }

    if (findVertexCover(&graph, included, 0, 0)) {
        writeResult("output.txt", included, graph.n);
    }
    else {
        FILE* file = fopen("output.txt", "w");
        if (file) {
            fprintf(file, "0");
            fclose(file);
        }
    }

    test_readGraph_validFile_No1();
    test_readGraph_emptyFile_No2();
    test_isCovered_allVerticesIncluded_No3();
    test_isCovered_notCovered_No4();
    test_findVertexCover_minimalCover_No5();
    test_findVertexCover_impossible_No6();
    test_isCovered_emptyGraph_No7();
    test_isCovered_selfLoop_No8();
    test_findVertexCover_chainGraph_No9();
    test_findVertexCover_singleEdge_No10();

    printf("Все тесты успешно пройдены!\n");

    return 0;
}

