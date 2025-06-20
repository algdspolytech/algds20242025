/*  splay_tree_full.c
 *  Скошенное дерево (splay tree) + юнит-тесты
 *  Обычная сборка: gcc -std=c11 -Wall -Wextra -O2 splay_tree_full.c -o outDebug
 *  Сборка тестов:  gcc -std=c11 -Wall -Wextra -O2 -DTEST splay_tree_full.c -o test_runner
 * 
 * или 
 * 
 * make или make all - собирает и приложение и тесты
 * make test - компилирует и запускает юнит-тесты
 * make run - запускает программу с input.txt → output.txt
 * make clean - удаляет все скомпилированные файлы
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

/* Структура узла скошенного дерева */
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Создание нового узла
static Node* createNode(int data) {
    Node *n = malloc(sizeof(Node));
    if (!n) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

// Правый поворот
static Node* rightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Левый поворот  
static Node* leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Основная операция splay - выталкивание элемента в корень
static Node* splay(Node *root, int data) {
    if (!root || root->data == data) {
        return root;
    }

    // Элемент в левом поддереве
    if (data < root->data) {
        if (!root->left) {
            return root;
        }

        // Zig-Zig (левый-левый)
        if (data < root->left->data) {
            root->left->left = splay(root->left->left, data);
            root = rightRotate(root);
        }
        // Zig-Zag (левый-правый)
        else if (data > root->left->data) {
            root->left->right = splay(root->left->right, data);
            if (root->left->right) {
                root->left = leftRotate(root->left);
            }
        }

        return root->left ? rightRotate(root) : root;
    }
    // Элемент в правом поддереве
    else {
        if (!root->right) {
            return root;
        }

        // Zag-Zag (правый-правый)
        if (data > root->right->data) {
            root->right->right = splay(root->right->right, data);
            root = leftRotate(root);
        }
        // Zag-Zig (правый-левый)
        else if (data < root->right->data) {
            root->right->left = splay(root->right->left, data);
            if (root->right->left) {
                root->right = rightRotate(root->right);
            }
        }

        return root->right ? leftRotate(root) : root;
    }
}

// Вставка элемента
static Node* insert(Node *root, int data) {
    if (!root) {
        return createNode(data);
    }

    root = splay(root, data);

    // Дубликат - не добавляем
    if (root->data == data) {
        return root;
    }

    Node *newNode = createNode(data);
    if (data < root->data) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = NULL;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = NULL;
    }

    return newNode;
}

// Удаление элемента
static Node* deleteNode(Node *root, int data) {
    if (!root) {
        return root;
    }

    root = splay(root, data);

    if (root->data != data) {
        return root;
    }

    Node *temp;
    if (!root->left) {
        temp = root->right;
    } else {
        temp = splay(root->left, data);
        temp->right = root->right;
    }

    free(root);
    return temp;
}

// Поиск элемента
static bool search(Node *root, int data) {
    root = splay(root, data);
    return root && root->data == data;
}

// Освобождение памяти дерева
static void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/* Блок тестов */
#ifdef TEST

void test1_insert_duplicate(void) {
    Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 10);
    assert(root->data == 10 && !root->left && !root->right);
    freeTree(root);
}

void test2_search_non_existing(void) {
    Node *root = NULL;
    root = insert(root, 10);
    bool found = search(root, 20);
    assert(!found);
    freeTree(root);
}

void test3_delete_non_existing(void) {
    Node *root = NULL;
    root = insert(root, 10);
    root = deleteNode(root, 30);
    assert(root && root->data == 10);
    freeTree(root);
}

void test4_delete_only_element(void) {
    Node *root = NULL;
    root = insert(root, 10);
    root = deleteNode(root, 10);
    assert(!root);
}

void test5_insert_single(void) {
    Node *root = NULL;
    root = insert(root, 50);
    assert(root && root->data == 50);
    freeTree(root);
}

void test6_search_after_splay(void) {
    Node *root = NULL;
    root = insert(root, 60);
    root = insert(root, 40);
    bool found = search(root, 40);
    assert(found && root->data == 40);
    freeTree(root);
}

void test7_delete_and_check_structure(void) {
    Node *root = NULL;
    root = insert(root, 60);
    root = insert(root, 40);
    root = deleteNode(root, 40);
    assert(root && root->data == 60);
    freeTree(root);
}

void test8_search_empty_tree(void) {
    bool found = search(NULL, 100);
    assert(!found);
}

void test9_mass_insert_delete(void) {
    Node *root = NULL;
    for (int i = 1; i <= 10; i++) {
        root = insert(root, i);
    }
    for (int i = 1; i <= 10; i++) {
        root = deleteNode(root, i);
    }
    assert(!root);
}

void test10_tree_structure(void) {
    Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = deleteNode(root, 10);
    assert(root && root->data == 5);
    freeTree(root);
}

int main(void) {
    printf("Running splay tree tests...\n");
    
    test1_insert_duplicate();
    printf("Test 1 passed\n");
    
    test2_search_non_existing();
    printf("Test 2 passed\n");
    
    test3_delete_non_existing();
    printf("Test 3 passed\n");
    
    test4_delete_only_element();
    printf("Test 4 passed\n");
    
    test5_insert_single();
    printf("Test 5 passed\n");
    
    test6_search_after_splay();
    printf("Test 6 passed\n");
    
    test7_delete_and_check_structure();
    printf("Test 7 passed\n");
    
    test8_search_empty_tree();
    printf("Test 8 passed\n");
    
    test9_mass_insert_delete();
    printf("Test 9 passed\n");
    
    test10_tree_structure();
    printf("Test 10 passed\n");
    
    printf("All tests passed!\n");
    return 0;
}

#else

// Инфиксный обход для вывода
static void inorder(Node *root, FILE *out) {
    if (!root) return;
    inorder(root->left, out);
    fprintf(out, "%d ", root->data);
    inorder(root->right, out);
}

int main(int argc, char *argv[]) {
    FILE *in = stdin, *out = stdout;
    
    if (argc >= 2) {
        in = fopen(argv[1], "r");
        if (!in) {
            perror("fopen input");
            return 1;
        }
    }
    if (argc >= 3) {
        out = fopen(argv[2], "w");
        if (!out) {
            perror("fopen output");
            if (in != stdin) fclose(in);
            return 1;
        }
    }

    Node *tree = NULL;
    char cmd[32];
    int x;
    
    while (fscanf(in, "%31s", cmd) == 1) {
        if (!strcmp(cmd, "insert")) {
            if (fscanf(in, "%d", &x) == 1) {
                tree = insert(tree, x);
            }
        }
        else if (!strcmp(cmd, "delete")) {
            if (fscanf(in, "%d", &x) == 1) {
                tree = deleteNode(tree, x);
            }
        }
        else if (!strcmp(cmd, "search")) {
            if (fscanf(in, "%d", &x) == 1) {
                bool found = search(tree, x);
                fprintf(out, "%s\n", found ? "found" : "not found");
            }
        }
        else if (!strcmp(cmd, "print")) {
            inorder(tree, out);
            fprintf(out, "\n");
        }
        else if (!strcmp(cmd, "exit")) {
            break;
        }
    }

    if (in != stdin) fclose(in);
    if (out != stdout) fclose(out);
    freeTree(tree);
    
    return 0;
}

#endif

