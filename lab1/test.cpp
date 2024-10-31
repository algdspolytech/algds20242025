#include "../Dasha_LabA/Dasha_LabA.cpp"
#include "pch.h"

// Проверяем функцию сравнения строк в случае равенства строк
TEST(WordsLibTests, CompareStringsGt_EqualStrings_1) {
  char word1[] = "aibfyuef";
  char word2[] = "aibfyuef";

  char **w1 = (char **)malloc(sizeof(char *));
  char **w2 = (char **)malloc(sizeof(char *));

  w1[0] = word1;
  w2[0] = word2;

  int a = compare_strings_gt(w1, w2);

  free(w1);
  free(w2);

  EXPECT_EQ(0, a);
}

// Проверяем функцию сравнения строк в случае пустых строк
TEST(WordsLibTests, CompareStringsGt_EmptyString_10) {
  char word1[] = "";
  char word2[] = "";

  char **w1 = (char **)malloc(sizeof(char *));
  char **w2 = (char **)malloc(sizeof(char *));

  w1[0] = word1;
  w2[0] = word2;

  int a = compare_strings_gt(w1, w2);

  free(w1);
  free(w2);

  EXPECT_EQ(0, a);
}

// Проверяем функцию сравнения строк в случае разной длинны строк
TEST(WordsLibTests, CompareStringsGt_DiffLengths_2) {
  char word1[] = "werwer";
  char word2[] = "werwe";

  char **w1 = (char **)malloc(sizeof(char *));
  char **w2 = (char **)malloc(sizeof(char *));

  w1[0] = word1;
  w2[0] = word2;

  int a = compare_strings_gt(w1, w2);

  free(w1);
  free(w2);

  EXPECT_EQ(1, a);
}
// Проверяем функцию сравнения строк в случае строк одной длинны с разными
// буквами строк
TEST(WordsLibTests, CompareStringsGt_EqualLength_3) {
  char word1[] = "werwer";
  char word2[] = "werwez";

  char **w1 = (char **)malloc(sizeof(char *));
  char **w2 = (char **)malloc(sizeof(char *));

  w1[0] = word1;
  w2[0] = word2;

  int a = compare_strings_gt(w1, w2);

  free(w1);
  free(w2);

  EXPECT_EQ(-1, a);
}

// Тест сортировки пустого списка
TEST(WordsLibTests, DownloadWords_EmptyList_4) {

  char **w1 = (char **)malloc(sizeof(char *));
  char **w2 = (char **)malloc(sizeof(char *));

  w1[0] = NULL;
  w2[0] = NULL;

  w2 = sort_words(w2);

  EXPECT_EQ(w1[0], w2[0]);

  free(w1);
  free(w2);
}

// Тест сортировки списка из слов
TEST(WordsLibTests, DownloadWords_LoadFile_5) {
  char word1[] = "werwea";
  char word2[] = "werweb";
  char word3[] = "werwec";
  char word4[] = "werwezd";

  char **w1 = (char **)malloc(sizeof(char *) * 5);
  char **w2 = (char **)malloc(sizeof(char *) * 5);

  w1[0] = word1;
  w1[1] = word2;
  w1[2] = word3;
  w1[3] = word4;
  w1[4] = NULL;

  for (int i = 0; i < 5; i++)
    w2[i] = w1[(i + 2) % 4];
  w2[4] = NULL;

  w2 = sort_words(w2);

  for (int i = 0; i < 4; i++)
    EXPECT_EQ(w1[i], w2[i]);

  free(w1);
  free(w2);
}

// Тест получения списка слов длинной N
TEST(WordsLibTests, DownloadWords_LoadFile_6) {
  char word1[] = "werwea";
  char word2[] = "werweb";
  char word3[] = "werwec";
  char word4[] = "werwezd";

  char **w1 = (char **)malloc(sizeof(char *) * 5);

  w1[0] = word1;
  w1[1] = word2;
  w1[2] = word3;
  w1[3] = word4;
  w1[4] = NULL;

  char **w2 = get_words_long_n(w1, 6);

  for (int i = 0; i < 3; i++)
    EXPECT_EQ(w1[i], w2[i]);
}

// Тест получения списка слов длинной N в случае если таких слов нет
TEST(WordsLibTests, DownloadWords_LoadFile_7) {
  char word1[] = "werwea";
  char word2[] = "werweb";
  char word3[] = "werwec";
  char word4[] = "werwezd";

  char **w1 = (char **)malloc(sizeof(char *) * 5);

  w1[0] = word1;
  w1[1] = word2;
  w1[2] = word3;
  w1[3] = word4;
  w1[4] = NULL;

  char **w2 = get_words_long_n(w1, 5);

  EXPECT_EQ(w2, (char **)NULL);
}

// Тест получения списка слов больше N
TEST(WordsLibTests, DownloadWords_LoadFile_8) {
  char word1[] = "werwea";
  char word2[] = "werweb";
  char word3[] = "werwec";
  char word4[] = "werwezd";

  char **w1 = (char **)malloc(sizeof(char *) * 5);

  w1[0] = word1;
  w1[1] = word2;
  w1[2] = word3;
  w1[3] = word4;
  w1[4] = NULL;

  char **w2 = get_words_longer_n(w1, 6);

  EXPECT_EQ(w2[0], word4);
}

// Тест получения списка слов больше N в случае если таких слов нет
TEST(WordsLibTests, DownloadWords_LoadFile_9) {
  char word1[] = "werwea";
  char word2[] = "werweb";
  char word3[] = "werwec";
  char word4[] = "werwezd";

  char **w1 = (char **)malloc(sizeof(char *) * 5);

  w1[0] = word1;
  w1[1] = word2;
  w1[2] = word3;
  w1[3] = word4;
  w1[4] = NULL;

  char **w2 = get_words_longer_n(w1, 7);

  EXPECT_EQ(w2, (char **)NULL);
}
