#include "unity.h"
#include "main.h" 

void setUp(void) {
    // Код инициализации перед каждым тестом (опционально)
}

void tearDown(void) {
    // Код очистки после каждого теста (опционально)
}

// Тест функции read_adjacency_matrix
void test_read_adjacency_matrix(void) {
    int size;
    int** matrix = read_adjacency_matrix("input.txt", &size);

    // Ожидаемый размер (из файла input.txt)
    int expected_size = 3; // Измените на ваш ожидаемый размер
    TEST_ASSERT_EQUAL_INT(expected_size, size);

    // Ожидаемая матрица
    int expected_matrix[3][3] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };

    // Проверяем соответствие матриц
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            TEST_ASSERT_EQUAL_INT(expected_matrix[i][j], matrix[i][j]);
        }
    }

    free_adjacency_matrix(matrix, size);
}

// Тест функции build_adjacency_list
void test_build_adjacency_list(void) {
    int size = 3;

    // Создаем тестовую матрицу
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }

    int data[3][3] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = data[i][j];
        }
    }

    Graph* graph = build_adjacency_list(matrix, size);

    // Проверяем вершину 0
    Node* temp = graph->adjLists[0];
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL_INT(1, temp->vertex);
    TEST_ASSERT_NULL(temp->next);

    // Проверяем вершину 1
    temp = graph->adjLists[1];
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL_INT(2, temp->vertex);
    TEST_ASSERT_NOT_NULL(temp->next);
    TEST_ASSERT_EQUAL_INT(0, temp->next->vertex);
    TEST_ASSERT_NULL(temp->next->next);

    // Проверяем вершину 2
    temp = graph->adjLists[2];
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL_INT(1, temp->vertex);
    TEST_ASSERT_NULL(temp->next);

    free_graph(graph);
    free_adjacency_matrix(matrix, size);
}

// Тест функции write_adjacency_list
void test_write_adjacency_list(void) {
    int size = 3;
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = size;
    graph->adjLists = (Node**)malloc(size * sizeof(Node*));

    // Вершина 0
    Node* node0 = create_node(1);
    graph->adjLists[0] = node0;

    // Вершина 1
    Node* node1_1 = create_node(2);
    Node* node1_2 = create_node(0);
    node1_2->next = node1_1;
    graph->adjLists[1] = node1_2;

    // Вершина 2
    Node* node2 = create_node(1);
    graph->adjLists[2] = node2;

    // Записываем список смежности в файл
    write_adjacency_list("test_output.txt", graph);

    // Проверяем содержимое файла
    FILE* file = fopen("test_output.txt", "r");
    TEST_ASSERT_NOT_NULL(file);

    char buffer[256];

    fgets(buffer, sizeof(buffer), file);
    TEST_ASSERT_EQUAL_STRING("Вершина 0: 1\n", buffer);

    fgets(buffer, sizeof(buffer), file);
    TEST_ASSERT_EQUAL_STRING("Вершина 1: 0 2\n", buffer);

    fgets(buffer, sizeof(buffer), file);
    TEST_ASSERT_EQUAL_STRING("Вершина 2: 1\n", buffer);

    fclose(file);

    // Удаляем тестовый файл и освобождаем память
    remove("test_output.txt");
    free_graph(graph);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_adjacency_matrix);
    RUN_TEST(test_build_adjacency_list);
    RUN_TEST(test_write_adjacency_list);

    return UNITY_END();
}
