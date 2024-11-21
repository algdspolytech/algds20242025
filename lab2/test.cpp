#include "main.h"

void getCouples_testSimple_correctCouples_1() {
    char *path = "../tests/testSimple.txt";
    char *str = readFile(path);

    struct getCouplesResult couplesResult = getCouples(str);
    struct couple *couples = couplesResult.couples;
    assert(
        couples[0].before[0] == 'a' && couples[0].after[0] == 'b' && couples[1].before[0] == 'a' && couples[1].after[0]
        ==
        'c' && couples[2].before[0] == 'b' && couples[2].after[0] == 'c');
}

void compareStr_differentLength_false_2() {
    char *str1 = "abc";
    char *str2 = "abcd";
    assert(!compareStr(str1, str2));
}

void compareStr_sameStr_str_3() {
    char *str1 = "abcd";
    char *str2 = "abcd";
    assert(compareStr(str1, str2));
}

void createStrArray_ThereAreIdenticalOnesTestSimple_3Array_4() {
    char *path = "../tests/testSimple.txt";
    char *str = readFile(path);

    struct getCouplesResult couplesResult = getCouples(str);
    struct couple *couples = couplesResult.couples;
    int couplesSize = couplesResult.size;

    struct createStrArrayResult arrResult = createStrArray(couples, couplesSize);
    char **arr = arrResult.arr;
    int arrSize = arrResult.size;
    assert(arr[0][0] == 'a' && arr[1][0] == 'b' && arr[2][0] == 'c' && arrSize == 3);
}

void pastSelectedItemBeforeItem_abc_neighboringElementsInBeginning_bac_5() {
    char *arr[] = {"a", "b", "c"};

    pastSelectedItemBeforeItem(arr, 0, 1);

    assert(compareStr(arr[0], "b") && compareStr(arr[1], "a") && compareStr(arr[2], "c"));
}

void pastSelectedItemBeforeItem_abc_neighboringElementsInEnd_acb_6() {
    char *arr[] = {"a", "b", "c"};

    pastSelectedItemBeforeItem(arr, 1, 2);

    assert(compareStr(arr[0], "a") && compareStr(arr[1], "c") && compareStr(arr[2], "b"));
}

void pastSelectedItemBeforeItem_abc_boundaryElements_cab_7() {
    char *arr[] = {"a", "b", "c"};

    pastSelectedItemBeforeItem(arr, 0, 2);

    assert(compareStr(arr[0], "c") && compareStr(arr[1], "a") && compareStr(arr[2], "b"));
}

void isTrueOrder_a_b_testSimple_true_8() {
    char *path = "../tests/testSimple.txt";
    char *str = readFile(path);

    struct getCouplesResult couplesResult = getCouples(str);
    struct couple *coupls = couplesResult.couples;
    int couplesSize = couplesResult.size;

    assert(isTrueOrder(coupls, couplesSize, "a", "b"));
}

void isTrueOrder_b_a_testSimple_true_9() {
    char *path = "../tests/testSimple.txt";
    char *str = readFile(path);

    struct getCouplesResult couplesResult = getCouples(str);
    struct couple *couples = couplesResult.couples;
    int couplesSize = couplesResult.size;

    assert(!isTrueOrder(couples, couplesSize, "b", "a"));
}

void algorithmProfessor_testSimple_abc_10() {
    char *path = "../tests/testSimple.txt";
    char *str = readFile(path);

    struct getCouplesResult couplesResult = getCouples(str);
    struct couple *couples = couplesResult.couples;
    int couplesSize = couplesResult.size;

    struct algorithmProfessorResult res = algorithmProfessor(couples, couplesSize);
    char **arr = res.arr;
    assert(arr[0][0] == 'a' && arr[1][0] == 'b' && arr[2][0] == 'c');
}

void algorithmProfessor_testError_Error_11() {
    char *path = "../tests/testError.txt";
    char *str = readFile(path);

    struct getCouplesResult couplesResult = getCouples(str);
    struct couple *couples = couplesResult.couples;
    int couplesSize = couplesResult.size;

    struct algorithmProfessorResult res = algorithmProfessor(couples, couplesSize);

    assert(res.arr == NULL && res.size == 0);
}

void algorithmProfessor_notTheOnlySolution_NotError_12() {
    char *path1 = "../tests/testNotTheOnlySolution1.txt";
    char *str1 = readFile(path1);

    struct getCouplesResult couplesResult1 = getCouples(str1);
    struct couple *couples1 = couplesResult1.couples;
    int couplesSize1 = couplesResult1.size;

    struct algorithmProfessorResult res1 = algorithmProfessor(couples1, couplesSize1);
    char **arr1 = res1.arr;

    char *path2 = "../tests/testNotTheOnlySolution2.txt";
    char *str2 = readFile(path2);

    struct getCouplesResult couplesResult2 = getCouples(str2);
    struct couple *couples2 = couplesResult2.couples;
    int couplesSize2 = couplesResult2.size;

    struct algorithmProfessorResult res2 = algorithmProfessor(couples1, couplesSize1);
    char **arr2 = res2.arr;

    assert(!compareStr(arr1[0], "error") && !compareStr(arr2[0], "error"));
}

void allTests() {
    getCouples_testSimple_correctCouples_1();
    compareStr_differentLength_false_2();
    compareStr_sameStr_str_3();
    createStrArray_ThereAreIdenticalOnesTestSimple_3Array_4();
    pastSelectedItemBeforeItem_abc_neighboringElementsInBeginning_bac_5();
    pastSelectedItemBeforeItem_abc_neighboringElementsInEnd_acb_6();
    pastSelectedItemBeforeItem_abc_boundaryElements_cab_7();
    isTrueOrder_a_b_testSimple_true_8();
    isTrueOrder_b_a_testSimple_true_9();
    algorithmProfessor_testSimple_abc_10();
    algorithmProfessor_testError_Error_11();
    algorithmProfessor_notTheOnlySolution_NotError_12();
}