#pragma once

#include <assert.h>
#include "lab5.h" 

void CreateNode_Interval_returnValidVal() {
    interval_t interval = { 1, 3 };
    node_t* node = CreateNode(interval);
    assert(node != NULL);
    assert(node->interval.start == 1);
    assert(node->interval.end == 3);
    assert(node->max_end == 3);
    assert(node->left == NULL);
    assert(node->right == NULL);
    free(node); 
}

void InsertInterval_NewMaxEnd_returnValidVal() {
    node_t* root = NULL;
    interval_t interval1 = { 1, 5 };
    interval_t interval2 = { 2, 6 };

    root = InsertInterval(root, interval1);
    assert(root != NULL);
    assert(root->max_end == 5);

    root = InsertInterval(root, interval2);
    assert(root->max_end == 6);
    free(root);
}

void DeleteInterval_Interval_returnValidVal() {
    node_t* root = NULL;
    interval_t intervals[] = { {1, 5}, {2, 6}, {8, 10} };
    int n = sizeof(intervals) / sizeof(intervals[0]);

    for (int i = 0; i < n; i++) {
        root = InsertInterval(root, intervals[i]);
    }

    assert(root != NULL);
    assert(root->max_end == 10);

    interval_t toDelete = { 2, 6 };
    root = DeleteInterval(root, toDelete);

    assert(root != NULL);
    assert(root->max_end == 10); // max_end still equals 10
    assert(root->interval.start == 1); // {1, 5} still exist

    root = DeleteInterval(root, intervals[0]);
    root = DeleteInterval(root, intervals[1]);
    root = DeleteInterval(root, intervals[2]);
    assert(root == NULL);
}

void DeleteInterval_NULL_returnNULL() {
    node_t* root = NULL;
    interval_t toDelete = { 2, 6 };
    root = DeleteInterval(root, toDelete);
    assert(root == NULL);
}

void IsIntersection_Intersection_returnOne() {
    interval_t i1 = { 1, 5 };
    interval_t i2 = { 4, 6 };
    assert(IsIntersection(i1, i2) == 1); 
}

void IsIntersection_NoIntersection_returnZero() {
    interval_t i1 = { 1, 5 };
    interval_t i2 = { 7, 8 };
    assert(IsIntersection(i1, i2) == 0); 
}

void SearchIntersections_OneIntersection_returnValidVal() {
    node_t* root = NULL;
    interval_t intervals[] = { {1, 3}, {2, 5}, {8, 10}, {15, 18}, {17, 20} };
    for (int i = 0; i < 5; i++) {
        root = InsertInterval(root, intervals[i]);
    }

    interval_t targetInterval = { 4, 6 };
    int count = 0;
    interval_t* result = (interval_t*)malloc(5 * sizeof(interval_t));
    result = SearchIntersections(root, targetInterval,result, &count);

    assert(count == 1); // one intersection
    assert(result[0].start == 2 && result[0].end == 5); // {2, 5}

    root = DeleteInterval(root, intervals[0]);
    root = DeleteInterval(root, intervals[1]);
    root = DeleteInterval(root, intervals[2]);
    root = DeleteInterval(root, intervals[3]);
    root = DeleteInterval(root, intervals[4]);
    free(result);
}

void SearchIntersections_NoIntersection_returnValidVal() {
    node_t* root = NULL;
    interval_t intervals[] = { {1, 3}, {2, 5}, {8, 10}, {15, 18}, {17, 20} };
    for (int i = 0; i < 5; i++) {
        root = InsertInterval(root, intervals[i]);
    }

    interval_t targetInterval = { 6, 7 };
    int count = 0;
    interval_t* result = (interval_t*)malloc(5 * sizeof(interval_t));
    result = SearchIntersections(root, targetInterval, result, &count);

    assert(count == 0); // no intersections

    root = DeleteInterval(root, intervals[0]);
    root = DeleteInterval(root, intervals[1]);
    root = DeleteInterval(root, intervals[2]);
    root = DeleteInterval(root, intervals[3]);
    root = DeleteInterval(root, intervals[4]);
    free(result);
}

void SearchIntersections_NULL_returnNULL() {
    node_t* root = NULL;
    int count = 0;
    interval_t targetInterval = { 4, 6 };
    interval_t* result = (interval_t*)malloc(5 * sizeof(interval_t));
    result = SearchIntersections(root, targetInterval, result, &count);

    assert(result == NULL);
}

void SearchIntersections_MultipIntersections_returnValidVal() {
    node_t* root = NULL;
    interval_t intervals[] = { {1, 3}, {2, 5}, {4, 6}, {7, 8}, {15, 18}, {17, 20} };
    for (int i = 0; i < 6; i++) {
        root = InsertInterval(root, intervals[i]);
    }

    interval_t targetInterval = { 2, 10 };
    int count = 0;
    interval_t* result = (interval_t*)malloc(6 * sizeof(interval_t));
    result = SearchIntersections(root, targetInterval, result, &count);

    assert(count == 4); // 4 intersections
    assert(result[0].start == 1); // {1, 3}
    assert(result[1].start == 2); // {2, 5}
    assert(result[2].start == 4); // {4, 6}
    assert(result[3].start == 7); // {7, 8}

    for (int i = 0; i < 6; i++) {
        root = DeleteInterval(root, intervals[i]);
    }
}

void tests() {
    CreateNode_Interval_returnValidVal();
    InsertInterval_NewMaxEnd_returnValidVal();
    DeleteInterval_Interval_returnValidVal();
    DeleteInterval_NULL_returnNULL();
    IsIntersection_Intersection_returnOne();
    IsIntersection_NoIntersection_returnZero();
    SearchIntersections_OneIntersection_returnValidVal();
    SearchIntersections_NoIntersection_returnValidVal();
    SearchIntersections_NULL_returnNULL();
    SearchIntersections_MultipIntersections_returnValidVal();
}
