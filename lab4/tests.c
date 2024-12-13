//
//  tests.c
//  LAB_F
//
//  Created by Фёдор Филь on 11.12.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tests.h"
#include "tree.h"

void test_insert_and_find_no1(void) {
    Node* root = NULL;
    root = insert(root, 10, 20);
    root = insert(root, 5, 25);
    root = insert(root, 15, 35);

    int intervalToFind[] = {14, 24};
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 2);
    assert(result[0]->low == 10 && result[0]->high == 20);
    assert(result[1]->low == 15 && result[1]->high == 35);
}

void test_delete_and_find_no2(void) {
    Node* root = NULL;
    root = insert(root, 10, 20);
    root = insert(root, 5, 25);
    root = insert(root, 15, 35);

    root = deleteNode(root, 10);

    int intervalToFind[] = {14, 24};
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 1);
    assert(result[0]->low == 15 && result[0]->high == 35);
}

void test_empty_tree_no3(void) {
    Node* root = NULL;

    int intervalToFind[] = {14, 24};
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 0);
}

void test_single_element_tree_no4(void) {
    Node* root = NULL;
    root = insert(root, 10, 20);

    int intervalToFind[] = {11, 18};
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 1);
    assert(result[0]->low == 10 && result[0]->high == 20);
}

void test_no_overlap_no5(void) {
    Node* root = NULL;
    root = insert(root, 10, 20);
    root = insert(root, 25, 30);

    int intervalToFind[] = {22, 23};
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 0);
}

void test_exact_match_no6(void) {
    Node* root = NULL;
    root = insert(root, 10, 20);
    root = insert(root, 15, 25);

    int intervalToFind[] = {15, 25};
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 1);
    assert(result[0]->low == 15 && result[0]->high == 25);
}

void test_multiple_overlaps_no7(void) {
    Node* root = NULL;
    root = insert(root, 10, 20);
    root = insert(root, 15, 25);
    root = insert(root, 5, 30);

    int intervalToFind[] = {8, 28};
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 3);
    assert(result[0]->low == 5 && result[0]->high == 30);
    assert(result[1]->low == 10 && result[1]->high == 20);
    assert(result[2]->low == 15 && result[2]->high == 25);
}

void test_left_edge_case_no8(void) {
    Node* root = NULL;
    root = insert(root, 10, 20);
    root = insert(root, 15, 25);

    int intervalToFind[] = {9, 26};
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 2);
    assert(result[0]->low == 10 && result[0]->high == 20);
    assert(result[1]->low == 15 && result[1]->high == 25);
}

void test_right_edge_case_no9(void) {
    Node* root = NULL;
    root = insert(root, 10, 20);
    root = insert(root, 15, 25);

    int intervalToFind[] = {11, 29};
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 2);
    assert(result[0]->low == 10 && result[0]->high == 20);
    assert(result[1]->low == 15 && result[1]->high == 25);
}

void test_boundary_cases_no10(void) {
    Node* root = NULL;
    root = insert(root, 10, 20);
    root = insert(root, 15, 25);

    int intervalToFind[] = {10, 25};
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 2);
    assert(result[0]->low == 10 && result[0]->high == 20);
    assert(result[1]->low == 15 && result[1]->high == 25);
}
