#include "xor.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void tests() {
    oaoa* test = NULL;
    test = add(test, "one");
    test = add(test, "two");
    test = add(test, "three");
    printf("Добавление в тест: ");
    it(test); 
    test = dbk(test, "two");
    printf("Проверка удаления по ключу: ");
    it(test); 
    oaoa* f = find(test, "three");
    printf("Тест нашел: ");
    if (f != NULL) {
      printf("Найдено: %s\n", f->data); 
    }
    f = find(test, "four");
    printf("Тестовое нахождение несуществующее: ");
    if (f == NULL) {
      printf("Не найдено: four\n"); 
    }
    oaoa* e = NULL;
    printf("Итерация пустого списка: ");
    it(e); 
    e = add(e, "first");
    printf("Добавление в пустой список: ");
    it(e); 

    e = dbk(e, "first");
    printf("Удаление одного элемента: ");
    it(e); 

    test = dbk(test, "one");
    test = dbk(test, "one");
    printf("Тестовое удаление подобных: ");
    it(test); 

    test = dbk(test, "non-existent");
    printf("Тестовое удаление несуществующего: ");
    it(test); 

    test = add(test, "one");
    test = add(test, "two");
    printf("Тестовое добавление подобных: ");
    it(test); 
}
