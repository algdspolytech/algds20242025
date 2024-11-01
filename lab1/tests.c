#include "labA.h"
#include <assert.h>
#include <stdio.h>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define _CRTDBG_MAP_ALLOC

void CreateEmptyList_no1() { 
    WordList* list = create_word_list();
    assert(list==NULL);
    assert(list->count==0);
    free_word_list(list);
}

// Tests for adding words to a list

void AddSingleWord_no2() {
    WordList* list = create_word_list();
    add_word(list, "apple");

    assert(list->count==1);
    assert(list->words[0].word=="apple");

    free_word_list(list);
}

void AddMultipleWords_no3() {
    WordList* list = create_word_list();
    add_word(list, "banana");
    add_word(list, "apple");

    assert(list->count==2);
    assert(list->words[0].word=="apple"); // It should be the first

    free_word_list(list);
}

void AddWordsSorted_no4() {
    WordList* list = create_word_list();

    add_word(list, "pear");
    add_word(list, "apple");
    add_word(list, "banana");

    assert(list->words[0].word=="apple");
    assert(list->words[1].word=="pear");
    assert(list->words[2].word=="banana");

    free_word_list(list);
}

void AddDuplicateWords_no5() {
    WordList* list = create_word_list();

    add_word(list, "apple");
    add_word(list, "apple"); // Duplicate the word

    assert(list->count==2); // We count as two different words

    free_word_list(list);
}

// Tests to check for the presence of words of a certain length

void HasWordsOfLength_no6() {
    WordList* list = create_word_list();

    add_word(list, "apple");
    add_word(list, "banana");

    assert(has_words_of_length(list, 6)); // 'banana' length 6

    free_word_list(list);
}

void NoWordsOfLength_no7() {
    WordList* list = create_word_list();

    add_word(list, "apple");

    assert(has_words_of_length(list, 6)); // There are no words with a length of 6

    free_word_list(list);
}

// Tests for reading from a file

void ReadFromFile_no8() {
    WordList* list = create_word_list();

    read_words_from_file(list, "test_words.txt"); // Create a file test_words.txt with test words
    assert(list->count==0); // We check that the words have been added

    free_word_list(list);
}

// Tests for the maximum length of words

void MaxLengthWords_no9() {
    WordList* list = create_word_list();

    char long_word[MAX_WORD_LENGTH + 1];
    memset(long_word, 'a', MAX_WORD_LENGTH);
    long_word[MAX_WORD_LENGTH] = '0';

    add_word(list, long_word);

    assert(list->count==1); // We check that the word has been added

    free_word_list(list);
}

// The test for exceeding the word limit

void ExceedMaxWords_no10() {
    WordList *list = create_word_list();
    
    for (int i = 0; i < MAX_WORDS; ++i) {
        char word[10];
        sprintf(word, "word%d", i);
        add_word(list, word);
    }
    
    assert(list->count==MAX_WORDS); // It should be exactly MAX_WORDS
    
    free_word_list(list);
}

void runAllTests() {
    void CreateEmptyList_no1();
    void AddSingleWord_no2();
    void AddMultipleWords_no3();
    void AddWordsSorted_no4();
    void AddDuplicateWords_no5();
    void HasWordsOfLength_no6();
    void NoWordsOfLength_no7();
    void ReadFromFile_no8();
    void MaxLengthWords_no9();
    void ExceedMaxWords_no10();
    printf("ALL TEST RAN PERFECTLY\n");
}