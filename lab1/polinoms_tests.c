#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include"Polinoms.h"

//добавление элемента в пустую очередь
void test_Add2Queue_EmptyQueue_ReturnFirstElement_no1()
{
	struct Queue q;
	InitQueue(&q);
	Add2Queue(&q, 5, 2);

	assert(q.first != NULL);
	assert(q.first->coef == 5);
	assert(q.first->pow == 2);
	assert(q.first == q.last);
}
//добавление второго элемента в очередь и корректность указателей
void test_Add2Queue_SingleElementQueue_ReturnLastElement_no2()
{
	struct Queue q;
	InitQueue(&q);
	Add2Queue(&q, 5, 2);
	Add2Queue(&q, 3, 1);

	assert(q.last != NULL);
	assert(q.last->coef == 3);
	assert(q.last->pow == 1);
}
//правильность порядка элементов в очереди
void test_Add2Queue_MultipleElements_ReturnCorrectOrder_no3()
{
	struct Queue q;
	InitQueue(&q);
	Add2Queue(&q, 1, 0);
	Add2Queue(&q, 2, 1);
	Add2Queue(&q, 3, 2);

	assert(q.first->coef == 1);
	assert(q.first->pow == 0);
	assert(q.first->next->coef == 2);
	assert(q.first->next->pow == 1);
	assert(q.last->coef == 3);
	assert(q.last->pow == 2);
}
//добавление элемента с отрицательным коэффициентом
void test_Add2Queue_NegativeCoef_ReturnValidElement_no4()
{
	struct Queue q;
	InitQueue(&q);
	Add2Queue(&q, -5, 3);

	assert(q.first != NULL);
	assert(q.first->coef == -5);
	assert(q.last->pow == 3);
	assert(q.first == q.last);
}
//добавление элемента с нулевым коэффициентом
void test_Add2Queue_ZeroCoef_ReturnValidElement_no5()
{
	struct Queue q;
	InitQueue(&q);
	Add2Queue(&q, 0, 2);

	assert(q.first != NULL);
	assert(q.first->coef == 0);
	assert(q.first->pow == 2);
	assert(q.first == q.last);
}
//проверяет чтение полинома, в котором есть мономы с коэффициентом 1 или -1
void test_ReadPol_1coef_no6()
{
	struct Queue q;
	InitQueue(&q);
	FILE* f = fopen("test1.txt", "w");
	fprintf(f, "-x^2+x-x^3");
	fclose(f);

	f = fopen("test1.txt", "r");
	ReadPol(f, &q);
	fclose(f);

	assert(q.first->coef == -1 && q.first->pow == 2);
	assert(q.first->next->coef == 1 && q.first->next->pow == 1);
	assert(q.last->coef == -1 && q.last->pow == 3);
}
//проверяет чтение полинома, в котором есть мономы со степенью 1
void test_ReadPol_1pow_no7()
{
	struct Queue q;
	InitQueue(&q);
	FILE* f = fopen("test2.txt", "w");
	fprintf(f, "5*x-2*x^2");
	fclose(f);

	f = fopen("test2.txt", "r");
	ReadPol(f, &q);
	fclose(f);

	assert(q.first->coef == 5 && q.first->pow == 1);
}
//проверяет чтение полинома, в котором есть мономы со степенью 0
void test_ReadPol_0pow_no8()
{
	struct Queue q;
	InitQueue(&q);
	FILE* f = fopen("test3.txt", "w");
	fprintf(f, "-5+3-x");
	fclose(f);

	f = fopen("test3.txt", "r");
	ReadPol(f, &q);
	fclose(f);

	assert(q.first->coef == -5 && q.first->pow == 0);
}
//проверяет чтение полинома, в котором есть моном с коэффициентом 0
void test_ReadPol_0coef_no9()
{
	struct Queue q;
	InitQueue(&q);
	FILE* f = fopen("test4.txt", "w");
	fprintf(f, "0*x^2+3");
	fclose(f);

	f = fopen("test4.txt", "r");
	ReadPol(f, &q);
	fclose(f);

	assert(q.first->coef == 0);
}
//вспомогательная функция для создания очереди
void createQueue(struct Queue* q, int values[][2], int size)
{
	InitQueue(q);
	for (int i = 0; i < size; i++)
	{
		Add2Queue(q, values[i][0], values[i][1]);
	}
}
//проверяет уже отсортированную очередь
void test_Sort_alreadySorted_no10()
{
	struct Queue q;
	int values[][2] = { {1, 0}, {2, 1}, {3, 2} };
	createQueue(&q, values, 3);

	Sort(&q);

	assert(q.first->coef == 1 && q.first->pow == 0);
	assert(q.first->next->coef == 2 && q.first->next->pow == 1);
	assert(q.last->coef == 3 && q.last->pow == 2);
}
//проверяет пустую очередь
void test_Sort_EmptyQueue_no11()
{
	struct Queue q;
	InitQueue(&q);
	Sort(&q);

	assert(q.first == NULL && q.last == NULL);
}
//проверяет неотсортированную очередь
void test_Sort_Unsorted_no12()
{
	struct Queue q;
	int values[][2] = { {-5, 3}, {4, 1}, {-1, 2} };
	createQueue(&q, values, 3);

	Sort(&q);

	assert(q.first->coef == 4 && q.first->pow == 1);
	assert(q.first->next->coef == -1 && q.first->next->pow == 2);
	assert(q.last->coef == -5 && q.last->pow == 3);
}
//проверяет ситуацию, когда степени мономов совпадают
void test_SupPol_SamePow_no13()
{
	struct Queue q1;
	struct Queue q2;
	struct Queue q3;
	int values1[][2] = { {3, 0}, {-2, 1}, {6, 2} };
	int values2[][2] = { {-2, 0}, {5, 1}, {2, 2} };
	createQueue(&q1, values1, 3);
	createQueue(&q2, values2, 3);
	InitQueue(&q3);

	SupPol(&q1, &q2, &q3);

	assert(q3.first->coef == 1 && q3.first->pow == 0);
	assert(q3.first->next->coef == 3 && q3.first->next->pow == 1);
	assert(q3.last->coef == 8 && q3.last->pow == 2);
}
//проверяет, когда степени мономов не совпадают
void test_SupPol_DifferentPow_no14()
{
	struct Queue q1;
	struct Queue q2;
	struct Queue q3;
	int values1[][2] = { {3, 0}, {-2, 1}, {6, 3} };
	int values2[][2] = { {-2, 1}, {5, 2} };
	createQueue(&q1, values1, 3);
	createQueue(&q2, values2, 2);
	InitQueue(&q3);

	SupPol(&q1, &q2, &q3);

	assert(q3.first->coef == 3 && q3.first->pow == 0);
	assert(q3.first->next->coef == -4 && q3.first->next->pow == 1);
	assert(q3.first->next->next->coef == 5 && q3.first->next->next->pow == 2);
	assert(q3.last->coef == 6 && q3.last->pow == 3);
}
//проверяет ситуацию, когда в одном из полиномов есть моном с коэффициентом 0
void test_SupPol_0coef_no15()
{
	struct Queue q1;
	struct Queue q2;
	struct Queue q3;
	int values1[][2] = { {3, 0}, {0, 1}, {6, 2} };
	int values2[][2] = { {-2, 1}, {5, 2} };
	createQueue(&q1, values1, 3);
	createQueue(&q2, values2, 2);
	InitQueue(&q3);

	SupPol(&q1, &q2, &q3);

	assert(q3.first->coef == 3 && q3.first->pow == 0);
	assert(q3.first->next->coef == -2 && q3.first->next->pow == 1);
	assert(q3.last->coef == 11 && q3.last->pow == 2);
}
//проверяет ситуацию, когда есть мономы, которые при сложении сокращаются
void test_SupPol_SameMonoms_no16()
{
	struct Queue q1;
	struct Queue q2;
	struct Queue q3;
	int values1[][2] = { {3, 0}, {2, 1}, {6, 2} };
	int values2[][2] = { {-2, 1}, {5, 2} };
	createQueue(&q1, values1, 3);
	createQueue(&q2, values2, 2);
	InitQueue(&q3);

	SupPol(&q1, &q2, &q3);

	assert(q3.first->coef == 3 && q3.first->pow == 0);
	assert(q3.first->next->coef == 11 && q3.first->next->pow == 2);
	assert(q3.first->next == q3.last);
}
//проверяет ситуацию, когда одна из очередей пустая
void test_SupPol_OneEmptyQueue_no17()
{
	struct Queue q1;
	struct Queue q2 = {NULL, NULL};
	struct Queue q3;
	int values1[][2] = { {3, 0}, {2, 1}, {6, 2} };
	createQueue(&q1, values1, 3);
	InitQueue(&q3);

	SupPol(&q1, &q2, &q3);

	assert(q3.first->coef == 3 && q3.first->pow == 0);
	assert(q3.first->next->coef == 2 && q3.first->next->pow == 1);
	assert(q3.last->coef == 6 && q3.last->pow == 2);
}
//проверяет ситуацию, когда обе очереди пустые
void test_SupPol_EmptyQueues_no18()
{
	struct Queue q1 = {NULL, NULL};
	struct Queue q2 = { NULL, NULL };
	struct Queue q3;
	InitQueue(&q3);

	SupPol(&q1, &q2, &q3);

	assert(q3.first == NULL && q3.last == NULL);
}
//проверяет вывод полинома, содержащего моном с коэффициентом 1 или -1
void test_WritePol_1coef_no19()
{
	FILE* f = fopen("test5.txt", "w");
	struct Queue q;
	int values[][2] = { {-1, 1}, {1, 2} };
	createQueue(&q, values, 2);

	WritePol(f, &q);
	fclose(f);

	f = fopen("test5.txt", "r");
	char buf[20];
	fgets(buf, sizeof(buf), f);
	assert(strcmp(buf, "-x+x^2") == 0);
	fclose(f);
}
//проверяет вывод полинома, содержащего моном со степенью 0
void test_WritePol_0pow_no20()
{
	FILE* f = fopen("test6.txt", "w");
	struct Queue q;
	int values[][2] = { {-5, 0}, {1, 0} };
	createQueue(&q, values, 2);

	WritePol(f, &q);
	fclose(f);

	f = fopen("test6.txt", "r");
	char buf[20];
	fgets(buf, sizeof(buf), f);
	assert(strcmp(buf, "-5+1") == 0);
	fclose(f);
}
//проверяет вывод полинома, содержащего моном со степенью 1
void test_WritePol_1pow_no21()
{
	FILE* f = fopen("test7.txt", "w");
	struct Queue q;
	int values[][2] = { {1, 1}, {-1, 1}, {5, 2} };
	createQueue(&q, values, 3);

	WritePol(f, &q);
	fclose(f);

	f = fopen("test7.txt", "r");
	char buf[20];
	fgets(buf, sizeof(buf), f);
	assert(strcmp(buf, "x-x+5*x^2") == 0);
	fclose(f);
}
//проверяет вывод полинома с различными степенями
void test_WritePol_DifferenrPows_no22()
{
	FILE* f = fopen("test8.txt", "w");
	struct Queue q;
	int values[][2] = { {-5, 0}, {2, 1}, {-9, 2} };
	createQueue(&q, values, 3);

	WritePol(f, &q);
	fclose(f);

	f = fopen("test8.txt", "r");
	char buf[20];
	fgets(buf, sizeof(buf), f);
	assert(strcmp(buf, "-5+2*x-9*x^2") == 0);
	fclose(f);
}
//тестирование функции приведения подобных слагаемых в отсортированной очереди 
void test_SimilarTerm_no23()
{
	struct Queue q;
	int values[][2] = { {-1, 1}, {1, 1}, {2, 2}, {5, 2}, {-10, 3} };
	createQueue(&q, values, 5);

	SimilarTerm(&q);
	
	assert(q.first->coef == 0 && q.first->pow == 1);
	assert(q.first->next->coef == 7 && q.first->next->pow == 2);
	assert(q.last->coef == -10 && q.last->pow == 3);
}
//проверяет умножение на нулевой полином
void test_MultiplicationPol_OneEmptyQueue_ReturnEmptyQueue_no24()
{
	struct Queue q1;
	struct Queue q2;
	struct Queue q3;
	InitQueue(&q2);
	int values1[][2] = { {3, 0}, {2, 1}, {6, 2} };
	createQueue(&q1, values1, 3);
	InitQueue(&q3);

	MultiplicationPol(&q1, &q2, &q3);

	assert(q3.first == NULL);
	assert(q3.first == q3.last);
}
//произведение двух полиномов
void test_MultiplicationPol_TwoPol_no25()
{
	struct Queue q1;
	struct Queue q2;
	struct Queue q3;
	int values1[][2] = { {3, 0}, {2, 1}, {6, 2} };
	int values2[][2] = { {-5, 1}, {10, 3} };
	createQueue(&q1, values1, 3);
	createQueue(&q2, values2, 2);
	InitQueue(&q3);

	MultiplicationPol(&q1, &q2, &q3);

	assert(q3.first->coef == -15 && q3.first->pow == 1);
	assert(q3.first->next->coef == -10 && q3.first->next->pow == 2);
	assert(q3.first->next->next->coef == 0 && q3.first->next->next->pow == 3);
	assert(q3.first->next->next->next->coef == 20 && q3.first->next->next->next->pow == 4);
	assert(q3.last->coef == 60 && q3.last->pow == 5);
}
//производная константы
void test_DerPol_Const_ReturnZero_no26()
{
	struct Queue q1;
	int values1[][2] = { {3, 0} };
	createQueue(&q1, values1, 1);

	DerPol(&q1);

	assert(q1.first == NULL);
}
//производная полинома со степенями выше 0
void test_DerPol_no27()
{
	struct Queue q1;
	int values1[][2] = { {3, 0}, {2, 1}, {0, 2}, {10, 3} };
	createQueue(&q1, values1, 4);

	DerPol(&q1);

	assert(q1.first->coef == 2 && q1.first->pow == 0);
	assert(q1.first->next->coef == 0 && q1.first->next->pow == 1);
	assert(q1.last->coef == 30 && q1.last->pow == 2);
}

