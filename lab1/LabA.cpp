#include <stdio.h>
#include <stdlib.h>
#include "LabA.h" 


// Создание пустого списка
ul_list* ul_create_list(int max_length) {
    if (max_length == 0) return NULL;

    // Создаем первый пусто node
    ul_node* node = (ul_node*)malloc(sizeof(ul_node));
    node->numbers = (int*)malloc(sizeof(int) * max_length);
    node->length = 0;
    node->next = NULL;

    // Создаем объект списка
    ul_list* list = (ul_list*)malloc(sizeof(ul_list));
    list->head = node;
    list->nodes_length = 1;
    list->max_length = max_length;

    return list;
}


// Добавление элемента в список
ul_list* ul_add_item(ul_list* list, int item) {
    // Проходим до последнего node
    ul_node* node = list->head;
    while (node->next != NULL) node = node->next;

    // Если в последнем node еще есть место
    if (node->length < list->max_length) {
        node->numbers[node->length] = item;
        node->length++;
    }
    else {
        // Если в последнем node места нет, то создаем новый
        ul_node* new_node = (ul_node*)malloc(sizeof(ul_node));
        new_node->numbers = (int*)malloc(sizeof(int) * list->max_length);
        new_node->length = 1;
        new_node->next = NULL;

        // Добавляем в новую node значения и добавляем ее в связный список
        new_node->numbers[0] = item;
        node->next = new_node;
        list->nodes_length++;
    }

    return list;
}


// Получение элемента по индексу
int ul_get_item(ul_list* list, int index) {
    ul_node* node = list->head;
    while (node != NULL) {
        if (index < node->length)
            return node->numbers[index];
        else
            index -= node->length;

        node = node->next;
    }

    return 0;
}


// Удаление элемента по индексу
ul_list* ul_del_item(ul_list* list, int index) {
    ul_node* node = list->head;
    ul_node* last_node = NULL; // Предыдущий node

    while (node != NULL) {
        if (index < node->length) {

            // Мы нашли node в котором находится число для удаления
            for (int i = index; i < node->length - 1; i++)
                node->numbers[i] = node->numbers[i + 1];
            node->length--;

            // Если node оказался пустой то его надо удалить, т.е. связать предыдущий и следующий node'ы вместе
            if (node->length == 0) {
                if (last_node != NULL)
                    last_node->next = node->next;
                else
                    list->head = node->next;
                list->nodes_length--;
                free(node->numbers);
                free(node);
            }
            return list;
        }
        else
            index -= node->length;

        last_node = node;
        node = node->next;
    }

    return 0;
}


// Функция получения следующего элемента
int ul_get_next(int number, ul_list* list) {
    ul_node* node = list->head;
    int return_flag = 0;

    while (node != NULL) {
        for (int i = 0;i < node->length;i++) {
            if (return_flag)
                return node->numbers[i];
            if (node->numbers[i] == number)
                return_flag = 1;
        }
        node = node->next;
    }

    return NULL;
}


// Получение длинны списка
int ul_length(ul_list* list) {
    ul_node* node = list->head;
    int length = 0;

    while (node != NULL) {
        length += node->length;
        node = node->next;
    }

    return length;
}


// Функция для вывода списка в строку
void ul_display(ul_list* list) {
    if (list == NULL) {
        printf("NULL");
        return;
    }

    ul_node* node = list->head;
    int i = 0;
    while (node != NULL) {
        printf("Node %i: [ ", i);
        for (int j = 0; j < node->length; j++) {
            printf("%i, ", node->numbers[j]);
        }
        printf("]\n");
        node = node->next;
        i++;
    }
}


// Преобразование всего содержимого развернутого связного списка в обычный массив(необходим для проведения тестов)
int* ul_to_array(ul_list* list) {
    int length = list->nodes_length * list->max_length;

    int* new_array = (int*)malloc(sizeof(int) * length);
    for (int i = 0;i < length;i++) new_array[i] = 0;

    ul_node* node = list->head;
    int i = 0;
    while (node != NULL) {
        for (int j = 0;j < node->length;j++) 
            new_array[i+j] = node->numbers[j];
        i += list->max_length;
        node = node->next;
    }
    
    return new_array;
}


// Метод для сравнения двух обычных массивов (необходим для проведения тестов)
int ul_equal(int* list1, int* list2, int length) {
    for (int i = 0;i < length;i++)
        if (list1[i] != list2[i]) return 0;
    return 1;
}
