#include "Header.h"
#include "math.h"

//функция для сравнени элементов, равны ли они
//первое значение - полученное, второе ожидаемое
bool Assert_eq(int val1, int val2) {
	if (val1 != val2) return false;
	return true;
}
//то же самое, только для bool
bool Assert_eq_bool(bool val1, bool val2) {
	if (val1 != val2) return false;
	return true;
}

//Тест: добавление элемента в пустое множество
void AddElem_Test1() {
	Set* s = initialization();
	add(s, 5);

	bool res = true;
	res &= Assert_eq(s->head->data, 5);

	if (res) printf("AddElem_Test1 passed\n");
	    else printf("AddElem_Test1 failed\n");

	free(s);
}

//Тест: проверка наличия элемента
void ContainsElem_Test2() {
	Set* s = initialization();
	add(s, 5);

	bool res = true;
	res &= Assert_eq_bool(contains(s, 5), true);

	if (res) printf("ContainsElem_Test2 passed\n");
	else printf("ContainsElem_Test2 failed\n");

	free(s);
}

//Тест: содержит ли элемент, которого нет
void DoesntContainsElem_Test3() {
	Set* s = initialization();
	add(s, 2);

	bool res = true;
	res &= Assert_eq_bool(contains(s, 'q'), false);

	if (res) printf("DoesntContainsElem_Test3 passed\n");
	else printf("DoesntContainsElem_Test3 failed\n");

	free(s);
}

//Тест: объединение множеств
void Union_Test4() {
	bool res = true;
	Set* s1 = initialization();
	Set* s2 = initialization();

	add(s1, 1); add(s2, 2);
	Set* union_ = union_sets(s1, s2);//полученное объединение
	Set* result_set = initialization();
	add(result_set, 1); add(result_set, 2);

	node* i = union_->head;
	node* j = result_set->head;
	while (i != NULL && j != NULL) {
		res &= Assert_eq(i->data, j->data);
		i = i->next;
		j = j->next;
	}

	if (res) printf("Union_Test4 passed\n");
	else printf("Union_Test4 failed\n");

	free_set(s1);    free_set(s2);
	free_set(union_);free_set(result_set);
	free(i); free(j);
}

void AddFewElem_Test5() {
	Set* s = initialization();
	add(s, 5);add(s, 4);add(s, 3);
	add(s, 2);add(s, 1);

	bool res = true;
	res &= Assert_eq(s->head->data, 1);
	res &= Assert_eq(s->head->next->data, 2);
	res &= Assert_eq(s->head->next->next->data, 3);
	res &= Assert_eq(s->head->next->next->next->data, 4);
	res &= Assert_eq(s->head->next->next->next->next->data, 5);
	if (res) printf("AddFewElem_Test5 passed\n");
	else printf("AddFewElem_Test5 failed\n");

	free(s);
}

void AddRandomElem_Test6() {
	Set* s = initialization();
	add(s, 'a');
	
	bool res = true;
	res &= Assert_eq(s->head->data, 'a');
	if (res) printf("AddRandomElem_Test6 passed\n");
	else printf("AddRandomElem_Test6 failed\n");

	free(s);
}

void DeleteElem_Test7() {
	Set* s = initialization();
	
	removee(s, 2);
	bool res = true;
	res &= Assert_eq_bool(contains(s,2), false);

	if (res) printf("ContainsElem_Test7 passed\n");
	else printf("ContainsElem_Test7 failed\n");

	free(s);
}

//Тест: удаление несуществующего элемента
void DeleteNonExistElem_Test8() {
	Set* s = initialization();
	add(s, 2);

	bool res = true;
	res &= Assert_eq_bool(removee(s, 3), false);

	if (res) printf("DeleteNonExistElem_Test8 passed\n");
	else printf("DeleteNonExistElem_Test8 failed\n");

	free(s);
}

//Тест: удаление из пустого списка
void DeleteEmptyList_Test9() {//лучше убрать
	Set* s = initialization();
	bool res = true;
	res &= Assert_eq_bool(removee(s,2), false);

	if (res) printf("ContainsElem_Test9 passed\n");
	else printf("ContainsElem_Test9 failed\n");

	free(s);
}

//Тест: пересечение множеств
void intersectionSets_Test10() {
	bool res = true;
	Set* s1 = initialization();
	Set* s2 = initialization();
	Set* res_set = initialization();
	add(res_set, 4); add(res_set, 1);
	add(s1, 1); add(s1, 2); add(s1, 4);
	add(s2, 1); add(s2, 3); add(s2, 4);
	Set* inters = intersection(s1, s2);
	node* i = inters->head;
	node* j = res_set->head;
	while (i != NULL && j != NULL) {
		res &= Assert_eq(i->data, j->data);
		i = i->next;
		j = j->next;
	}
	if (res) printf("intersectionSets_Test10 passed\n");
	else printf("intersectionSets_Test10 failed\n");

	free_set(s1); free_set(s2); free_set(res_set); free_set(inters);
	free(i); free(j);
}

//Тест: пересечение пустых множеств
void IntersectionEmptySets_Test11() {
	bool res = true;
	Set* s1 = initialization();
	Set* s2 = initialization();
	Set* res_set = initialization();
	Set* inters = intersection(s1, s2);

	node* i = inters->head;
	node* j = res_set->head;
	while (i != NULL && j != NULL) {
		res &= Assert_eq(i->data, j->data);
		i = i->next;
		j = j->next;
	}

	if (res) printf("IntersectionEmptySets_Test11 passed\n");
	else printf("IntersectionEmptySets_Test11 failed\n");

	free_set(s1); free_set(s2); free_set(res_set); free_set(inters);
	free(i); free(j);
}

//Тест: объединение пустых множеств
void UnionEmpty_Test12() {
	bool res = true;
	Set* s1 = initialization(); Set* s2 = initialization();
	Set* union_ = union_sets(s1, s2);//полученное объединение
	Set* result_set = initialization();//мн-во, с которым буду сравнивать

	node* i = union_->head;
	node* j = result_set->head;
	while (i != NULL && j != NULL) {
		res &= Assert_eq(i->data, j->data);
		i = i->next;
		j = j->next;
	}

	if (res) printf("UnionEmpty_Test12 passed\n");
	else printf("UnionEmpty_Test12 failed\n");

	free_set(s1);    free_set(s2);
	free_set(union_); free_set(result_set);
	free(i); free(j);
}


int main() {
	AddElem_Test1();
	ContainsElem_Test2();
	DoesntContainsElem_Test3();
	Union_Test4();
	AddFewElem_Test5();
	AddRandomElem_Test6();
	DeleteElem_Test7();
	DeleteNonExistElem_Test8();
	DeleteEmptyList_Test9();
	intersectionSets_Test10();
	IntersectionEmptySets_Test11();
	UnionEmpty_Test12();

	printf("\nall test passed\n");
	return 0;
}