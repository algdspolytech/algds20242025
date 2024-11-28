
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <locale.h>



typedef struct {
    int V, s, t, K;
    int** adj;    
    int* visited; 
    int* path; 
    int path_length; 
} Graphss;


typedef struct {
    int vertex;
    int depth;
} Stack_node;


char* ReadLine(FILE* file) {
    char* line = malloc(sizeof(char));
    if (line == NULL) {
        free(line);
        printf("������ ��������� ������");
        return NULL;
    }
    char c;
    int i = 1;
    while (fscanf(file, "%c", &c) != EOF) {
        if (c == '\n' || c == '\0') {
            break;
        }
        line[i - 1] = c;
        i++;
        line = realloc(line, i * sizeof(char));
        if (line == NULL) {
            free(line);
            printf("������ ��������� ������");
            return NULL;
        }
    }
    line[i - 1] = '\0';
    return line;
}

void Free_Matrix(int** Matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        free(Matrix[i]);
        Matrix[i] = NULL;
    }
    free(Matrix);
    Matrix = NULL;
}

int** Create_Matrix(int vertices) {
    int** Matrix_adj = (int**)malloc(vertices * sizeof(int*));
    if (Matrix_adj == NULL) {
        free(Matrix_adj);
        return NULL;
    }
    int flag = 0;
    for (int i = 0; i < vertices; i++) {
        Matrix_adj[i] = (int*)malloc(vertices * sizeof(int));
        if (Matrix_adj[i] == NULL) {
            flag = 1;
        }
        if (flag == 0) {
            for (int j = 0; j < vertices; j++) {
                Matrix_adj[i][j] = 0; // �������������� ������
            }
        }
    }
    if (flag == 1) {
        Free_Matrix(Matrix_adj, vertices);
        return NULL;
    }
    return Matrix_adj;
}


Graphss* Parse_paramss(const char* filename, Graphss* graph) {
    FILE* file = fopen(filename, "r");
    fscanf(file, "%d %d %d %d", &graph->V, &graph->s, &graph->t, &graph->K);
    graph->s--; 
    graph->t--;
    graph->path_length = 0;
    fclose(file);
    return graph;
}



Graphss* Create_graph_from_matrix(char* filename) {
    Graphss* graph = (Graphss*)malloc(sizeof(Graphss));
    graph = Parse_paramss(filename, graph);
    graph->adj = Create_Matrix(graph->V);
    graph->visited = calloc(graph->V, sizeof(int));
    graph->path = malloc(graph->V * sizeof(int));
    return graph;
}


int Parsing_graphss(Graphss* graph, const char* filename) {
    FILE* input = fopen(filename, "r");
    if (!input) {
        fprintf(stderr, "������ �������� ����� %s.\n", filename);
        return 0;
    }
    char* line = ReadLine(input);
    for (int j = 0; j < graph->V; j++) {
        line = ReadLine(input);
        if (line[0] == '\0') {
            free(line);
            break;
        }
        char* token;

        
        token = strtok(line, " ");

        while (token != NULL) {
            int i = atoi(token) - 1; 
            graph->adj[j][i] = 1;
            graph->adj[i][j] = 1;
            token = strtok(NULL, " "); 
        }
    }

    fclose(input);
    return 1;
}


int Find_path(Graphss* graph) {
  
    Stack_node* stack = malloc(graph->V * sizeof(Stack_node));
    int top = -1; 

    
    stack[++top] = (Stack_node){ .vertex = graph->s, .depth = 0 };
    graph->visited[graph->s] = 1;

    
    int path_index = 0;

    while (top >= 0) {
        Stack_node node = stack[top--];
        int v = node.vertex;
        int depth = node.depth;

        
        graph->path[path_index++] = v;

        
        if (v == graph->t && depth >= graph->K) {
            graph->path_length = path_index;
            printf("\n");
            free(stack);
            return 1;
        }

        int has_unvisited_neighbor = 0; 

       
        for (int u = 0; u < graph->V; u++) {
            if (graph->adj[v][u] == 1 &&
                !graph->visited[u]) { 
                stack[++top] = (Stack_node){
                    .vertex = u, .depth = depth + 1 }; 
                graph->visited[u] = 1; 
                has_unvisited_neighbor = 1;
            }
        }

        
        if (!has_unvisited_neighbor) {
            path_index--; 
            graph->visited[v] = 0;
        }
    }

 
    free(stack);
    return 0;
}


void Write_result(Graphss* graph, const char* output_filename) {
    FILE* output = fopen(output_filename, "w");
    if (!output) {
        fprintf(stderr, "������ �������� ����� %s.\n", output_filename);
        return;
    }

    if (Find_path(graph)) {
        for (int i = 0; i < graph->path_length; i++) {
            fprintf(output, "%d ", graph->path[i] + 1);
        }
        fprintf(output, "\n");
    }
    else {
        fprintf(output, "0\n");
    }

    fclose(output);
}


