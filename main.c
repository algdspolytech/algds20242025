
#include "binary_tree.h"

#include <string.h>

// ������� ��� �������������� �������� ������
void interactiveCreateTree(TreeNode** root) {
    int choice, value;
    while (1) {
        printf("\n����:\n");
        printf("1. �������� ����\n");
        printf("2. ��������� ������ � ����\n");
        printf("3. ��������� ������ �� �����\n");
        printf("4. ������ ������ (���������� �������)\n");
        printf("5. ������ ������ (��������� �������)\n");
        printf("6. ������ ������ (����������� �������)\n");
        printf("7. �����\n");
        printf("�������� ��������: ");
        if (scanf("%d", &choice) != 1) {
            printf("������������ ����.\n");
            // �������� ����� �����
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1:
            printf("������� �������� ����: ");
            if (scanf("%d", &value) != 1) {
                printf("������������ ����.\n");
                while (getchar() != '\n');
                continue;
            }
            *root = insertNode(*root, value);
            printf("���� ��������.\n");
            break;
        case 2: {
            char filename[256];
            printf("������� ��� ����� ��� ����������: ");
            scanf("%s", filename);
            if (saveTreeToFile(*root, filename)) {
                printf("������ ��������� � ���� %s.\n", filename);
            }
            else {
                printf("�� ������� ��������� ������.\n");
            }
            break;
        }
        case 3: {
            char filename[256];
            printf("������� ��� ����� ��� ��������: ");
            scanf("%s", filename);
            TreeNode* loadedTree = loadTreeFromFile(filename);
            if (loadedTree) {
                freeTree(*root);
                *root = loadedTree;
                printf("������ ��������� �� ����� %s.\n", filename);
            }
            else {
                printf("�� ������� ��������� ������.\n");
            }
            break;
        }
        case 4:
            printf("������ ������ (���������� �������):\n");
            printTreePreOrder(*root, stdout);
            printf("\n");
            break;
        case 5:
            printf("������ ������ (��������� �������):\n");
            printTreeInOrder(*root, stdout);
            printf("\n");
            break;
        case 6:
            printf("������ ������ (����������� �������):\n");
            printTreePostOrder(*root, stdout);
            printf("\n");
            break;
        case 7:
            return;
        default:
            printf("������������ �����. ���������� �����.\n");
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