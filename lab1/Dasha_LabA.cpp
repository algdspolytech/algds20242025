#include "Dasha_LabA.h"

#include <stdbool.h>
#include <stdlib.h>

// Функция для считывания списка слов из файла (считается что они разделены
// символом пробела)
char **download_words(FILE *fp) {
  int word_length = 0;
  int word_memory_size = 8;

  char *word = (char *)malloc(word_memory_size);

  int words_length = 0;
  int words_memory_size = 8;
  char **words = (char **)malloc(sizeof(char *) * words_memory_size);

  char sym;
  do {
    sym = fgetc(fp);
    if (sym == ' ' || sym == EOF) {
      word = (char *)realloc(word, word_length + 1);
      word[word_length] = '\0';

      if (words_length >= words_memory_size) {
        words_memory_size *= 2;
        words = (char **)realloc(words, sizeof(char *) * words_memory_size);
      }

      words[words_length] = word;
      words_length++;

      if (sym == EOF) {
        words = (char **)realloc(words, sizeof(char *) * (words_length + 1));
        words[words_length] = NULL;
      }

      word_length = 0;
      word_memory_size = 8;
      word = (char *)malloc(word_memory_size);
    } else {
      if (word_length >= word_memory_size) {
        word_memory_size *= 2;
        word = (char *)realloc(word, word_memory_size);
      }

      word[word_length] = sym;
      word_length++;
    }
  } while (sym != EOF);

  return words;
}

// Функция для сравнения двух строк
int compare_strings_gt(const void *_s1, const void *_s2) {
  char *s1 = *(char **)_s1;
  char *s2 = *(char **)_s2;

  // Сначала сравним длинну
  int i = 0;
  while (s1[i] != '\0' && s2[i] != '\0')
    i++;

  if (s1[i] == '\0' && s2[i] != '\0')
    return -1;
  if (s1[i] != '\0' && s2[i] == '\0')
    return 1;

  // Если их длинна равна начинаем сравнивать по алфавиту
  for (int j = 0; j < i; j++) {
    if (s1[j] > s2[j])
      return 1;
    if (s1[j] < s2[j])
      return -1;
  }

  return 0;
}

// Функция для сортировки списка слов
char **sort_words(char **words) {
  int words_length = 0;
  while (words[words_length] != NULL)
    words_length++;

  qsort(words, words_length, sizeof(char *), compare_strings_gt);
  return words;
}

// Функция возвращает список слов длинной больше чем n (принимает на вход
// ОТСОРТИРОВАННЫЙ ПО НЕУБЫВАНИЮ массив слов)
char **get_words_longer_n(char **words, int n) {
  int words_length = 0;
  while (words[words_length] != NULL)
    words_length++;

  int m = words_length;

  for (int i = 0; i < words_length; i++) {
    int length = 0;
    while (words[i][length] != '\0')
      length++;

    if (length > n) {
      m = i;
      break;
    }
  }

  char **n_words = (char **)malloc(sizeof(char *) * (words_length - m + 1));
  for (int i = 0; i < words_length - m; i++)
    n_words[i] = words[i + m];
  n_words[words_length - m] = NULL;

  return n_words;
}

// Функция возвращает список слов длинной n (принимает на вход ОТСОРТИРОВАННЫЙ
// ПО НЕУБЫВАНИЮ массив слов)
char **get_words_long_n(char **words, int n) {
  int words_length = 0;
  while (words[words_length] != NULL)
    words_length++;

  int m = words_length;
  int m2 = words_length;

  bool flag = false;

  for (int i = 0; i < words_length; i++) {
    int length = 0;
    while (words[i][length] != '\0')
      length++;

    if (length >= n && !flag) {
      m = i;
      flag = true;
    }

    if (length > n) {
      m2 = i;
      break;
    }
  }

  if (m == m2)
    return NULL;

  char **n_words = (char **)malloc(sizeof(char *) * (m2 - m + 1));
  for (int i = 0; i < m2 - m; i++)
    n_words[i] = words[i + m];
  n_words[m2 - m] = NULL;

  return n_words;
}
