#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "tree.h"

void runTest(const char* input, const char* expectedOutput, int i) {
    FILE* inputFile = fopen("input.txt", "w");
    if (inputFile == NULL) {
        perror("������ �������� input.txt");
        return;
    }
    fprintf(inputFile, "%s", input);
    fclose(inputFile);

    execute_algorithm();

    FILE* outputFile = fopen("output.txt", "r");
    if (outputFile == NULL) {
        perror("������ �������� output.txt");
        return;
    }

    size_t outputSize = 512;
    char* output = (char*)malloc(outputSize);
    if (output == NULL) {
        perror("������ ��������� ������");
        fclose(outputFile);
        return;
    }

    // ������ ���������� �� �����
    size_t bytesRead = fread(output, sizeof(char), outputSize - 1, outputFile);
    output[bytesRead] = '\0'; // ��������� ������ ������� ��������
    fclose(outputFile);

    if (strcmp(output, expectedOutput) == 0) {
        printf("���� %d �������\n", i);
    }
    else {
        printf("���� %d �� �������!\n", i);
        printf("�������: %s\n", expectedOutput);
        printf("��������: %s\n", output);
    }
    free(output);
}

int main() {
    setlocale(LC_ALL, "RUS");

    // ���� 1: ������ ������
    runTest("", "", 1);

    // ���� 2: ���� �����
    runTest("hello\n", "hello\n5\n", 2);

    // ���� 3: ������ � ����� ������
    runTest("hello\nworld\n", "hello\n5\nworld\n5\n", 3);

    // ���� 4: ��������������� ������
    runTest("cat\ndog\nfish\n", "cat\n3\ndog\n3\nfish\n4\n", 4);

    // ���� 5: �� ���������������� ������
    runTest("a\nab\nabc\nabcd\n", "a\n1\nab\n2\nabc\n3\nabcd\n4\n", 5);

    // ���� 6: ������ � ����������� ������� ����
    runTest("one\ntwo\nred\nblue\n", "blue\n4\none\n3\nred\n3\ntwo\n3\n", 6);

    // ���� 7: ��������� ������
    runTest("apple\norange\nbanana\nkiwi\n", "apple\n5\nbanana\n6\nkiwi\n4\norange\n6\n", 7);

    // ���� 8: ���� � ��������� � ������
    runTest("hello world\ntest case\n", "hello world\n11\ntest case\n9\n", 8);

    // ���� 9: ������ � ������
    runTest("!@#$%\n^&*()_+\n", "!@#$%\n5\n^&*()_+\n7\n", 9);

    // ���� 10: ������� ������
    runTest("medium\nverylongword\nshort\ntiny\nthequickbrownfox\n",
        "medium\n6\nshort\n5\nthequickbrownfox\n16\ntiny\n4\nverylongword\n12\n", 10);

    // ���� 11 (�� README)
    runTest("cat\ndog\nfish\n", "cat\n3\ndog\n3\nfish\n4\n", 11);

    return 0;
}
