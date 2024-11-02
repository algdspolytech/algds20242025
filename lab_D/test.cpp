#include "pch.h"

extern "C" {
#include "Lab_D.h" // Подключаем ваш код с функциями
}

TEST(GraphTest, Creating_matrix) {
    int n = 5;
    int** matrix = Create_Matrix_adj(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            EXPECT_EQ(matrix[i][j], 0) << "Ожидалось 0";
        }
    }
    Free_Matrix_adj(matrix, n);
}

TEST(GraphTest, Readline) {
    FILE* file = fopen("input.txt", "r");
    char* line = Read_line(file);
    EXPECT_EQ(line[0], '3') << "Ожидалось 3";
    EXPECT_EQ(line[1], ' ') << "Ожидалось "
                               "";
    EXPECT_EQ(line[2], '1') << "Ожидалось 1";
    EXPECT_EQ(line[3], ' ') << "Ожидалось "
                               "";
    EXPECT_EQ(line[4], '3') << "Ожидалось 3";
    EXPECT_EQ(line[5], ' ') << "Ожидалось "
                               "";
    EXPECT_EQ(line[6], '2') << "Ожидалось 2";
    EXPECT_EQ(line[7], '\0') << "Ожидалось \\0";
    fclose(file);
    free(line);
}

TEST(GraphTest, ParseParameters) { 
    char* filename = "input.txt";
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    Parse_parameters(filename, graph);
    EXPECT_EQ(graph->V, 3) << "Ожидалось 3";
    EXPECT_EQ(graph->s, 0) << "Ожидалось 0";
    EXPECT_EQ(graph->t, 2) << "Ожидалось 2";
    EXPECT_EQ(graph->K, 2) << "Ожидалось 2";
    EXPECT_EQ(graph->path_length, 0) << "Ожидалось 0";
    free(graph);
}

TEST(GraphTest, CreateGraph) {
    char* filename = "input.txt";
    Graph* graph = Create_graph(filename);
    EXPECT_EQ(graph->V, 3) << "Ожидалось 3";
    EXPECT_EQ(graph->s, 0) << "Ожидалось 0";
    EXPECT_EQ(graph->t, 2) << "Ожидалось 2";
    EXPECT_EQ(graph->K, 2) << "Ожидалось 2";
    EXPECT_EQ(graph->path_length, 0) << "Ожидалось 0";

    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            EXPECT_EQ(graph->adj[i][j], 0) << "Ожидалось 0";
        }
    }

    for (int i = 0; i < graph->V; i++) {
        EXPECT_EQ(graph->visited[i], 0) << "Ожидалось 0";
    }

    Free_memory(graph);
}

TEST(GraphTest, PasreGraph) {
    char* filename = "input.txt";
    Graph* graph = Create_graph(filename);
    EXPECT_EQ(Parse_Graph(graph,filename),1) << "Ожидалось 1";
    EXPECT_EQ(graph->adj[0][0], 0) << "Ожидалось 0";
    EXPECT_EQ(graph->adj[0][1], 1) << "Ожидалось 1";
    EXPECT_EQ(graph->adj[0][2], 1) << "Ожидалось 1";
    EXPECT_EQ(graph->adj[1][0], 1) << "Ожидалось 1";
    EXPECT_EQ(graph->adj[1][1], 0) << "Ожидалось 0";
    EXPECT_EQ(graph->adj[1][2], 1) << "Ожидалось 1";
    EXPECT_EQ(graph->adj[2][0], 1) << "Ожидалось 1";
    EXPECT_EQ(graph->adj[2][1], 1) << "Ожидалось 1";
    EXPECT_EQ(graph->adj[2][2], 0) << "Ожидалось 0";
    Free_memory(graph);
}

TEST(GraphTest, FindPath) {
    char* filename = "input.txt";
    Graph* graph = Create_graph(filename);
    Parse_Graph(graph, filename);
    EXPECT_EQ(Find_path(graph), 1) << "Ожидалось 1";
    EXPECT_EQ(graph->path_length, 3) << "Ожидалось 3";
    for (int i = 0; i < graph->path_length; i++) {
        EXPECT_EQ(graph->path[i], i) << "Ожидалось %d",i;
    }
    Free_memory(graph);
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); // Запуск всех тестов
}