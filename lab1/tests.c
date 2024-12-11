#include "tree.h"

#include <assert.h>

#include <string.h>

// Функция для сравнения дерева с ожидаемой структурой
void compare_tree(Node * root,
    const char * expected[], int * index, int depth) {
    if (depth > 0) {
        char buffer[256] = "";
        for (int i = 0; i < depth; i++)
            strcat(buffer, " ");
        strcat(buffer, root -> name);
        assert(strcmp(buffer, expected[ * index]) == 0);
        ( * index) ++;
    }

    for (int i = 0; i < root -> children_count; i++) {
        compare_tree(root -> children[i], expected, index, depth + 1);
    }
}

void TestCreateNode_ValidName_no1() {
    Node * node = create_node("TestNode");
    assert(strcmp(node -> name, "TestNode") == 0);
    assert(node -> children == NULL);
    assert(node -> children_count == 0);
    assert(node -> children_capacity == 0);
    free_tree(node);
}

void TestAddPath_SinglePath_no2() {
    Node * root = create_node("");
    add_path(root, "Folder1");

    assert(root -> children_count == 1);
    assert(strcmp(root -> children[0] -> name, "Folder1") == 0);
    free_tree(root);
}

void TestAddPath_NestedPath_no3() {
    Node * root = create_node("");
    add_path(root, "Folder1\\Subfolder1");

    assert(root -> children_count == 1);
    assert(strcmp(root -> children[0] -> name, "Folder1") == 0);
    assert(root -> children[0] -> children_count == 1);
    assert(strcmp(root -> children[0] -> children[0] -> name, "Subfolder1") == 0);
    free_tree(root);
}

void TestAddPath_MultiplePaths_no4() {
    Node * root = create_node("");
    add_path(root, "Folder1\\Subfolder1");
    add_path(root, "Folder1\\Subfolder2");

    assert(root -> children_count == 1);
    assert(strcmp(root -> children[0] -> name, "Folder1") == 0);
    assert(root -> children[0] -> children_count == 2);
    assert(strcmp(root -> children[0] -> children[0] -> name, "Subfolder1") == 0);
    assert(strcmp(root -> children[0] -> children[1] -> name, "Subfolder2") == 0);
    free_tree(root);
}

void TestSortChildren_LexicographicOrder_no5() {
    Node * root = create_node("Root");
    root -> children_capacity = 3;
    root -> children_count = 3;
    root -> children = malloc(3 * sizeof(Node * ));
    root -> children[0] = create_node("FolderC");
    root -> children[1] = create_node("FolderA");
    root -> children[2] = create_node("FolderB");

    sort_children(root);

    assert(strcmp(root -> children[0] -> name, "FolderA") == 0);
    assert(strcmp(root -> children[1] -> name, "FolderB") == 0);
    assert(strcmp(root -> children[2] -> name, "FolderC") == 0);
    free_tree(root);
}

void TestWriteTreeToFile_SimpleTree_no6() {
    FILE * file = fopen("test_output.txt", "w");
    Node * root = create_node("");
    add_path(root, "Folder1");
    add_path(root, "Folder2");

    write_tree_to_file(root, file, 0);
    fclose(file);

    file = fopen("test_output.txt", "r");
    char line[50];

    fgets(line, sizeof(line), file);
    assert(strcmp(line, "Folder1\n") == 0);

    fgets(line, sizeof(line), file);
    assert(strcmp(line, "Folder2\n") == 0);

    fclose(file);
    free_tree(root);
}

void TestFreeTree_EmptyTree_no7() {
    Node * root = create_node("");
    free_tree(root);
}

void TestFreeTree_NonEmptyTree_no8() {
    Node * root = create_node("");
    add_path(root, "Folder1\\Subfolder1");
    add_path(root, "Folder2");
    free_tree(root);
}

void TestAddPath_DeeplyNestedPath_no9() {
    Node * root = create_node("");
    add_path(root, "A\\B\\C\\D\\E");

    Node * current = root;
    const char * expected[] = {
        "A",
        "B",
        "C",
        "D",
        "E"
    };
    for (int i = 0; i < 5; i++) {
        assert(current -> children_count == 1);
        assert(strcmp(current -> children[0] -> name, expected[i]) == 0);
        current = current -> children[0];
    }

    free_tree(root);
}

void TestAddPath_DuplicatePath_no10() {
    Node * root = create_node("");
    add_path(root, "Folder1");
    add_path(root, "Folder1");

    assert(root -> children_count == 1);
    assert(strcmp(root -> children[0] -> name, "Folder1") == 0);
    free_tree(root);
}

void TestWriteTreeToFile_RussianNames_no11() {
    FILE * file = fopen("test_output.txt", "w");
    Node * root = create_node("");
    add_path(root, "Папка1");
    add_path(root, "Папка2");

    write_tree_to_file(root, file, 0);
    fclose(file);

    file = fopen("test_output.txt", "r");
    char line[50];

    fgets(line, sizeof(line), file);
    assert(strcmp(line, "Папка1\n") == 0);

    fgets(line, sizeof(line), file);
    assert(strcmp(line, "Папка2\n") == 0);

    fclose(file);
    free_tree(root);
}

int main() {
    TestCreateNode_ValidName_no1();
    TestAddPath_SinglePath_no2();
    TestAddPath_NestedPath_no3();
    TestAddPath_MultiplePaths_no4();
    TestSortChildren_LexicographicOrder_no5();
    TestWriteTreeToFile_SimpleTree_no6();
    TestFreeTree_EmptyTree_no7();
    TestFreeTree_NonEmptyTree_no8();
    TestAddPath_DeeplyNestedPath_no9();
    TestAddPath_DuplicatePath_no10();
    TestWriteTreeToFile_RussianNames_no11();

    printf("All tests passed successfully!\n");
    return 0;
}