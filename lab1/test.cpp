#include "../LabA/LabA.cpp"
#include "pch.h"

// Проверка инициализвации числа из строки
TEST(SuperHugeNumber_CreateNumberTest, number_from_string__1) {
  SuperHugeNum *num1 = number_from_string("653");
  int num2[2] = {53, 6};

  for (int i = 0; i < 2; i++)
    EXPECT_EQ(num1->number[i], num2[i]);
  free_number(num1);
}

// Проверка инициализвации числа из другого числа
TEST(SuperHugeNumber_CreateNumberTest, number_from_number__2) {
  SuperHugeNum *num0 = number_from_string("653");
  SuperHugeNum *num1 = new_number_from_number(num0);
  int num2[2] = {53, 6};

  for (int i = 0; i < 2; i++)
    EXPECT_EQ(num1->number[i], num2[i]);

  free_number(num0);
  free_number(num1);
}

// Проверка сложения чисел с нулем
TEST(SuperHugeNumber_AddNumberTest, add_number_AddZero__3) {
  SuperHugeNum *num0 = number_from_string("653");
  SuperHugeNum *num1 = number_from_string("0");
  uint8_t num2[2] = {53, 6};

  add_number(num0, num1);

  for (int i = 0; i < 2; i++)
    EXPECT_EQ(num0->number[i], num2[i]);

  free_number(num0);
  free_number(num1);
}

// Проверка сложения чисел с другим числом
TEST(SuperHugeNumber_AddNumberTest, add_number_AddNumber__4) {
  SuperHugeNum *num0 = number_from_string("653");
  SuperHugeNum *num1 = number_from_string("123");
  int num2[2] = {76, 7};

  add_number(num0, num1);

  for (int i = 0; i < 2; i++)
    EXPECT_EQ(num0->number[i], num2[i]);

  free_number(num0);
  free_number(num1);
}

// Проверка умножения чисела на маленькое число (обычный int)
TEST(SuperHugeNumber_MulNumberTest, short_mul_number__5) {
  SuperHugeNum *num0 = number_from_string("653");
  uint8_t num1 = 7;
  int num2[2] = {71, 45};

  short_mul_number(num0, num1);

  for (int i = 0; i < 2; i++)
    EXPECT_EQ(num0->number[i], num2[i]);

  free_number(num0);
}

// Проверка умнжения числа на число
TEST(SuperHugeNumber_MulNumberTest, mul_number_MulNumber__6) {
  SuperHugeNum *num0 = number_from_string("653");
  SuperHugeNum *num1 = number_from_string("123");
  int num2[3] = {19, 3, 8};

  mul_number(num0, num1);

  for (int i = 0; i < 3; i++)
    EXPECT_EQ(num0->number[i], num2[i]);

  free_number(num0);
  free_number(num1);
}

// Проверка умножения числа на 0
TEST(SuperHugeNumber_MulNumberTest, mul_number_MulZero__7) {
  SuperHugeNum *num0 = number_from_string("653");
  SuperHugeNum *num1 = number_from_string("0");
  int num2[2] = {0, 0};

  mul_number(num0, num1);

  for (int i = 0; i < 2; i++)
    EXPECT_EQ(num0->number[i], num2[i]);

  free_number(num0);
  free_number(num1);
}

// Проверка умнжения числа на 1
TEST(SuperHugeNumber_MulNumberTest, mul_number_MulOne__8) {
  SuperHugeNum *num0 = number_from_string("653");
  SuperHugeNum *num1 = number_from_string("1");
  int num2[2] = {53, 6};

  mul_number(num0, num1);

  for (int i = 0; i < 2; i++)
    EXPECT_EQ(num0->number[i], num2[i]);

  free_number(num0);
  free_number(num1);
}

// Проверка возведения числа в 1 степень
TEST(SuperHugeNumber_PowNumberTest, pow_number_PowOne__9) {
  SuperHugeNum *num0 = number_from_string("653");

  pow_number(num0, 1);

  int num2[2] = {53, 6};

  for (int i = 0; i < 2; i++)
    EXPECT_EQ(num0->number[i], num2[i]);

  free_number(num0);
}

// Проверка возведения числа в 0 степень
TEST(SuperHugeNumber_PowNumberTest, pow_number_PowZero__10) {

  SuperHugeNum *num0 = number_from_string("53");

  pow_number(num0, 0);

  int num2[1] = {1};

  EXPECT_EQ(num0->number[0], num2[0]);

  free_number(num0);
}

// Проверка возведения числа в небольшую степень(int) степень
TEST(SuperHugeNumber_PowNumberTest, pow_number_PowNumber__11) {

  SuperHugeNum *num0 = number_from_string("53");

  pow_number(num0, 3);

  int num2[3] = {77, 88, 14};

  for (int i = 0; i < 3; i++)
    EXPECT_EQ(num0->number[i], num2[i]);

  free_number(num0);
}