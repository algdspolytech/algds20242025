#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Константа для настройки таблицы (минимальный размер) */
#define MIN_SIZE 2

/* Структура элемента таблицы */
typedef struct {
    char *key;      // Ключ-строка
    int is_occupied;// Флаг занятости (1 - занято, 0 - свободно)
    int is_deleted; // Флаг удаления (1 - удалено, 0 - нет)
} HashItem;

/* Структура хеш-таблицы */
typedef struct {
    HashItem *items;// Массив элементов
    int size;       // Общий размер таблицы
    int count;      // Количество занятых элементов
} HashTable;

/*
Первая хеш-функция (djb2 алгоритм)
Принимает: ключ (строку) и размер таблицы
Возвращает: индекс в таблице
*/
unsigned int hash1(const char *key, int size) {
    unsigned long hash = 5381;// Начальное значение
    int c;
    // Проходим по каждому символу строки
    while ((c = *key++)) {
        // Обновляем хеш: hash * 33 + c
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;// Обеспечиваем попадание в границы таблицы
}

/*
Вторая хеш-функция для разрешения коллизий
Всегда возвращает значение от 1 до size-1
*/
unsigned int hash2(const char *key, int size) {
    if (size < 2)
        return 1;// Защита от минимального размера

    unsigned long hash = 0;
    int c;
    while ((c = *key++)) {
        // Сложная смесь для создания хорошего распределения
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return (hash % (size - 1)) + 1;// Гарантируем диапазон 1..size-1
}

/*
Создание новой хеш-таблицы
Принимает: желаемый размер
Возвращает: указатель на таблицу или NULL при ошибке
*/
HashTable *create_table(int size) {
    // Проверка и корректировка размера
    if (size < MIN_SIZE)
        size = MIN_SIZE;

    // Выделяем память под структуру таблицы
    HashTable *table = malloc(sizeof(HashTable));
    if (!table)
        return NULL;

    // Инициализируем поля
    table->size = size;
    table->count = 0;

    // Выделяем память под элементы таблицы и обнуляем
    table->items = calloc(size, sizeof(HashItem));
    if (!table->items) {
        free(table);
        return NULL;
    }
    return table;
}

/*
Вставка элемента в таблицу
Принимает: таблицу и ключ (строку)
Возвращает: 0 при успехе, -1 при переполнении, -2 при дубликате, -3 при ошибке
*/
int insert(HashTable *table, const char *key) {
    // Проверка входных параметров
    if (!table || !key || table->count >= table->size)
        return -1;

    // Вычисляем начальную позицию и шаг
    unsigned int index = hash1(key, table->size);
    unsigned int step = hash2(key, table->size);
    unsigned int initial = index;// Запоминаем начальную позицию
    int i = 0;                   // Счетчик попыток

    // Пытаемся найти место для вставки
    do {
        // Если ячейка свободна или удалена
        if (!table->items[index].is_occupied || table->items[index].is_deleted) {
            // Освобождаем старый ключ, если был
            if (table->items[index].key)
                free(table->items[index].key);

            // Копируем строку
            table->items[index].key = strdup(key);
            if (!table->items[index].key)
                return -3;// Ошибка копирования

            // Устанавливаем флаги
            table->items[index].is_occupied = 1;
            table->items[index].is_deleted = 0;
            table->count++;
            return 0;// Успех
        }

        // Проверка на дубликат
        if (strcmp(table->items[index].key, key) == 0)
            return -2;

        // Переход к следующей ячейке с двойным хешированием
        index = (index + step) % table->size;
        i++;
    } while (i < table->size && index != initial);// Пока не проверим всю таблицу

    return -3;// Не нашли свободного места
}

/*
Поиск элемента в таблице
Принимает: таблицу и ключ
Возвращает: индекс элемента или -1 если не найден
*/
int search(HashTable *table, const char *key) {
    if (!table || !key)
        return -1;

    // Вычисляем начальную позицию и шаг
    unsigned int index = hash1(key, table->size);
    unsigned int step = hash2(key, table->size);
    unsigned int initial = index;
    int i = 0;

    do {
        // Если ячейка занята и не удалена
        if (table->items[index].is_occupied && !table->items[index].is_deleted) {
            // Сравниваем ключи
            if (strcmp(table->items[index].key, key) == 0)
                return index;
        }
        // Если нашли пустую и не удаленную ячейку - элемент не существует
        else if (!table->items[index].is_occupied && !table->items[index].is_deleted) {
            return -1;
        }

        // Переход к следующей ячейке
        index = (index + step) % table->size;
        i++;
    } while (i < table->size && index != initial);

    return -1;// Элемент не найден
}

/*
Удаление элемента из таблицы
Принимает: таблицу и ключ
Возвращает: 0 при успехе, -1 если элемент не найден
*/
int delete(HashTable *table, const char *key) {
    // Сначала находим элемент
    int index = search(table, key);
    if (index == -1)
        return -1;

    // Помечаем как удаленный (память не освобождаем!)
    table->items[index].is_deleted = 1;
    table->count--;
    return 0;
}

/*
Освобождение памяти таблицы
Принимает: указатель на таблицу
*/
void free_table(HashTable *table) {
    if (!table)
        return;

    // Освобождаем все строки-ключи
    for (int i = 0; i < table->size; i++) {
        if (table->items[i].key)
            free(table->items[i].key);
    }
    // Освобождаем массив элементов и саму структуру
    free(table->items);
    free(table);
}

/*************** ТЕСТЫ ***************/

// Тест 1: Создание пустой таблицы
void Test1_CreateEmptyTable() {
    HashTable *table = create_table(5);
    assert(table != NULL);    // Таблица создана
    assert(table->size == 5); // Правильный размер
    assert(table->count == 0);// Пустая
    free_table(table);
}

// Тест 2: Вставка и поиск элемента
void Test2_InsertSearch() {
    HashTable *table = create_table(5);
    assert(insert(table, "test") == 0); // Успешная вставка
    assert(search(table, "test") != -1);// Элемент найден
    free_table(table);
}

// Тест 3: Попытка вставить дубликат
void Test3_DuplicateInsert() {
    HashTable *table = create_table(5);
    assert(insert(table, "dup") == 0); // Первая вставка OK
    assert(insert(table, "dup") == -2);// Дубликат не допускается
    free_table(table);
}

// Тест 4: Переполнение таблицы
void Test4_FullTable() {
    HashTable *table = create_table(2);// Маленькая таблица
    assert(insert(table, "a") == 0);   // Первый элемент
    assert(insert(table, "b") == 0);   // Второй элемент
    assert(insert(table, "c") == -1);  // Таблица переполнена
    free_table(table);
}

// Тест 5: Обработка коллизий
void Test5_CollisionHandling() {
    HashTable *table = create_table(5);
    assert(insert(table, "a") == 0); // Вставка первого элемента
    assert(insert(table, "f") == 0); // Должна произойти коллизия
    assert(table->count == 2);       // Оба элемента добавлены
    assert(search(table, "a") != -1);// Первый элемент на месте
    assert(search(table, "f") != -1);// Второй элемент на месте
    free_table(table);
}

// Тест 6: Поиск несуществующего элемента
void Test6_SearchNonExistent() {
    HashTable *table = create_table(5);
    assert(search(table, "missing") == -1);// Элемент не найден
    free_table(table);
}

// Тест 7: Удаление элемента
void Test7_Delete() {
    HashTable *table = create_table(5);
    assert(insert(table, "del") == 0); // Вставляем
    assert(delete (table, "del") == 0);// Удаляем
    assert(search(table, "del") == -1);// Проверяем что удален
    assert(table->count == 0);         // Счетчик уменьшился
    free_table(table);
}

// Тест 8: Повторная вставка после удаления
void Test8_ReinsertAfterDelete() {
    HashTable *table = create_table(5);
    assert(insert(table, "key") == 0); // Вставляем
    assert(delete (table, "key") == 0);// Удаляем
    assert(insert(table, "key") == 0); // Вставляем снова
    assert(table->count == 1);         // Только один элемент
    free_table(table);
}

// Тест 9: Проверка что одинаковый ключ дает одинаковый хеш
void Test9_SameKeySameHash() {
    unsigned int h1 = hash1("test", 10);
    unsigned int h2 = hash1("test", 10);
    assert(h1 == h2);
}

// Тест 10: Проверка что хеш-функции разные
void Test10_DifferentHashes() {
    unsigned int h1 = hash1("test", 10);
    unsigned int h2 = hash2("test", 10);
    assert(h1 != h2);// Две разные функции дают разные результаты
}

int main() {
    // Запускаем все тесты
    Test1_CreateEmptyTable();
    Test2_InsertSearch();
    Test3_DuplicateInsert();
    Test4_FullTable();
    Test5_CollisionHandling();
    Test6_SearchNonExistent();
    Test7_Delete();
    Test8_ReinsertAfterDelete();
    Test9_SameKeySameHash();
    Test10_DifferentHashes();

    printf("All tests passed successfully!\n");
    return 0;
}