# Лабораторная 1 
Вариант 20 - Очередь с приоритетами <br>
Структура Очереди: <br>
<p>typedef struct PriorityQueue {
	int data; //Значение Ячейки
	int key; //Приоритет Ячейки
	struct PriorityQueue* next; //Следующая Ячейка
} PriorityQueue;</p>
<p>Для очереди реализованы следующие Функции:
struct PriorityQueue* PrQcreate(int data, int key); //Создание новой очереди с нуля
void PrQclear(struct PriorityQueue* q); //Очистка существующей очереди
struct PriorityQueue* PrQinsert(struct PriorityQueue* q, int data, int key); //Вставка нового значения в очередь с сортировкой
int PrQextractMinimum(struct PriorityQueue* q); //Извлечение значения с минимальным приоритетом с обновлением очереди</p>