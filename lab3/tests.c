#include "Header.h"

void test_Check_Visits() {
    int visited_all[] = {1, 1, 1}; // Все посещены
    assert(Check_Visits(visited_all, 3) == 0);

    int visited_some[] = {1, 0, 1}; // Не все посещены
    assert(Check_Visits(visited_some, 3) == 0);
}

void test_Find_Hamilton_Path() {
    // Создаем простой граф: 1 -- 2 -- 3
    adjacency_list* l = malloc(sizeof(adjacency_list));
    l->number_of_vertex = 3;
    l->list = malloc(sizeof(Nodel*) * 3);

    // Инициализация списка смежности
    for (int i = 0; i < 3; i++) {
        l->list[i] = malloc(sizeof(Nodel));
        l->list[i]->next = NULL;
        l->list[i]->length = 1; // Предположительная длина
    }

    l->list[0]->vertex = 2; // Ребро 1 -> 2
    l->list[1]->vertex = 3; // Ребро 2 -> 3

    int* visited = calloc(3, sizeof(int));
    FILE* f = fopen("output1.txt", "w");
    assert(f != NULL);  // Убедитесь, что файл успешно открыт

    char result = Find_Hamilton_Path(l, visited, 0, f);
    fclose(f);
    
    assert(result == NULL); // Проверяем, был ли найден путь

    // Освобождение памяти
    for (int i = 0; i < 3; i++) {
        free(l->list[i]);
    }
    free(l->list);
    free(l);
    free(visited);
}

void test_Find_Hamilton_Path_Start() {
    // Создадим файл с входными данными
    FILE* input = fopen("test_input.txt", "w");
    fprintf(input, "3\n1 2\n2 3\n");
    fclose(input);

    Find_Hamilton_Path_Start("test_input.txt", "test_output.txt");

    // Проверим выходной файл
    FILE* output = fopen("test_output.txt", "r");
    char buffer[100];
    fgets(buffer, 100, output);
    assert(strcmp(buffer, "1 2 3 ") == 0);
    fclose(output);
}

void test_Get_Int_From_Char() {
    char num1[] = "123\n";
    assert(Get_Int_From_Char(num1) == 123);
    
    char num2[] = "42";
    assert(Get_Int_From_Char(num2) == 42);
}

void test_Get_List() {
    // Создадим временный файл для хранения графа
    FILE* f = fopen("temp_graph.txt", "w");
    fprintf(f, "3\n1 2\n2 3\n");
    fclose(f);

    adjacency_list* list = Get_List("temp_graph.txt");
    assert(list != NULL);
    assert(list->number_of_vertex == 3);
    
    // Проверим структуру
    assert(list->list[0]->vertex == 2);
    assert(list->list[1]->vertex == 3);
    
    // Освобождение памяти
    for (int i = 0; i < list->number_of_vertex; i++) {
        free(list->list[i]);
    }
    free(list->list);
    free(list);
    
    // Удалим временный файл (если требуется)
}

int main() {
    testCheckVisits();
    testFindHamiltonPath();
    testFindHamiltonPathStart();
    testGetIntFromChar();
    testGetList();
    printf("Все тесты прошли успешно.\n");
    return 0;
}