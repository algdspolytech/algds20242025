# algds20242025
Лабораторная работа A
Вариант 12: XOR связный список (2)
XOR­связный список — структура данных, похожая на обычный двусвязный список, однако в каждом
элементе хранящая только один адрес — результат выполнения операции XOR над адресами
предыдущего и следующего элементов списка. Для того, чтобы перемещаться по списку, необходимо взять
TWiki > ComputerScience Web > LabA (02 Sep 2013, OlegTalalov)

два последовательных адреса и выполнить над ними операцию XOR, которая и даст реальный адрес
следующего элемента.
Реализуйте XOR­связный список элементами которого являются ASCII­Z строки, со следующими
операциями:
Добавить элемент в список
Удалить элемент из списка по ключу
Удалить данный элемент списка (по адресу элемента)
Найти элемент по ключу
Итерирование по списку
В чем недостатки и преимущества XOR­связанного списка?