
# algds20242025
# Лабораторная работа B: Управление памятью
## Вариант 13: Следующий подходящий. Двухсвязный список. (2)
Реализуйте систему управления памятью, построенную на списках пустых блоков. Используйте
двухсвязный список и стратегию “Следующий подходящий”.
Напишите функции выделения и освобождения памяти блоками произвольного размера.
Сравните производительность вашей системы с стандартным malloc/free

## Эффективность написанного решения
Для сравнения эффективности работы нашего решения (memalloc) и встроенных функций malloc() и free(), была написана программа для тестирования скорости работы этих функций. Она выполняет определенное количество тестов и замеряет время их выполнения, каждый тест состоит из случайного количества действий выделения и освобождения памяти. На следующем графики представлена зависимость времени выполнения от количества тестов, для обоих функций:
<image src="/images/memalloc.jpg">
Из представленного графика видно что наше решение немного уступает по скорости встроенной функции malloc().

## Прохождение тестов
<image src="/images/tests.jpg">
