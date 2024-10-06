#pragma once

typedef struct {
    char* result;
    char* original_result;
    int IsNegative;
} LongNumber;

LongNumber* Create_long_number(int length);
LongNumber* Add_long_numbers(const char* num1, const char* num2);
LongNumber* Subtract_long_numbers(const char* num1, const char* num2);
LongNumber* Multiply_long_numbers(const char* num1, const char* num2);
LongNumber* Power_long_numbers(const char* num, int exponent);
int Find_significant_digit(int start, int maxLength, const char* ln);
int IsBigger_long_numer(const char* num1, const char* num2);
void Free_long_number(LongNumber* longnum);
