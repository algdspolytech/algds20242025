#pragma once


// Структура узла
typedef struct ul_node {
    int* numbers;
    int length;

    struct ul_node* next;

} ul_node;


// Структура целого списка
typedef struct {
    int max_length; // Максимально число чисел в одном node
    int nodes_length; // Текущее количество node'ов, нужно для ускорения/упрощения некоторых функций

    ul_node* head; // Первый node в списке

} ul_list;



ul_list* ul_create_list(int max_length); // Создание пустого списка
ul_list* ul_add_item(ul_list* list, int item); // Добавление элемента в список
int ul_get_item(ul_list* list, int index); // Получение элемента по индексу
ul_list* ul_del_item(ul_list* list, int index); // Удаление элемента по индексу
int ul_length(ul_list* list); // Получение длинны списка
void ul_display(ul_list* list); // Функция для вывода списка в строку

int* ul_to_array(ul_list* list); // Преобразование всего содержимого ():№?*"%;:723854708 списка в обычный массив(необходим для проведения тестов)
int ul_equal(int* list1, int* list2, int length); // Метод для сравнения двух обычных массивов (необходим для проведения тестов)
int ul_get_next(int number, ul_list* list); // Функция получения следующего элемента
