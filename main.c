#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <intrin.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <locale.h>
#include "functions.h"
#include "tests.h"

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    system("chcp 1251");
    setlocale(LC_ALL, "Russian");
    TESTS();
    struct Node* head = NULL;
    char buffer[100];

    printf("Введите строки (Ctrl+Z для окончания ввода):\n");
    while (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;
        appendNode(&head, buffer);
    }

    char* result = concatenateStrings(head);

    printf("Результат: %s\n", result);

    free(result);
    freeList(head);

    return 0;
}