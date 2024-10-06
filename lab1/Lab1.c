#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char* result;          // Указатель на результат
    char* original_result; // Указатель на оригинальную строку, чтобы корректно
                           // очищать память
    int IsNegative; // 1 - если отрицательное, 0 - если положительное
} LongNumber;

LongNumber* Subtract_long_numbers(const char* num1, const char* num2);

LongNumber* Create_long_number(int length) {
    LongNumber* longnum = (LongNumber*)malloc(sizeof(LongNumber));
    longnum->original_result = (char*)malloc(
        (length + 1) * sizeof(char)); // Выделяем память для хранения числа
    for (int i = 0; i < length; i++)
        longnum->original_result[i] = '0';
    longnum->original_result[length] = '\0';
    longnum->result =
        longnum->original_result; // Начально результат равен началу строки
    return longnum;
}

void Free_long_number(LongNumber* longnum) {
    free(longnum->original_result);
    free(longnum);
}

void Print_long_number(LongNumber* longnum) {
    if (longnum->result[0] == '0') {
        printf("0");
        return;
    }
    if (longnum->IsNegative == 1)
        printf("-");
    printf("%s", longnum->result);
}

// Вспомогательная функция вычисляемая номер первого значащего разряда
int Find_significant_digit(int start, int maxLength, const char* ln) {
    int k = start; // Изначально указываем на первую значащую цифру после цикла
                   // сложения
    while (k < maxLength && ln[k] == '0') {
        k++; // Пропускаем ведущие нули
    }

    // Если все цифры — нули (например, "000"), то оставляем один ноль
    if (k == maxLength + 1) {
        k = maxLength; // Это значит, что все числа были нулями, и мы оставляем
                       // последний '0'
    }

    return k;
}
// Функция определяющая большее из двух длинных чисел. Возвращает 1 если
// num1>=num2, 0 если num1<num2
int IsBigger_long_numer(const char* num1, const char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int firstdigit1 = Find_significant_digit(0, len1, num1);
    int firstdigit2 = Find_significant_digit(0, len2, num2);

    int reallen1 = len1 - firstdigit1;
    int reallen2 = len2 - firstdigit2;

    if (reallen1 != reallen2) {
        return reallen1 > reallen2 ? 1 : 0;
    }

    // т.е. reallen1=reallen2
    int j = firstdigit2;
    for (int i = firstdigit1; i < len1; i++) {
        if (num1[i] > num2[j]) {
            return 1;
        } else {
            if (num1[i] < num2[j])
                return 0;
        }
        j++;
    }
    return 1;
}

LongNumber* Add_long_numbers(const char* num1, const char* num2) {
    char* n1 = num1;
    char* n2 = num2;

    int len1 = strlen(n1);
    int len2 = strlen(n2);

    int isNeg = 0;

    // проверка на отрицательные
    if (num1[0] == '-') {
        if (num2[0] == '-') {
            n1 = num1 + 1;
            n2 = num2 + 1;
            len1--;
            len2--;
            isNeg = 1;
        } else {
            return Subtract_long_numbers(num2, num1 + 1);
        }
    } else {
        if (num2[0] == '-') {
            return Subtract_long_numbers(num1, num2 + 1);
        } else {
            n1 = num1;
            n2 = num2;
        }
    }

    int maxLength = len1 > len2 ? len1 : len2;

    // Создаем длинное число с запасом памяти для возможного переноса
    LongNumber* result = Create_long_number(maxLength + 1);

    int carry = 0;
    int sum;
    int i = len1 - 1, j = len2 - 1, k = maxLength;

    // Основной цикл сложения
    while (i >= 0 || j >= 0 || carry) {
        sum = carry;
        if (i >= 0)
            sum += n1[i--] - '0';
        if (j >= 0)
            sum += n2[j--] - '0';
        carry = sum / 10;
        result->original_result[k--] = (sum % 10) + '0';
    }

    // Удаляем ведущие нули
    int start =
        Find_significant_digit(k + 1, maxLength, result->original_result);

    // Устанавливаем указатель на результат без ведущих нулей
    result->result = result->original_result + start;

    result->IsNegative = isNeg;
    //Считаем ноль - "положительным" числом
    if (result->result[0] == '0') {
        result->IsNegative = 0;
    }

    return result;
}

