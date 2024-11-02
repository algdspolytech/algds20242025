#include "test.h"


void append_OneElementList_ruturnNULL() {
	BigInt* test_num = init(1, 1);
	BigInt* result_num = init(2, 2, 1);
	append(test_num, 2);
	assert(equal(test_num, result_num) == 1);
}


void append_ManyElementList_ruturnNULL() {
	BigInt* test_num = init(3, 3, 2, 1);
	BigInt* result_num = init(4, 4, 3, 2, 1);
	append(test_num, 4);
	assert(equal(test_num, result_num) == 1);
}


void rappend_OneElementList_ruturnNULL() {
	BigInt* test_num = init(1, 1);
	BigInt* result_num = init(2, 1, 0);
	rappend(test_num, 0);
	assert(equal(test_num, result_num) == 1);
}


void rappend_ManyElementList_ruturnNULL() {
	BigInt* test_num = init(3, 3, 2, 1);
	BigInt* result_num = init(4, 3, 2, 1, 0);
	rappend(test_num, 0);
	assert(equal(test_num, result_num) == 1);
}


void reverse_OneElementList_ruturnNULL() {
	BigInt* test_num = init(1, 1);
	BigInt* result_num = init(1, 1);
	reverse(test_num);
	assert(equal(test_num, result_num) == 1);
}


void reverse_ManyElementList_ruturnNULL() {
	BigInt* test_num = init(3, 3, 2, 1);
	BigInt* result_num = init(3, 1, 2, 3);
	reverse(test_num);
	assert(equal(test_num, result_num) == 1);
}


void add_SameSignNumbers_ruturnNULL() {
	BigInt* test_num_a = init(1, 2);
	BigInt* test_num_b = init(2, 1, 0);
	BigInt* result_num = init(2, 1, 2);
	assert(equal(add(test_num_a, test_num_b), result_num) == 1);
}


void add_DifferentSignNumbers_ruturnNULL() {
	BigInt* test_num_a = init(1, 2);
	BigInt* test_num_b = init(2, -1, 0);
	BigInt* result_num = init(1, -8);
	assert(equal(add(test_num_a, test_num_b), result_num) == 1);
}


void mul_SameSignNumbers_ruturnNULL() {
	BigInt* test_num_a = init(1, 2);
	BigInt* test_num_b = init(2, 1, 0);
	BigInt* result_num = init(2, 2, 0);
	assert(equal(mul(test_num_a, test_num_b), result_num) == 1);
}


void mul_DifferentSignNumbers_ruturnNULL() {
	BigInt* test_num_a = init(1, 2);
	BigInt* test_num_b = init(2, -1, 0);
	BigInt* result_num = init(2, -2, 0);
	assert(equal(mul(test_num_a, test_num_b), result_num) == 1);
}


void sub_EqualNumbers_ruturnNULL() {
	BigInt* test_num_a = init(3, 1, 0, 0);
	BigInt* test_num_b = init(3, 1, 0, 0);
	BigInt* result_num = init(1, 0);
	assert(equal(sub(test_num_a, test_num_b), result_num) == 1);
}


void bigpow_BigSecondNumber_ruturnNULL() {
	BigInt* test_num_a = init(2, 1, 0);
	BigInt* test_num_b = init(2, 1, 0);
	BigInt* result_num = init(11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	assert(equal(bigpow(test_num_a, test_num_b), result_num) == 1);
}

void run_all_tests() {
	append_OneElementList_ruturnNULL();
	append_ManyElementList_ruturnNULL();
	rappend_OneElementList_ruturnNULL();
	rappend_ManyElementList_ruturnNULL();
	reverse_OneElementList_ruturnNULL();
	reverse_ManyElementList_ruturnNULL();
	add_SameSignNumbers_ruturnNULL();
	add_DifferentSignNumbers_ruturnNULL();
	mul_SameSignNumbers_ruturnNULL();
	mul_DifferentSignNumbers_ruturnNULL();
	sub_EqualNumbers_ruturnNULL();
	bigpow_BigSecondNumber_ruturnNULL();
	printf("All tests completed successfully.\n");
}