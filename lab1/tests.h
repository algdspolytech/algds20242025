#pragma once
#ifndef TESTS_H
#define TESTS_H

#include <stdlib.h>

#include <stdio.h>

#include <math.h>

#include <string.h>

#include <time.h>

#include <windows.h>

#include "functions.h"


void test_init_EmptyString_return0_no1();
void test_init_NotEmptyString_return0_no2();
void test_add_node_EmptyString_return0_no3();
void test_add_node_NotEmptyString_return0_no4();
void test_add_node_NullList_return0_no5();
void test_add_node_SeveralNodes_return0_no6();
void test_len_of_full_str_EmptyList_return0_no7();
void test_len_of_full_str_ListWithEmptyStrings_return0_no8();
void test_len_of_full_str_ListWithSeveralNotEmptyStrings_return0_no9();
void test_len_of_full_str_ListWithEmptyAndNotEmptyStrings_return0_no10();
void test_get_full_str_EmptyList_return0_no11();
void test_get_full_str_ListWithEmptyStrings_return0_no12();
void test_get_full_str_ListWithSeveralNotEmptyStrings_return0_no13();
void test_get_full_str_ListWithEmptyAndNotEmptyStrings_return0_no14();

#endif