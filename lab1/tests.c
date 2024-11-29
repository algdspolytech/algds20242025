#include <stdio.h>
#include <stdlib.h>
#include "A_v29.h"


int compare_str(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0;
        }
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0') {
        return 1;
    }
    else {
        return 0;
    }
}

void TestCreateDir_ValidName_no2() {
    dir* d = create_dir("TestDir", 7);
    int name = compare_str(d->name, "TestDir");
    int subdir = (d->subdir_cnt == 0);
    printf("Test 2 = %i\n", name && subdir);
    free(d);
}

void TestCreateDir_MaxLength_no3() {
    dir* d = create_dir("12345678", 8);
    int name = compare_str(d->name, "12345678");
    int subdir = (d->subdir_cnt == 0);
    printf("Test 3 = %i\n", name && subdir);
    free(d);
}

void TestCreateDir_EmptyName_no4() {
    dir* d = create_dir("", 0);
    int name = compare_str(d->name, "");
    int subdir = (d->subdir_cnt == 0);
    printf("Test 4 = %i\n", name && subdir);
    free(d);
}

void TestFindSubdir_ExistingSubdir_no5() {
    dir* parent = create_dir("Parent", 6);
    dir* subdir = create_dir("SubDir", 6);
    add_subdir(parent, subdir);

    dir* found = find_subdir(parent, "SubDir", 6);
    printf("Test 5 = %i\n", found == subdir);

    free(subdir);
    free(parent);
}

void TestFindSubdir_NonExistingSubdir_no6() {
    dir* parent = create_dir("Parent", 6);
    dir* found = find_subdir(parent, "NonExist", 8);
    printf("Test 6 = %i\n", found == NULL);

    free(parent);
}

void TestAddSubdir_AddSingleSubdir_no7() {
    dir* parent = create_dir("Parent", 6);
    dir* subdir = create_dir("SubDir", 6);
    add_subdir(parent, subdir);

    printf("Test 7 = %i\n", parent->subdir_cnt == 1 && parent->subdirs[0] == subdir);

    free(subdir);
    free(parent);
}

void TestAddSubdir_AddMultipleSubdirs_no8() {
    dir* parent = create_dir("Parent", 6);
    dir* subdir1 = create_dir("Sub1", 4);
    dir* subdir2 = create_dir("Sub2", 4);
    add_subdir(parent, subdir1);
    add_subdir(parent, subdir2);

    printf("Test 8 = %i\n", parent->subdir_cnt == 2 && parent->subdirs[0] == subdir1 && parent->subdirs[1] == subdir2);

    free(subdir1);
    free(subdir2);
    free(parent);
}

void TestSortDirs_AlphabeticalOrder_no9() {
    dir* parent = create_dir("Parent", 6);
    dir* subdir1 = create_dir("BDir", 4);
    dir* subdir2 = create_dir("ADir", 4);
    add_subdir(parent, subdir1);
    add_subdir(parent, subdir2);

    qsort(parent->subdirs, parent->subdir_cnt, sizeof(dir*), sort_dirs);
    int firstSorted = compare_str(parent->subdirs[0]->name, "ADir");
    int secondSorted = compare_str(parent->subdirs[1]->name, "BDir");
    printf("Test 9 = %i\n", firstSorted && secondSorted);

    free(subdir1);
    free(subdir2);
    free(parent);
}

void TestSortDirs_SingleSubdir_no10() {
    dir* parent = create_dir("Parent", 6);
    dir* subdir = create_dir("SubDir", 6);
    add_subdir(parent, subdir);

    qsort(parent->subdirs, parent->subdir_cnt, sizeof(dir*), sort_dirs);
    int sorted = compare_str(parent->subdirs[0]->name, "SubDir");
    printf("Test 10 = %i\n", sorted);

    free(subdir);
    free(parent);
}

void TestSortDirs_EmptyDir_no11() {
    dir* parent = create_dir("Parent", 6);
    qsort(parent->subdirs, parent->subdir_cnt, sizeof(dir*), sort_dirs);
    printf("Test 11 = %i\n", parent->subdir_cnt == 0);

    free(parent);
}

void TestMainFunctionality_no1() {
    dir* root = read_tree_from_file("input.txt");
    if (root == NULL) {
        printf("Error: could not read from input file\n");
        return;
    }

    write_tree_to_file("output.txt", root);

    printf("Test 1 = ok\n");
}

void runAllTests() {
    TestMainFunctionality_no1();
    TestCreateDir_ValidName_no2();
    TestCreateDir_MaxLength_no3();
    TestCreateDir_EmptyName_no4();
    TestFindSubdir_ExistingSubdir_no5();
    TestFindSubdir_NonExistingSubdir_no6();
    TestAddSubdir_AddSingleSubdir_no7();
    TestAddSubdir_AddMultipleSubdirs_no8();
    TestSortDirs_AlphabeticalOrder_no9();
    TestSortDirs_SingleSubdir_no10();
    TestSortDirs_EmptyDir_no11();
}

int main() {
    runAllTests();
    return 0;
}
