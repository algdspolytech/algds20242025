#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 256

typedef struct Node {
    char data[MAX_STRING_LENGTH];
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    strncpy(newNode->data, data, MAX_STRING_LENGTH);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void addNode(Node* root) {
    char answer[MAX_STRING_LENGTH];
    printf("Это %s? (да/нет): ", root->data);
    scanf("%s", answer);

    if (strcmp(answer, "да") == 0) {
        if (root->left) {
            addNode(root->left);
        } else {
            printf("Введите ваш ответ (или вопрос): ");
            scanf(" %s", answer);
            root->left = createNode(answer);
        }
    } else if (strcmp(answer, "нет") == 0) {
        if (root->right) {
            addNode(root->right);
        } else {
            printf("Введите ваш ответ (или вопрос): ");
            scanf(" %s", answer);
            root->right = createNode(answer);
        }
    } else {
        printf("Ответ должен быть \"да\" или \"нет\". Попробуйте снова.\n");
    }
}

void saveTree(FILE* file, Node* root) {
    if (root == NULL) {
        fprintf(file, "#\n"); // Маркер конца узла
        return;
    }
    fprintf(file, "%s\n", root->data);
    saveTree(file, root->left);
    saveTree(file, root->right);
}

Node* loadTree(FILE* file) {
    char buffer[MAX_STRING_LENGTH];
    if (!fgets(buffer, MAX_STRING_LENGTH, file)) {
        return NULL;
    }

    // Удаляем символ новой строки
    buffer[strcspn(buffer, "\n")] = 0;

    if (strcmp(buffer, "#") == 0) {
        return NULL;
    }

    Node* root = createNode(buffer);
    root->left = loadTree(file);
    root->right = loadTree(file);
    return root;
}

void printTree(Node* root, int level) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("%s\n", root->data);
    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}

void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void init() {
    Node* root = NULL;
    int choice;
    char filename[MAX_STRING_LENGTH];
    FILE* fp;

    do {
        printf("\nМеню:\n");
        printf("1. Создать корневой узел\n");
        printf("2. Добавить узел\n");
        printf("3. Сохранить дерево в файл\n");
        printf("4. Загрузить дерево из файла\n");
        printf("5. Вывести дерево\n");
        printf("6. Выйти\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (root) {
                    printf("Корневой узел уже существует!\n");
                } else {
                    printf("Введите корневой вопрос/ответ: ");
                    scanf(" %s", filename);
                    root = createNode(filename);
                }
                break;
            case 2:
                if (!root) {
                    printf("Создайте корневой узел сначала!\n");
                } else {
                    addNode(root);
                }
                break;
            case 3:
                printf("Введите имя файла для сохранения: ");
                scanf("%s", filename);
                fp = fopen(filename, "w");
                if (!fp) {
                    perror("Ошибка открытия файла");
                    break;
                }
                saveTree(fp, root);
                fclose(fp);
                printf("Дерево сохранено!\n");
                break;
            case 4:
                printf("Введите имя файла для загрузки: ");
                scanf("%s", filename);
                fp = fopen(filename, "r");
                if (!fp) {
                    perror("Ошибка открытия файла");
                    break;
                }
                freeTree(root);
                root = loadTree(fp);
                fclose(fp);
                printf("Дерево загружено!\n");
                break;
            case 5:
                if (!root) {
                    printf("Дерево пусто!\n");
                } else {
                    printTree(root, 0);
                }
                break;
            case 6:
                printf("Выход...\n");
                break;
            default:
                printf("Неверный выбор!\n");
        }
    } while (choice != 6);

    freeTree(root);
}
