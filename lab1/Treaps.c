#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Treaps.h"

//создание элемента со случайным приоритетом
Treap_t* CreateNode(int key) {
	srand(time(NULL));
	Treap_t* t = (Treap_t*)malloc(sizeof(Treap_t));
	t->key = key;
	t->priority = rand();
	t->left = NULL;
	t->right = NULL;
	return t;
}

/* Объединение
* 
* Вспомогательная функция, объединяет деревья l и r в одно дерево
* Условие - все ключи в l должны быть меньше ключей в r
*/
Treap_t* Merge(Treap_t* l, Treap_t* r) {
	if (l == NULL) {
		return r;
	}
	if (r == NULL) {
		return l;
	}
	if (l->priority < r->priority) {
		l->right = Merge(l->right, r);
		return l;
	}
	else {
		r->left = Merge(l, r->left);
		return r;
	}
}

/* Разделение
* 
* Вспомогательная функция, разделяет дерево t на два дерева l и r
* В l оказываются элементы с ключами < key, в r - с ключами >= key
*/
void Split(Treap_t* t, int key, Treap_t** l, Treap_t** r) {
	if (t == NULL) {
		*l = NULL;
		*r = NULL;
	}
	else {
		if (t->key < key) {
			*l = t;
			Split(t->right, key, &(t->right), r);
		}
		else {
			*r = t;
			Split(t->left, key, l, &(t->left));
		}
	}
}

//добавление элемента с ключом key
Treap_t* Add(Treap_t* t, int key) {
	Treap_t* newNode = CreateNode(key);
	Treap_t *l, *r;
	Split(t, key, &l, &r);
	Treap_t* res = Merge(l, Merge(newNode, r));
	return res;
}

//поиск элемента по ключу
Treap_t* Find(Treap_t* t, int key) {
	Treap_t* cur = t;
	while (cur != NULL && cur->key != key) {
		if (key < cur->key) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	return cur;
}

/* Удаление элемента по ключу
* 
* В случае если элемента с ключом key в дереве нет, дерево не меняется
*/
Treap_t* Delete(Treap_t* t, int key) {
	if (Find(t, key == NULL)) {
		return t;
	}
	Treap_t *l, *r, *rl, *rr; 
	Split(t, key, &l, &r);
	Split(r, key + 1, &rl, &rr);
	Treap_t* res = Merge(l, rr);
	return res;
}