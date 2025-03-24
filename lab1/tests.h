#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_WORDS 100
#define MAX_LENGTH 21

int read_words(const char* filename, char* words[MAX_WORDS]);

void stub_read_words(const char* filename, char words[][MAX_LENGTH], int* count);

void stub_write_words(const char* filename, char words[][MAX_LENGTH], int count);

int merge_sorted_lists(char* words1[MAX_WORDS], int count1,
    char* words2[MAX_WORDS], int count2,
    char* merged[MAX_WORDS * 2]);

void test_read_words_no1();

void test_compare_words_no2();

void test_merge_sorted_lists_no3();

void test_merge_sorted_lists_with_duplicates_no4();

void test_write_words_no5();

void test_merge_empty_lists_no6();

void test_merge_one_empty_list_no7();

void test_merge_identical_lists_no8();

void test_empty_file_no9();

void test_non_existent_file_no10();