LongNumber* Subtract_long_numbers(const char* num1,
    const char* num2) { // Вычитает второе из первого + добавить проверку на то,
                        // что n1 >= n2

    char* n1 = num1;
    char* n2 = num2;

    int len1 = strlen(n1);
    int len2 = strlen(n2);

    int isNeg = 0;

    if (num1[0] == '-') {
        if (num2[0] == '-') {
            if (IsBigger_long_numer(num1 + 1, num2 + 1) == 1) {
                n1 = num1 + 1;
                len1--;
                n2 = num2 + 1;
                len2--;
                isNeg = 1;
            } else {
                int templen = len1;
                n1 = num2 + 1;
                len1 = len2 - 1;
                n2 = num1 + 1;
                len2 = templen - 1;
                isNeg = 0;
            }
        } else {
            n1 = num1 + 1;
            len1--;
            n2 = num2;
            isNeg = 1;
        }
    } else {
        if (num2[0] == '-') {
            return Add_long_numbers(num1, num2 + 1);
        } else {
            if (IsBigger_long_numer(num1, num2) == 1) {
                n1 = num1;
                n2 = num2;
                isNeg = 0;
            } else {
                int templen = len1;
                n1 = num2;
                len1 = len2;
                n2 = num1;
                len2 = templen;
                isNeg = 1;
            }
        }
    }

    // Создаем длинное число
    int maxLength = len1 > len2 ? len1 : len2;
    LongNumber* result = Create_long_number(maxLength + 1);

    int carry = 0;
    int temp = 0;
    int i = len1 - 1, j = len2 - 1, k = maxLength;

    // Основной цикл вычитания
    while (i >= 0 || j >= 0 || carry) {
        // Если i >= 0, используем цифру из num1, иначе считаем, что num1[i] = 0
        int digit1 = (i >= 0) ? n1[i] - '0' : 0;

        // Если j >= 0, используем цифру из num2, иначе считаем, что num2[j] = 0
        int digit2 = (j >= 0) ? n2[j] - '0' : 0;

        // Вычитаем с учётом переноса
        temp = digit1 - digit2 - carry;

        if (temp < 0) {
            temp += 10; // Заимствуем единицу из следующего разряда
            carry = 1; // Устанавливаем перенос
        } else {
            carry = 0;
        }

        result->original_result[k--] =
            temp + '0'; // Записываем результат в строку

        i--;
        j--;
    }

    // Удаляем ведущие нули
    int start =
        Find_significant_digit(k + 1, maxLength, result->original_result);
    // Устанавливаем указатель на результат без ведущих нулей
    result->result = result->original_result + start;

    result->IsNegative = isNeg;

    // Считаем ноль - "положительным" числом
    if (result->result[0] == '0') {
        result->IsNegative = 0;
    }

    return result;
}

LongNumber* Multiply_long_numbers(const char* num1, const char* num2) {

    char* n1 = num1;
    char* n2 = num2;

    // провека на отрицительные
    int isNeg = 0;
    if (num1[0] == '-') {
        n1 = num1 + 1;
        isNeg = 1;
    }
    if (num2[0] == '-') {
        n2 = num2 + 1;
        isNeg = isNeg == 0 ? 1 : 0;
    }
    int len1 = strlen(n1);
    int len2 = strlen(n2);
    int resultLen = len1 + len2;

    // Создаем длинное число для хранения результата умножения
    LongNumber* result = Create_long_number(resultLen);

    for (int i = len1 - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; j--) {
            int temp = (result->original_result[i + j + 1] - '0') +
                (n1[i] - '0') * (n2[j] - '0') + carry;
            carry = temp / 10;
            result->original_result[i + j + 1] =
                (temp % 10) + '0'; // происходит конвертирование в аски символ
        }
        result->original_result[i] += carry;
    }

    // Удаляем ведущие нули
    int start = 0;
    while (start < resultLen - 1 && result->original_result[start] == '0')
        start++;

    result->result = result->original_result + start;

    result->IsNegative = isNeg;

    // Считаем ноль - "положительным" числом
    if (result->result[0] == '0') {
        result->IsNegative = 0;
    }

    return result;
}

LongNumber* Power_long_numbers(const char* num, int exponent) {

    char* base = num;

    // провека на отрицительные
    int isNeg = 0;
    if (base[0] == '-') {
        base = num + 1;
        if (exponent % 2 != 0)
            isNeg = 1;
    }

    LongNumber* result = Create_long_number(1);
    result->original_result[0] = '1'; // Начальное значение - 1

    for (int i = 0; i < exponent; i++) {
        LongNumber* new_result = Multiply_long_numbers(result->result, base);
        free(
            result
                ->original_result); // Освобождаем память предыдущего результата
        free(result);
        result = new_result; // Новый результат становится текущим
    }

    result->IsNegative = isNeg;

    // Считаем ноль - "положительным" числом
    if (result->result[0] == '0') {
        result->IsNegative = 0;
    }

    return result;
}
/*
int main() {

    setlocale(LC_ALL, "ru");
    // Примеры использования функций
    LongNumber* ln;
    ln = Add_long_numbers("5", "-9");
    printf("Сложение чисел: ");
    Print_long_number(ln);
    printf("\n");
    Free_long_number(ln);
    ln = Multiply_long_numbers("-5", "-6");
    printf("Умножение чисел: ");
    Print_long_number(ln);
    printf("\n");
    Free_long_number(ln);
    ln = Power_long_numbers("-5", 0);
    printf("Возведение числа в сетепень: ");
    Print_long_number(ln);
    printf("\n");
    Free_long_number(ln);
    ln = Subtract_long_numbers("000000", "9");
    printf("Сложение чисел: ");
    Print_long_number(ln);
    Free_long_number(ln);

    return 0;
}
*/