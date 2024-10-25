# Лабораторная работа А: Связные списки
## Вариант 13. Развернутый связный список
Развёрнутый связный список — список, каждый физический элемент которого содержит несколько
логических (обычно в виде массива, что позволяет ускорить доступ к отдельным элементам).
Реализуйте развернутый связный список, элементами которого являются целые числа со
следующими операциями:
- Добавить элемент
- Найти номер элемента по ключу
- Найти элемент с заданным номером
- Удалить элемент с заданным номером
- Подсчитать количество элементов
- По заданному элементу найти следующий (итерирование)

Обратите особое внимание на интерфейсы вашей системы.
В чем преимущества и недостатки таких списков? Ответ: Преимуществом таких списков является то что они сочетают в себе большую скорость индексации (от обычных массивов) чем в связных списках и большую скорость изменения структуры (операции вставки, удаления, добавления элементов от связных списков) чем в обычных массивах, также в отличие от связных списокв намного меньше памяти тратиться на хранение ссылок на следующий узел. Недостатком является то что скорость индексации все таки ниже чем в массивах, а изменение структуры занимает больше веремени чем в связных списках. По сути развернутый связный список является очень оптимальным "средним" между связным списком и массивом.

## Небольшие комментарии к моему решению
- Файлы с кодом имеют расширение .cpp  т.к. gtest написан на C++ и использует ООП => не дружит с обычным С, однако весь код написаны на языке С (за исключением того что требует gtest).
- По уловию задания необходимо скинуть только файлы с кодом без файлов проекта (вроде .sln) поэтому необходимых зависимостей что бы запустить тесты в этом пул реквесте нет, но естественно код их всех проходит:
<image src="/images/test.jpg">
