#include "xor.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <assert.h>

void tests() {
    oaoa* test = NULL;
    test = add(test, "one");
    test = add(test, "two");
    test = add(test, "three");
    
    printf("Добавление в тест: ");
    it(test);
    assert(find(test, "one") != NULL);
    assert(find(test, "two") != NULL);
    assert(find(test, "three") != NULL);

    test = dbk(test, "two");
    printf("Проверка удаления по ключу: ");
    it(test);
    assert(find(test, "two") == NULL);
    assert(find(test, "one") != NULL);
    assert(find(test, "three") != NULL);

    oaoa* f = find(test, "three");
    printf("Тест нашел: ");
    if (f != NULL) {
        printf("Найдено: %s\n", f->data); 
    }
    assert(f != NULL);

    f = find(test, "four");
    printf("Тестовое нахождение несуществующее: ");
    if (f == NULL) {
        printf("Не найдено: four\n"); 
    }
    assert(f == NULL);

    oaoa* e = NULL;
    printf("Итерация пустого списка: ");
    it(e);
    
    e = add(e, "first");
    printf("Добавление в пустой список: ");
    it(e);
    assert(find(e, "first") != NULL);

    e = dbk(e, "first");
    printf("Удаление одного элемента: ");
    it(e);
    assert(find(e, "first") == NULL);

    test = dbk(test, "one");
    test = dbk(test, "one");
    printf("Тестовое удаление подобных: ");
    it(test);
    assert(find(test, "one") == NULL);
    assert(find(test, "three") != NULL);

    test = dbk(test, "non-existent");
    printf("Тестовое удаление несуществующего: ");
    it(test);
    assert(find(test, "three") != NULL);

    test = add(test, "one");
    test = add(test, "two");
    printf("Тестовое добавление подобных: ");
    it(test);
    assert(find(test, "one") != NULL);
    assert(find(test, "two") != NULL);
}