void Memory_free(Graphss* graph) {
    for (int i = 0; i < graph->V; i++) {
        free(graph->adj[i]);
    }
    free(graph->adj);
    free(graph->visited);
    free(graph->path);
    free(graph);
}

void test_create_graph() {
    Graphss* graph = Create_graph_from_matrix("test_input_1.txt");
    assert(graph != NULL);
    assert(graph->V == 4); // �������� ���������� ������
    assert(graph->s == 0); // �������� ��������� �������
    assert(graph->t == 3); // �������� �������� �������
    assert(graph->K == 2); // �������� �������� K
    assert(graph->adj != NULL);
    assert(graph->visited != NULL);
    assert(graph->path != NULL);
    Memory_free(graph);
}

void test_create_matrix() {
    int vertices = 3;
    int** matrix = Create_Matrix(vertices);
    assert(matrix != NULL);
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            assert(matrix[i][j] == 0); // ��� �������� ������ ���� ����� 0
        }
    }
    Free_Matrix(matrix, vertices);
}

void test_read_line() {
    FILE* file = fopen("test_input_1.txt", "r");
    char* line = ReadLine(file);
    assert(line != NULL);
    assert(strlen(line) > 0);  // ������ ������ ���� �� ������
    free(line);
    fclose(file);
}

void test_parse_params() {
    Graphss graph;
    Parse_paramss("test_input_1.txt", &graph);
    assert(graph.V == 4);  // ��������� ���������� ������
    assert(graph.s == 0);  // ��������� ������� (������ ���� ��������� �� 1)
    assert(graph.t == 3);  // �������� ������� (������ ���� ��������� �� 1)
    assert(graph.K == 2);  // ��������� K
}

void test_parsing_graph() {
    Graphss graph;
    Parse_paramss("test_input_1.txt", &graph);
    assert(Parsing_graphss(&graph, "test_input_1.txt") == 1);
    assert(graph.adj[0][1] == 1);  // ��������, ��� ���������� ����� ����� ��������� 0 � 1
    assert(graph.adj[1][2] == 1);  // ��������, ��� ���������� ����� ����� ��������� 1 � 2
    assert(graph.adj[0][2] == 0);  // ��������, ��� ����� ��������� 0 � 2 ��� �����
    Memory_free(&graph);
}

void test_find_path_exists() {
    Graphss graph;
    Parse_paramss("test_input_1.txt", &graph);
    Parsing_graphss(&graph, "test_input_1.txt");
    assert(Find_path(&graph) == 1);  // ���� ������ ���� ������
    assert(graph.path_length > 0);   // ����� ���� ������ ���� ������ ����
    Memory_free(&graph);
}

void test_find_path_not_exists() {
    Graphss graph;
    Parse_paramss("test_input_1.txt", &graph);
    Parsing_graphss(&graph, "test_input_1.txt");
    graph.s = 0; // ��������� �������
    graph.t = 3; // �������� �������, ������� ��� ����
    assert(Find_path(&graph) == 0);  // ���� �� ������ ���� ������
    Memory_free(&graph);
}

void test_write_result() {
    Graphss graph;
    Parse_paramss("test_input_1.txt", &graph);
    Parsing_graphss(&graph, "test_input_1.txt");
    Write_result(&graph, "output.txt");

    FILE* output = fopen("output.txt", "r");
    assert(output != NULL);

    char result[100];
    fgets(result, sizeof(result), output);
    fclose(output);

    assert(strlen(result) > 0);  // ��������� ������ ���� �������
    Memory_free(&graph);
}

void test_file_open_error() {
    FILE* file = fopen("non_existing_file.txt", "r");
    assert(file == NULL);  // ���� �� ������ ���������
}

void test_memory_free() {
    Graphss* graph = Create_graph_from_matrix("test_input_1.txt");
    Parsing_graphss(graph, "test_input_1.txt");
    Memory_free(graph);  // ��������, ��� ������ ������������� ��� ������
}


void run_all_tests() {
    test_create_graph();
    test_create_matrix();
    test_read_line();
    test_parse_params();
    test_parsing_graph();
    test_find_path_exists();
    test_find_path_not_exists();
    test_write_result();
    test_file_open_error();
    test_memory_free();
}




int main() {
    setlocale(LC_ALL, "ru");
    run_all_tests();
    char* input = "input.txt";
    Graphss* graph = Create_graph_from_matrix(input);
    if (!Parsing_graphss(graph, input)) {
        return 1;
    }
    Write_result(graph, "output.txt");
    Memory_free(graph);
    return 0;
}

