#include "Dasha_LabA.h"
#include "stdlib.h"

int main() {
  FILE *fp = fopen("text.txt", "r");

  // Считываем слова их файла
  char **words = download_words(fp);
  sort_words(words);

  // Получаем слова длинной больше N
  char **new_words = get_words_longer_n(words, N);
  int i = 0;
  while (new_words[i] != NULL) {
    printf("%s\n", new_words[i]);
    i++;
  }

  // Считываем число с клавиатуры
  int n;
  scanf("%i", &n);

  // Получаем слова длинной ровно n
  new_words = get_words_long_n(words, n);

  if (new_words != NULL) {
    i = 0;
    while (new_words[i] != NULL) {
      printf("%s\n", new_words[i]);
      i++;
    }
  }

  return 0;
}
