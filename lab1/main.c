#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define _CRTDBG_MAP_ALLOC

#include <stdio.h>
#include "labA.h"

// Creating a list of words
WordList* create_word_list() {
    WordList* list = (WordList*)malloc(sizeof(WordList));
    list->words = (Word*)malloc(MAX_WORDS * sizeof(Word));
    list->count = 0;
    return list;
}

// A function for adding a word to a sorted list
void add_word(WordList* list, const char* word) {
    if (list->count >= MAX_WORDS) return;

    strcpy(list->words[list->count].word, word);
    list->count++;

    // Sorting the list after adding a new word
    for (int i = list->count - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (strlen(list->words[j].word) > strlen(list->words[j + 1].word) ||
                (strlen(list->words[j].word) == strlen(list->words[j + 1].word) &&
                    strcmp(list->words[j].word, list->words[j + 1].word) > 0)) {
                Word temp = list->words[j];
                list->words[j] = list->words[j + 1];
                list->words[j + 1] = temp;
            }
        }
    }
}

// Function for reading words from a file
void read_words_from_file(WordList* list, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("File opening error");
        return;
    }

    char buffer[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", buffer) != EOF) {
        add_word(list, buffer);
    }

    fclose(file);
}

// Function for output of words longer than N
void print_words_longer_than(WordList* list, int N) {
    for (int i = 0; i < list->count; i++) {
        if (strlen(list->words[i].word) > N) {
            printf("%s\n", list->words[i].word);
        }
    }
}

// A function to check for the presence of words of a certain length
int has_words_of_length(WordList* list, int N) {
    for (int i = 0; i < list->count; i++) {
        if (strlen(list->words[i].word) == N) {
            return 1; // The word is found
        }
    }
    return 0; // The word was not found
}

// Freeing up memory
void free_word_list(WordList* list) {
    free(list->words);
    free(list);
}

int main() {
    void runAllTests(); 
    WordList* list = create_word_list();

    // Reading words from a file
    read_words_from_file(list, "words.txt");

    int N;
    printf("Enter the number N: ");
    scanf("%d", &N);

    printf("Words longer than %d: \n", N);
    print_words_longer_than(list, N);

    if (has_words_of_length(list, N)) {
        printf("The list contains words of length %d\n", N);
    }
    else {
        printf("The list does not contain a word in length %d\n", N);
    }

    free_word_list(list); // Freeing up memory
    return 0;
}
