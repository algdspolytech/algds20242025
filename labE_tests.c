#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "labE.h"

int compare_str(char *str1, char *str2) {
    int n = strlen(str1);
    if (strlen(str2) < n) return 0;

    for (int i = 0; i < n; i++) {
        if (str1[i] != str2[i]) return 0;
    }
    return 1;
}

void test1_read_file() {
    char *s = "tree00 (tree10 (tree20 (tree30)) (tree11))    (tree01 (tree11) (tree02))";
    char *rs = read_file("test1.txt");
    if(rs == NULL) {
        printf("\n change file path; test1_read_file\n");
        return;
    }
    assert(compare_str(s, rs));
    free(rs);
}

void test2_remove_spaces() {
    char a[10];
    for (int i = 0; i < 10; i++) a[i] = ' ';
    a[4] = 'a';
    a[7] = 'b';
    a[8] = 'c';
    a[9] = '\0';
    remove_spaces(a);
    assert(a[0] == 'a' && a[1] == 'b' && a[2] == 'c');
}

void test3_parse_tree_0children0brackets() {
    char *str = "tree";
    node *tree = parse_tree(str, NULL);
    assert(compare_str(tree->data, "tree") && tree->left == NULL && tree->right == NULL);
    free_tree(tree);
}

void test4_parse_tree_0children1couplesBrackets() {
    char *str = "tree()";
    node *tree = parse_tree(str, NULL);
    assert(compare_str(tree->data, "tree") && tree->left == NULL && tree->right == NULL);
    free_tree(tree);
}

void test5_parse_tree_0children2couplesBrackets() {
    char *str = "tree()()";
    node *tree = parse_tree(str, NULL);
    assert(compare_str(tree->data, "tree") && tree->left == NULL && tree->right == NULL);
    free_tree(tree);
}

void test6_parse_tree_1children1left2couplesBrackets() {
    char *str = "tree(child1)()";
    node *tree = parse_tree(str, NULL);
    assert(compare_str(tree->data, "tree") && compare_str(tree->left->data, "child1") && tree->right == NULL);
    free_tree(tree);
}

void test7_parse_tree_1children1left1couplesBrackets() {
    char *str = "tree(child1)";
    node *tree = parse_tree(str, NULL);
    assert(compare_str(tree->data, "tree") && compare_str(tree->left->data, "child1") && tree->right == NULL);
    free_tree(tree);
}

void test8_parse_tree_1children1right2couplesBrackets() {
    char *str = "tree()(child1)";
    node *tree = parse_tree(str, NULL);
    assert(compare_str(tree->data, "tree") && compare_str(tree->right->data, "child1") && tree->left == NULL);
    free_tree(tree);
}

void test9_parse_tree_2children() {
    char *str = "tree(child1)(child2)";
    node *tree = parse_tree(str, NULL);
    assert(
        compare_str(tree->data, "tree") && compare_str(tree->right->data, "child2") && compare_str(tree->left->data,
            "child1"));
    free_tree(tree);
}

void test10_parse_tree_2children1children() {
    char *str = "tree(child1(child11))(child2)";
    node *tree = parse_tree(str, NULL);
    assert(
        compare_str(tree->data, "tree") && compare_str(tree->right->data, "child2") && compare_str(tree->left->data,
            "child1")
        && compare_str(tree->left->left->data, "child11"));
    free_tree(tree);
}

void test11_parse_tree_onlyLeft() {
    char *str = "tree(1(2(3(4(5))())))()";
    node *tree = parse_tree(str, NULL);
    assert(compare_str(tree->left->left->left->left->left->data, "5"));
}

void tests() {
    test1_read_file();
    test2_remove_spaces();
    test3_parse_tree_0children0brackets();
    test4_parse_tree_0children1couplesBrackets();
    test5_parse_tree_0children2couplesBrackets();
    test6_parse_tree_1children1left2couplesBrackets();
    test7_parse_tree_1children1left1couplesBrackets();
    test8_parse_tree_1children1right2couplesBrackets();
    test9_parse_tree_2children();
    test10_parse_tree_2children1children();
    test11_parse_tree_onlyLeft();

    printf("\ntests ok\n");
}
