#include "pch.h"
#include "../LabA/LabA.cpp" // Здесь *.cpp а не *.h потому что, при сборке,
							// линкер почему то не может найти нужные функции в этом файле
							// (такой костыль найден на StackOverflow, другого решения проблемы найти не удалось)


// Тест если максимальный размер массива в одном узле равен 0, тогда список должен быть NULL так как такого списка быть не может
TEST(UlList__ul_create_list__Test, CreateListZeroMaxlength___1) {
	ul_list* list = ul_create_list(0);
	int eq = list == NULL;
	EXPECT_EQ(1, eq);
}

// Тест если максимальный размер массива в одном узле равен 5
TEST(UlList__ul_create_list__Test, CreateListFiveMaxlength___2) {
	ul_list* list = ul_create_list(5);

	int* val_list = ul_to_array(list);
	int true_list[5] = { 0, 0, 0, 0, 0 };

	int eq = ul_equal(val_list, true_list, 5);
	EXPECT_EQ(1, eq);
}

// Попробуем добавить в список 3 элемента (числа от 1 до 3)
TEST(UlList__ul_add_item__Test, AddThreeElements___3) {
	ul_list* list = ul_create_list(5);

	for (int i = 1;i < 4;i++)
		ul_add_item(list, i);

	int* val_list = ul_to_array(list);
	int true_list[5] = { 1, 2, 3, 0, 0 };

	int eq = ul_equal(val_list, true_list, 5);
	EXPECT_EQ(1, eq);
}

// Попробуем добавить в список 7 элементов (числа от 1 до 7)
// в такой ситуации (т.к. максимальное число элементов в node равно 5) должен быть создан еще один node)
TEST(UlList__ul_add_item__Test, AddSevenElements__4) {
	ul_list* list = ul_create_list(5);

	for (int i = 1;i < 8;i++)
		ul_add_item(list, i);

	int* val_list = ul_to_array(list);
	int true_list[10] = { 1, 2, 3, 4, 5, 6, 7, 0, 0, 0 };

	int eq = ul_equal(val_list, true_list, 10);
	EXPECT_EQ(1, eq);
}

// Попробуем удалить из списка 1 элемент (по индексу) из последнего node
TEST(UlList__ul_del_item__Test, DelOneElementFromLastNode__5) {
	ul_list* list = ul_create_list(5);

	for (int i = 1;i < 8;i++)
		ul_add_item(list, i);
	ul_del_item(list, 6);

	int* val_list = ul_to_array(list);
	int true_list[10] = { 1, 2, 3, 4, 5, 6, 0, 0, 0, 0 };

	int eq = ul_equal(val_list, true_list, 10);
	EXPECT_EQ(1, eq);
}

// Попробуем удалить из списка 1 элемент (по индексу) из первого node
TEST(UlList__ul_del_item__Test, DelOneElementFromFirstNode__6) {
	ul_list* list = ul_create_list(5);

	for (int i = 1;i < 8;i++)
		ul_add_item(list, i);
	ul_del_item(list, 3);

	int* val_list = ul_to_array(list);
	int true_list[10] = { 1, 2, 3, 5, 0, 6, 7, 0, 0, 0 };

	int eq = ul_equal(val_list, true_list, 10);
	EXPECT_EQ(1, eq);
}

// Попробуем удалить из списка все элементы определенного node (тогда такой node должен быть полностью уничтожен)
TEST(UlList__ul_del_item__Test, DelAllElemntsFromOneNode__7) {
	ul_list* list = ul_create_list(5);

	for (int i = 1;i < 8;i++)
		ul_add_item(list, i);

	for (int i = 0;i < 5;i++) 
		ul_del_item(list, 0);

	int* val_list = ul_to_array(list);
	int true_list[5] = { 6, 7, 0, 0, 0 };

	int eq = ul_equal(val_list, true_list, 5);
	EXPECT_EQ(1, eq);
}

// Попробуем удалить из списка элемент которого там нет (удаляем 13-ый элемент, а длинна списка 7)
TEST(UlList__ul_del_item__Test, DelOneNonExistentElement__8) {
	ul_list* list = ul_create_list(5);

	for (int i = 1;i < 8;i++)
		ul_add_item(list, i);
	ul_del_item(list, 13);

	int* val_list = ul_to_array(list);
	int true_list[10] = { 1, 2, 3, 4, 5, 6, 7, 0, 0, 0 };

	int eq = ul_equal(val_list, true_list, 10);
	EXPECT_EQ(1, eq);
}

// Попробуем удалить из пустого списка один элемент
TEST(UlList__ul_del_item__Test, DelOneElementFromEmptyList__9) {
	ul_list* list = ul_create_list(5);

	ul_del_item(list, 3);

	int* val_list = ul_to_array(list);
	int true_list[5] = { 0, 0, 0, 0, 0 };

	int eq = ul_equal(val_list, true_list, 5);
	EXPECT_EQ(1, eq);
}


// Пробуем получить следующий элемент
TEST(UlList__ul_get_next__Test, GetNextElement__10) {
	ul_list* list = ul_create_list(5);

	for (int i = 1;i < 8;i++)
		ul_add_item(list, i);

	int value = ul_get_next(6, list);

	EXPECT_EQ(7, value);
}


// Пробуем получить следующий элемент которого нет
TEST(UlList__ul_get_next__Test, GetEmptyNextElement__11) {
	ul_list* list = ul_create_list(5);

	for (int i = 1;i < 8;i++)
		ul_add_item(list, i);

	int value = ul_get_next(7, list);

	EXPECT_EQ(value, NULL);
}


// Пробуем получить длинну списка
TEST(UlList__ul_length__Test, GetLengthFromSevenElementsList__12) {
	ul_list* list = ul_create_list(5);

	for (int i = 1;i < 8;i++)
		ul_add_item(list, i);

	int value = ul_length(list);

	EXPECT_EQ(value, 7);
}
