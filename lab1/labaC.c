#include "structure.h"
#include "tests.c"

Node *Create_Node(int vertex) {

    Node* new_Node = malloc(sizeof(Node));

    new_Node->vertex = vertex;
    new_Node->next = NULL;

    return new_Node;
}


Graph *Create_Graph(int vertices) 
{
    Graph *graph = malloc(sizeof(Graph));
    graph->number_of_vertices = vertices;

    graph->list = malloc(vertices * sizeof(Node*));

    if (graph->list == NULL) {

        free(graph);
        
        return NULL; 
    }


    for (int i = 0; i < vertices; i++) {
        graph->list[i] = NULL;
    }
    return graph;
}

void Add_Edge(Graph *graph, int the_start_vertex, int the_final_vertex) 
{
    Node* new_Node = Create_Node(the_final_vertex);

    new_Node->next = graph->list[the_start_vertex];
    graph->list[the_start_vertex] = new_Node;

    // Если неориентированный 
    new_Node = Create_Node(the_start_vertex);

    new_Node->next = graph->list[the_final_vertex];
    graph->list[the_final_vertex] = new_Node;
}

void Print_Graph(Graph *graph) 
{
    for (int i = 0; i < graph->number_of_vertices; i++) {

        Node *temp = graph->list[i];

        printf("\n Вершина %d: ", i);

        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL");
    }
}

Graph *Read_File(const char* filename) {

    FILE *file = fopen(filename, "r");
    
    if (!file) {
        return NULL;
    }

    int vertices;

    fscanf(file, "%d", &vertices); 

    Graph *graph = Create_Graph(vertices);
    int the_start_vertex, the_final_vertex;

    while (fscanf(file, "%d %d", &the_start_vertex, &the_final_vertex) != EOF) {
        Add_Edge(graph, the_start_vertex, the_final_vertex);
    }

    fclose(file);

    return graph;
}

void Find_Shortest_Way(Graph *graph, int start_vertex, int end_vertex) {

    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES]; 
    int start = 0;
    int stop = 0;
    int parent[MAX_VERTICES];

    for (int i = 0; i < graph->number_of_vertices; i++) {

        visited[i] = -1; 
        parent[i] = -1;  
    }

    queue[start++] = start_vertex;
    visited[start_vertex] = 1;

    while (start < stop) {

        int current = queue[start++];

        if (current == end_vertex) {
            break; // была достигнута конечная вершина
        }

        Node* temp = graph->list[current];

        while (temp) {

            if (visited[temp->vertex] == -1) {
                visited[temp->vertex] = visited[current] + 1; 
                parent[temp->vertex] = current; 
                queue[stop++] = temp->vertex; 
            }

            temp = temp->next;
        }
    }

    if (visited[end_vertex] != -1) {

        printf("Кратчайший путь между %d и %d:\n", start_vertex, end_vertex);

        int way[MAX_VERTICES];
        int index = 0;

        for (int v = end_vertex; v != -1; v = parent[v]) {
            way[index++] = v;
        }

        for (int i = index - 1; i >= 0; i--) {
            printf("%d ", way[i]);
            if (i > 0) printf("-> ");
        }

        printf("\n");
    }

    else {
        printf("Нет пути между %d и %d\n", start_vertex, end_vertex);
    }
}