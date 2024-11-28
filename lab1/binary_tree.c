#include "binary_tree.h"
#pragma warning(disable:4996)

TreeNode* create_new_node(int value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->node_count = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Процедура добавления узла в бинарное дерево
void insert(TreeNode** root, int value) {
    TreeNode* new_node = create_new_node(value);

    if (*root == NULL) {
        *root = new_node;
        return;
    }

    TreeNode* stack[MAX_STACK_SIZE];
    int top = -1;
    TreeNode* current = *root;

    while (1) {
        // Сохраняем путь к узлу в стеке
        if (top < MAX_STACK_SIZE - 1) {
            stack[++top] = current;
        }
        else {
            printf("Переполнение стека при вставке\n");
            free(new_node);
            return;
        }

        // Сравниваем количество узлов в левом и правом поддеревьях
        int left_count = (current->left) ? current->left->node_count : 0;
        int right_count = (current->right) ? current->right->node_count : 0;

        if (left_count <= right_count) {
            if (current->left == NULL) {
                current->left = new_node;
                break;
            }
            else {
                current = current->left;
            }
        }
        else {
            if (current->right == NULL) {
                current->right = new_node;
                break;
            }
            else {
                current = current->right;
            }
        }
    }

    // Обновляем количество узлов в пути от вставленного узла к корню
    while (top >= 0) {
        TreeNode* node = stack[top--];
        node->node_count = 1 +
            ((node->left) ? node->left->node_count : 0) +
            ((node->right) ? node->right->node_count : 0);
    }
}

// Процедура удаления узла из бинарного дерева
void delete_node(TreeNode** root, int value) {
    if (*root == NULL) {
        printf("Дерево пусто\n");
        return;
    }

    typedef struct NodeParentPair {
        TreeNode* node;
        TreeNode* parent;
    } NodeParentPair;

    NodeParentPair queue[MAX_QUEUE_SIZE];
    int front = 0;
    int rear = 0;

    // Начинаем обход дерева в ширину
    queue[rear++] = (NodeParentPair){ *root, NULL };

    TreeNode* node_to_delete = NULL;
    TreeNode* parent_of_node_to_delete = NULL;
    TreeNode* deepest_node = NULL;
    TreeNode* parent_of_deepest_node = NULL;

    while (front < rear) {
        NodeParentPair np = queue[front++];
        TreeNode* current = np.node;
        TreeNode* parent = np.parent;

        // Обновляем информацию о самом глубоком узле
        deepest_node = current;
        parent_of_deepest_node = parent;

        // Проверяем, является ли текущий узел тем, который нужно удалить
        if (current->value == value) {
            node_to_delete = current;
            parent_of_node_to_delete = parent;
        }

        // Добавляем левого потомка в очередь
        if (current->left != NULL) {
            if (rear < MAX_QUEUE_SIZE) {
                queue[rear++] = (NodeParentPair){ current->left, current };
            }
            else {
                printf("Переполнение очереди при удалении\n");
                return;
            }
        }

        // Добавляем правого потомка в очередь
        if (current->right != NULL) {
            if (rear < MAX_QUEUE_SIZE) {
                queue[rear++] = (NodeParentPair){ current->right, current };
            }
            else {
                printf("Переполнение очереди при удалении\n");
                return;
            }
        }
    }

    if (node_to_delete == NULL) {
        printf("Узел со значением %d не найден\n", value);
        return;
    }

    // Заменяем значение узла на значение самого глубокого узла
    node_to_delete->value = deepest_node->value;

    // Удаляем самый глубокий узел
    if (parent_of_deepest_node == NULL) {
        // Дерево состоит из одного узла
        free(*root);
        *root = NULL;
        return;
    }
    else {
        if (parent_of_deepest_node->left == deepest_node) {
            parent_of_deepest_node->left = NULL;
        }
        else if (parent_of_deepest_node->right == deepest_node) {
            parent_of_deepest_node->right = NULL;
        }
        free(deepest_node);
    }

    // Пересчитываем количество узлов в дереве
    typedef struct StackNode {
        TreeNode* node;
        int visited;
    } StackNode;

    StackNode stack[MAX_STACK_SIZE];
    int top = -1;

    if (*root != NULL) {
        stack[++top] = (StackNode){ *root, 0 };
    }

    while (top >= 0) {
        StackNode* sn = &stack[top];
        if (sn->node == NULL) {
            top--;
            continue;
        }

        if (sn->visited == 0) {
            sn->visited = 1;
            if (top + 2 < MAX_STACK_SIZE) {
                stack[++top] = (StackNode){ sn->node->right, 0 };
                stack[++top] = (StackNode){ sn->node->left, 0 };
            }
            else {
                printf("Переполнение стека при пересчете node_count\n");
                return;
            }
        }
        else {
            sn->node->node_count = 1 +
                ((sn->node->left) ? sn->node->left->node_count : 0) +
                ((sn->node->right) ? sn->node->right->node_count : 0);
            top--;
        }
    }
}

// Функция для вывода дерева (для тестирования)
void print_tree(TreeNode* root) {
    if (root == NULL) return;
    printf("Узел %d, количество узлов %d\n", root->value, root->node_count);
    print_tree(root->left);
    print_tree(root->right);
}

// Функция для освобождения памяти дерева
void free_tree(TreeNode* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}