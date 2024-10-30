#ifndef TESTS_H
#define TESTS_H
#include "lib.h"
#include <assert.h>

void runAllTests();

void initQueue_Initialization_FrontAndRearEqual0_no1();
    
void isEmpty_EmptyQueue_returnTrue_no2();
void isEmpty_NotEmptyQueue_returnFalse_no3();

void addToQueue_AddToEmptyQueue_returnValidVal_no4();
void addToQueue_AddToNotEmpty_returnValidVal_no5();

void removeFromQueue_RemoveFromEmpty_returnMinus1_no6();
void removeFromQueue_RemoveFromNotEmpty_returnItem_no7();

void bfs_ThereIsAPath_returnShortestPath_no8();
void bfs_ThereAreNoPath_returnINF_no9();
void bfs_NoSuchVertex_returnINF_no10();
void bfs_PathIntoItself_return0_no11();

#endif