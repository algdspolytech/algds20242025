# include "header.h"

int main() {
    test_createNode();
    test_addNode();
    test_addDuplicateNode();
    test_loadTreeFromFile();
    test_loadEmptyTreeFromFile();
    test_freeTree();
    test_loadingFromFileWithExtraNewlines();
    test_nullFileLoading();
    test_loadTreeFromFileWithIncorrectFormat();
    test_createNodeWithEmptyString();
    printf("success");
    return 0;
}