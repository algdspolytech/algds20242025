#pragma once
#ifndef TESTS_H
#define TESTS_H

#include "funcs.h"

void test_readGraph_validFile_No1();
void test_readGraph_emptyFile_No2();
void test_isCovered_allVerticesIncluded_No3();
void test_isCovered_notCovered_No4();
void test_findVertexCover_minimalCover_No5();
void test_findVertexCover_impossible_No6();
void test_isCovered_emptyGraph_No7();
void test_isCovered_selfLoop_No8();
void test_findVertexCover_chainGraph_No9();
void test_findVertexCover_singleEdge_No10();

#endif