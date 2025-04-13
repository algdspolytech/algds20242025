#include "code.h"
#include <stdlib.h>
#include <math.h>

// Функция для создания нового узла дерева
Node* create(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Выделяем память под новый узел
    newNode->value = value;                      // Устанавливаем значение узла
    newNode->left = newNode->right = NULL;      // Инициализируем указатели на поддеревья как NULL
    return newNode;                              // Возвращаем указатель на новый узел
}

// Функция для освобождения памяти дерева
void free(Node* node) {
    if (node) {                                  // Если узел не пустой,
        free(node->left);                   // освобождаем левое поддерево.
        free(node->right);                  // освобождаем правое поддерево.
        free(node);                              // освобождаем память текущего узла.
    }
}

// Рекурсивная функция для чтения дерева из массива данных
static Node* recursiveRead(const int* data, int index, int length) {
    if (index >= length) return NULL;            // Если индекс выходит за пределы массива, возвращаем NULL.

    Node* node = create(data[index]);       // Создаем новый узел с текущим значением.
    node->left = recursiveRead(data, 2 * index + 1, length);  // Левый потомок.
    node->right = recursiveRead(data, 2 * index + 2, length); // Правый потомок.

    return node;                                 // Возвращаем созданный узел.
}

// Функция для чтения дерева из файла
Node* read(FILE* file) {
    int* data = NULL;
    int length = 0;

    while (1) {
        data = (int*)realloc(data, sizeof(int) * (length + 1));  // Увеличиваем размер массива данных.
        if (fscanf(file, "%i", &data[length]) == EOF) break;      // Читаем данные из файла до конца файла.
        length++;
    }

    Node* root = recursiveRead(data, 0, length);   // Возвращаем корень дерева.
    free(data);                                           // Освобождаем память массива данных.

    return root;
}

// Функция для получения глубины дерева
static int getDepth(const Node* node) {
    return node ? 1 + max(getDepth(node->left), getDepth(node->right)) : 0;  // Глубина равна 1 + максимальная глубина из левого и правого поддеревьев.
}

// Функция для печати отступов в выводе 
static void fprint_tab(FILE* out, int n) {
    for (int i = 0; i < n; i++) fprintf(out, " ");   // Печатаем пробелы для отступа.
}

// Функция для отображения дерева в виде уровней (первый способ)
void Tree1(FILE* out, const Node* node) {
    if (!node) return;

    const int symbolWidth = 4;
    int depth = getDepth(node);
    int currentLength = 1;
    Node** currentLine = malloc(sizeof(Node*) * currentLength);
    currentLine[0] = (Node*)node;

    int totalWidth = (pow(2, depth)) * (symbolWidth + 1);

    for (int i = 0; i < depth; i++) {
        int items = currentLength;
        int tab = (totalWidth - symbolWidth * items) / (pow(2, i + 1));

        for (int j = 0; j < currentLength; j++) {
            fprint_tab(out, tab);
            fprintf(out, "%4i", currentLine[j]->value);
        }
        fprint_tab(out, tab);
        fprintf(out, "\n");

        Node** nextLine = malloc(sizeof(Node*) * currentLength * 2);
        for (int j = 0; j < currentLength; j++) {
            nextLine[j * 2] = currentLine[j]->left;
            nextLine[j * 2 + 1] = currentLine[j]->right;
        }

        free(currentLine);
        currentLine = nextLine;
        currentLength *= 2;
    }

    free(currentLine);
}

// Функция для отображения дерева в виде последовательности значений (второй способ)
void Tree2(FILE* out, const Node* node) {
    if (!node) return;

    fprintf(out, "%i ", node->value);              // Печатаем значение текущего узла.

    Tree2(out, node->left);                 // Рекурсивно печатаем левое поддерево.
    Tree2(out, node->right);                // Рекурсивно печатаем правое поддерево.
}