#pragma once

#ifndef WORD_LIST_H
#define WORD_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 1000

typedef struct {
    char word[MAX_WORD_LENGTH];
} Word;

typedef struct {
    Word* words;
    int count;
} WordList;

// Functions for working with a list of words
WordList* create_word_list();
void add_word(WordList* list, const char* word);
void read_words_from_file(WordList* list, const char* filename);
void print_words_longer_than(WordList* list, int N);
int has_words_of_length(WordList* list, int N);
void free_word_list(WordList* list);


// For tests
void runAllTests();

#endif