
#include "binary_tree.h"

#include <string.h>

// Функция для интерактивного создания дерева
void interactiveCreateTree(TreeNode** root) {
    int choice, value;
    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавить узел\n");
        printf("2. Сохранить дерево в файл\n");
        printf("3. Загрузить дерево из файла\n");
        printf("4. Печать дерева (префиксный порядок)\n");
        printf("5. Печать дерева (инфиксный порядок)\n");
        printf("6. Печать дерева (постфиксный порядок)\n");
        printf("7. Выход\n");
        printf("Выберите действие: ");
        if (scanf("%d", &choice) != 1) {
            printf("Некорректный ввод.\n");
            // Очистить буфер ввода
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1:
            printf("Введите значение узла: ");
            if (scanf("%d", &value) != 1) {
                printf("Некорректный ввод.\n");
                while (getchar() != '\n');
                continue;
            }
            *root = insertNode(*root, value);
            printf("Узел добавлен.\n");
            break;
        case 2: {
            char filename[256];
            printf("Введите имя файла для сохранения: ");
            scanf("%s", filename);
            if (saveTreeToFile(*root, filename)) {
                printf("Дерево сохранено в файл %s.\n", filename);
            }
            else {
                printf("Не удалось сохранить дерево.\n");
            }
            break;
        }
        case 3: {
            char filename[256];
            printf("Введите имя файла для загрузки: ");
            scanf("%s", filename);
            TreeNode* loadedTree = loadTreeFromFile(filename);
            if (loadedTree) {
                freeTree(*root);
                *root = loadedTree;
                printf("Дерево загружено из файла %s.\n", filename);
            }
            else {
                printf("Не удалось загрузить дерево.\n");
            }
            break;
        }
        case 4:
            printf("Печать дерева (префиксный порядок):\n");
            printTreePreOrder(*root, stdout);
            printf("\n");
            break;
        case 5:
            printf("Печать дерева (инфиксный порядок):\n");
            printTreeInOrder(*root, stdout);
            printf("\n");
            break;
        case 6:
            printf("Печать дерева (постфиксный порядок):\n");
            printTreePostOrder(*root, stdout);
            printf("\n");
            break;
        case 7:
            return;
        default:
            printf("Некорректный выбор. Попробуйте снова.\n");
        }
    }
}
#ifdef RUN_TESTS
int main() {
    setlocale(LC_ALL, "RUS");
    TreeNode* root = NULL;
    interactiveCreateTree(&root);
    freeTree(root);
    return 0;
}
#endif // RUN_TESTS