void RunTests()
{
	test_Add2Queue_EmptyQueue_ReturnFirstElement_no1();
	test_Add2Queue_SingleElementQueue_ReturnLastElement_no2();
	test_Add2Queue_MultipleElements_ReturnCorrectOrder_no3();
	test_Add2Queue_NegativeCoef_ReturnValidElement_no4();
	test_Add2Queue_ZeroCoef_ReturnValidElement_no5();
	test_ReadPol_1coef_no6();
	test_ReadPol_1pow_no7();
	test_ReadPol_0pow_no8();
	test_ReadPol_0coef_no9();
	test_Sort_alreadySorted_no10();
	test_Sort_EmptyQueue_no11();
	test_Sort_Unsorted_no12();
	test_SupPol_SamePow_no13();
	test_SupPol_DifferentPow_no14();
	test_SupPol_0coef_no15();
	test_SupPol_SameMonoms_no16();
	test_SupPol_OneEmptyQueue_no17();
	test_SupPol_EmptyQueues_no18();
	test_WritePol_1coef_no19();
	test_WritePol_0pow_no20();
	test_WritePol_1pow_no21();
	test_WritePol_DifferenrPows_no22();
	test_SimilarTerm_no23();
	test_MultiplicationPol_OneEmptyQueue_ReturnEmptyQueue_no24();
	test_MultiplicationPol_TwoPol_no25();
	test_DerPol_Const_ReturnZero_no26();
	test_DerPol_no27();

	printf("All tests were successful!\n");
}