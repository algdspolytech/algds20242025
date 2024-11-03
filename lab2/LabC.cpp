#include "LabC.h"


// Функция считывающая слова
char** get_words_from_file(FILE* file) {
	size_t words_size = 0;
	size_t words_memory_size = 2;
	char** words = (char**)malloc(sizeof(char*) * words_memory_size);

	size_t word_size = 0;
	size_t word_memory_size = 2;
	char* word = (char*)malloc(word_memory_size);

	char sym;
	do {
		sym = getc(file);

		if (sym == ' ' || sym == '\n') {
			if (words_size >= words_memory_size) {
				words_memory_size *= 2;
				words = (char**)realloc(words, sizeof(char*)*words_memory_size);
			}

			word = (char*)realloc(word, word_size+1);
			word[word_size] = '\0';

			words[words_size] = word;
			words_size++;

			word_size = 0;
			word_memory_size = 2;
			word = (char*)malloc(word_memory_size);
		}
		else {
			if (word_size >= word_memory_size) {
				word_memory_size *= 2;
				word = (char*)realloc(word, word_memory_size);
			}

			word[word_size] = sym;
			word_size++;
		}
	} while (sym != '\n');
	words = (char**)realloc(words, sizeof(char*) * (words_size+1));
	words[words_size] = NULL;

	return words;
}

// Функция создающая словарь слов, где каждому слову сопоставляется число от 1 до n
HashMap* get_words_table(char** words) {
	size_t length = 0;
	while (words[length] != NULL) length++;

	HashMap* hm = CreateHashMap(1024);

	for (int i = 0;i < length;i++)
		AddItem(hm, words[i], i);

	return hm;
}

// Функция считывающая из файла связи между словами
int** get_segments(FILE* file, HashMap* dict) {

	int** graph = (int**)malloc(sizeof(int*) * dict->size);

	for (int i = 0;i < dict->size;i++) {
		graph[i] = (int*)malloc(sizeof(int) * dict->size);

		for (int j = 0;j < dict->size;j++)
			graph[i][j] = 0;
	}

	char* dich1 = (char*)malloc(30);
	char* dich2 = (char*)malloc(30);
	while (fscanf(file, "%s%s", dich1, dich2) != EOF) 
		graph[GetValue(dict, dich1)][GetValue(dict, dich2)] = 1;

	return graph;
}

// Рекурсивная функция топологической сортировки
void top_sort(int i, int* visited, int* st, int** graph, int length) {
	visited[i] = 1;

	for (int j = 0;j < length;j++) {
		if (graph[i][j] == 1) {
			if (visited[j] != 1) {
				top_sort(j, visited, st, graph, length);
			}
		}
	}

	int len = 0;
	while (st[len] != -1) len++;
	st[len] = i;
	st[len + 1] = -1;
}
