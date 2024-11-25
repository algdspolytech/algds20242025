//
// Created by frama on 15/09/2024.
//

#include "../main.h"
#include "tests.h"
#include <assert.h>
#include <stdio.h>

void cmpstr_zerostrings_return0() {
    assert(cmpstr(0, "", 0, "") == 0);
}

void cmpstr_a_shorter_than_b_returnValidVal() {
    assert(cmpstr(1, "a", 2, "ab") == -1);
}

void cmpstr_a_longer_than_b_returnValidVal() {
    assert(cmpstr(2, "ab", 1, "a") == 1);
}

void cmpstr_a_same_as_b_returnValidVal() {
    assert(cmpstr(3, "abc", 3, "cab") == -1);
}

void check_if_contains_one_element_list_that_contains_return1() {
    List *l = initList("testtesttest");
    assert(check_if_contains(l, 12) == 1);
    deleteList(l);
}

void check_if_contains_one_element_list_that_not_contains_return0() {
    List *l = initList("testtesttest");
    assert(check_if_contains(l, 15) == 0);
    deleteList(l);
}

void check_if_contains_large_list_return1() {
    List *l = initList("test1");
    l = addToList(l, initList("test12"));
    l = addToList(l, initList("te"));
    l = addToList(l, initList(""));
    l = addToList(l, initList(
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."));
    assert(check_if_contains(l, 5) == 1);
    deleteList(l);
}

void List_longer_n_NULL_list_return_NULL() {
    assert(List_longer_n(NULL, 13) == NULL);
}

void List_longer_n_one_el_list_return_NULL() {
    List *l = initList("");
    assert(List_longer_n(l, 13) == NULL);
    deleteList(l);
}

void List_longer_n_large_list_return_NULL() {
    List *l = initList("test1");
    l = addToList(l, initList("test12"));
    l = addToList(l, initList("te"));
    List *expected = initList("top");
    l = addToList(l, expected);
    l = addToList(l, initList(""));
    l = addToList(l, initList(
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."));
    assert(List_longer_n(l, 2) == expected);
    deleteList(l);
}

void addToList_null_add_null_returnNull() {
    assert(addToList(NULL, NULL) == NULL);
}

void addToList_list_add_null_returnList() {
    List *l = initList("addToList_list_add_null_returnList");
    assert(addToList(l, NULL) == l && l->next == NULL);
    deleteList(l);
}

void addToList_list_add_smaller_returnList() {
    List *l = initList("addToList_list_add_smaller_returnList");
    List *expected = initList("expected");
    l = addToList(l, expected);
    assert(l == expected);
    deleteList(l);
}

void addToList_list_add_longer_returnList() {
    List *l = initList("adad");
    List *expected = initList("addToList_list_add_longer_returnList");
    assert(addToList(l, expected) == l && l->next == expected);
    deleteList(l);
}

// 13 tests total
void runAllTests() {
    cmpstr_zerostrings_return0();
    cmpstr_a_shorter_than_b_returnValidVal();
    cmpstr_a_longer_than_b_returnValidVal();
    cmpstr_a_same_as_b_returnValidVal();
    check_if_contains_one_element_list_that_contains_return1();
    check_if_contains_one_element_list_that_not_contains_return0();
    check_if_contains_large_list_return1();
    List_longer_n_NULL_list_return_NULL();
    List_longer_n_large_list_return_NULL();
    List_longer_n_one_el_list_return_NULL();
    addToList_list_add_null_returnList();
    addToList_null_add_null_returnNull();
    addToList_list_add_smaller_returnList();
    addToList_list_add_longer_returnList();
    printf("ALL TEST RAN PERFECTLY\n");
}

