# Лабораторная 1 
Вариант 20 - Очередь с приоритетами <br>
Структура Очереди: <br>
<p>typedef struct PriorityQueue {
	int data; //Значение Ячейки<br>
	int key; //Приоритет Ячейки<br>
	struct PriorityQueue* next; //Следующая Ячейка<br>
} PriorityQueue;</p>
<p>Для очереди реализованы следующие Функции:<br>
struct PriorityQueue* PrQcreate(int data, int key); //Создание новой очереди с нуля<br>
void PrQclear(struct PriorityQueue* q); //Очистка существующей очереди<br>
struct PriorityQueue* PrQinsert(struct PriorityQueue* q, int data, int key); //Вставка нового значения в очередь с сортировкой<br>
int PrQextractMinimum(struct PriorityQueue* q); //Извлечение значения с минимальным приоритетом с обновлением<br> очереди</p>