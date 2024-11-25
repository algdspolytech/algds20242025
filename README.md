
# algds20242025
## Лабораторная работа D.
## Вариант 14. Судоку

Условие
Решите головоломку судоку размером N > 2.

Исходные данные
В текстовом файле input.txt храниться натуральное число 2 < N < 10. После чего
записаны N^2 строк, содержащие N^2 целых чисел в интервале [0; N^2] каждая. (0 –
означает, что клетка пуста, иначе там записано правильное значение). Выведите любое
решение судоку в текстовый файл output.txt в том же формате, что и исходный файл. Если
решения не существует выведите 0.

Дополнительные условия
1. Решите эту задачу с условием N=3.
2. Задача Судоку в общем случае NP-полна. судоку сводится к задаче вершинного
покрытия. Для решения этой задачи нередко используется такая структура данных,
как танцующие ссылки (Dancing Links). Реализуйте решение судоку с помощью
танцующих ссылок.

Пример
input.txt
3
0 0 5 3 0 0 0 0 0
8 0 0 0 0 0 0 2 0
0 7 0 0 1 0 5 0 0
4 0 0 0 0 5 3 0 0
0 1 0 0 7 0 0 0 6
0 3 2 0 0 0 0 8 0
0 6 0 5 0 0 0 0 9
0 0 4 0 0 0 0 3 0
0 0 0 0 0 9 7 0 0

output.txt
3
1 4 5 3 2 7 6 9 8
8 3 9 6 5 4 1 2 7
6 7 2 9 1 8 5 4 3
4 9 6 1 8 5 3 7 2
2 1 8 4 7 3 9 5 6
7 5 3 2 9 6 4 8 1
3 6 7 5 4 2 8 1 9
9 8 4 7 6 1 2 3 5
5 2 1 8 3 9 7 6 4
